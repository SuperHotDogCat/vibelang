#include "semantics.h"
#include <stdexcept>
#include <sstream>

namespace novus {

static std::string errorWithLoc(const std::string& msg, const Location& loc) {
    std::stringstream ss;
    ss << "Error at line " << loc.line << ", col " << loc.col << ": " << msg;
    return ss.str();
}

void SymbolTable::pushScope() {
    scopes.push_back({});
}

void SymbolTable::popScope() {
    scopes.pop_back();
}

void SymbolTable::define(const std::string& name, std::shared_ptr<Type> type, bool isFunction) {
    scopes.back()[name] = {type, isFunction};
}

SymbolTable::Symbol* SymbolTable::resolve(const std::string& name) {
    for (auto it = scopes.rbegin(); it != scopes.rend(); ++it) {
        if (it->count(name)) {
            return &((*it)[name]);
        }
    }
    return nullptr;
}

void SemanticAnalyzer::analyze(Program* program) {
    symbolTable.pushScope();
    collectDecls(program);
    analyzeOnly(program);
    symbolTable.popScope();
}

void SemanticAnalyzer::collectDecls(Program* program) {
    for (auto& decl : program->decls) {
        if (auto* sd = dynamic_cast<StructDecl*>(decl.get())) {
            structs[sd->name] = sd;
        } else if (auto* fd = dynamic_cast<FunctionDecl*>(decl.get())) {
            symbolTable.define(fd->name, fd->returnType, true);
        } else if (auto* id = dynamic_cast<ImplDecl*>(decl.get())) {
            for (auto& md : id->methods) {
                methods[id->structName][md->funcDecl->name] = md.get();
            }
        } else if (auto* gv = dynamic_cast<GlobalVarDecl*>(decl.get())) {
            symbolTable.define(gv->varDecl->name, gv->varDecl->type);
        }
    }
}

void SemanticAnalyzer::analyzeOnly(Program* program) {
    for (auto& decl : program->decls) {
        visitDecl(decl.get());
    }
}

void SemanticAnalyzer::visitDecl(Decl* decl) {
    if (auto* gv = dynamic_cast<GlobalVarDecl*>(decl)) {
        visitStmt(gv->varDecl.get());
    } else if (auto* fd = dynamic_cast<FunctionDecl*>(decl)) {
        if (!fd->body) return;
        symbolTable.pushScope();
        currentReturnType = fd->returnType;
        for (auto& param : fd->params) {
            symbolTable.define(param.name, param.type);
        }
        visitStmt(fd->body.get());
        symbolTable.popScope();
    } else if (auto* id = dynamic_cast<ImplDecl*>(decl)) {
        for (auto& md : id->methods) {
            symbolTable.pushScope();
            currentReturnType = md->funcDecl->returnType;
            // Add 'self' parameter
            auto selfType = std::make_shared<PointerType>(std::make_shared<StructType>(id->structName));
            symbolTable.define("self", selfType);
            for (auto& param : md->funcDecl->params) {
                symbolTable.define(param.name, param.type);
            }
            visitStmt(md->funcDecl->body.get());
            symbolTable.popScope();
        }
    }
}

void SemanticAnalyzer::visitStmt(Stmt* stmt) {
    if (auto* bs = dynamic_cast<BlockStmt*>(stmt)) {
        symbolTable.pushScope();
        for (auto& s : bs->stmts) {
            visitStmt(s.get());
        }
        symbolTable.popScope();
    } else if (auto* vs = dynamic_cast<VarDeclStmt*>(stmt)) {
        if (vs->init) {
            visitExpr(vs->init.get());
            if (!isAssignable(vs->type, vs->init->evaluatedType)) {
                throw std::runtime_error(errorWithLoc("Type mismatch in variable initialization: " + vs->name, vs->loc));
            }
        }
        symbolTable.define(vs->name, vs->type);
    } else if (auto* es = dynamic_cast<ExprStmt*>(stmt)) {
        visitExpr(es->expr.get());
    } else if (auto* is = dynamic_cast<IfStmt*>(stmt)) {
        visitExpr(is->condition.get());
        visitStmt(is->thenStmt.get());
        if (is->elseStmt) visitStmt(is->elseStmt.get());
    } else if (auto* ws = dynamic_cast<WhileStmt*>(stmt)) {
        visitExpr(ws->condition.get());
        visitStmt(ws->body.get());
    } else if (auto* rs = dynamic_cast<ReturnStmt*>(stmt)) {
        if (rs->expr) {
            visitExpr(rs->expr.get());
            if (!isAssignable(currentReturnType, rs->expr->evaluatedType)) {
                throw std::runtime_error(errorWithLoc("Type mismatch in return statement", rs->loc));
            }
        } else if (currentReturnType->kind != TypeKind::Void) {
            throw std::runtime_error(errorWithLoc("Return without value in non-void function", rs->loc));
        }
    }
}

void SemanticAnalyzer::visitExpr(Expr* expr) {
    if (auto* il = dynamic_cast<IntLiteral*>(expr)) {
        il->evaluatedType = std::make_shared<ScalarType>(TypeKind::Int);
    } else if (auto* fl = dynamic_cast<FloatLiteral*>(expr)) {
        fl->evaluatedType = std::make_shared<ScalarType>(TypeKind::Float);
    } else if (auto* bl = dynamic_cast<BoolLiteral*>(expr)) {
        bl->evaluatedType = std::make_shared<ScalarType>(TypeKind::Bool);
    } else if (auto* sl = dynamic_cast<StringLiteral*>(expr)) {
        sl->evaluatedType = std::make_shared<ScalarType>(TypeKind::String);
    } else if (auto* ve = dynamic_cast<VariableExpr*>(expr)) {
        auto sym = symbolTable.resolve(ve->name);
        if (!sym) throw std::runtime_error(errorWithLoc("Undefined variable: " + ve->name, ve->loc));
        ve->evaluatedType = sym->type;
    } else if (auto* be = dynamic_cast<BinaryExpr*>(expr)) {
        visitExpr(be->left.get());
        visitExpr(be->right.get());
        if (be->op == "=") {
            // L-value check
            bool isLValue = false;
            if (dynamic_cast<VariableExpr*>(be->left.get())) isLValue = true;
            else if (dynamic_cast<MemberAccessExpr*>(be->left.get())) isLValue = true;
            else if (dynamic_cast<IndexExpr*>(be->left.get())) isLValue = true;
            else if (auto* ue = dynamic_cast<UnaryExpr*>(be->left.get())) {
                if (ue->op == "*") isLValue = true;
            }

            if (!isLValue) {
                throw std::runtime_error(errorWithLoc("Left side of assignment is not an L-value", be->loc));
            }

            if (!isAssignable(be->left->evaluatedType, be->right->evaluatedType)) {
                throw std::runtime_error(errorWithLoc("Type mismatch in assignment", be->loc));
            }
            be->evaluatedType = be->left->evaluatedType;
        } else if (be->op == "==" || be->op == "!=" || be->op == "<" || be->op == ">" || be->op == "<=" || be->op == ">=") {
            be->evaluatedType = std::make_shared<ScalarType>(TypeKind::Bool);
        } else {
            // For simplicity, assume arithmetic operators return left type
            be->evaluatedType = be->left->evaluatedType;
        }
    } else if (auto* ue = dynamic_cast<UnaryExpr*>(expr)) {
        visitExpr(ue->expr.get());
        if (ue->op == "&") {
            ue->evaluatedType = std::make_shared<PointerType>(ue->expr->evaluatedType);
        } else if (ue->op == "*") {
            if (ue->expr->evaluatedType->kind != TypeKind::Pointer) {
                throw std::runtime_error(errorWithLoc("Dereferencing non-pointer type", ue->loc));
            }
            ue->evaluatedType = static_cast<PointerType*>(ue->expr->evaluatedType.get())->base;
        } else {
            ue->evaluatedType = ue->expr->evaluatedType;
        }
    } else if (auto* ce = dynamic_cast<CallExpr*>(expr)) {
        auto sym = symbolTable.resolve(ce->funcName);
        if (!sym || !sym->isFunction) throw std::runtime_error(errorWithLoc("Undefined function: " + ce->funcName, ce->loc));
        for (auto& arg : ce->args) visitExpr(arg.get());
        ce->evaluatedType = sym->type;
    } else if (auto* ma = dynamic_cast<MemberAccessExpr*>(expr)) {
        visitExpr(ma->object.get());
        auto objType = ma->object->evaluatedType;
        if (objType->kind == TypeKind::Pointer) {
            objType = static_cast<PointerType*>(objType.get())->base;
        }
        if (objType->kind != TypeKind::Struct) throw std::runtime_error(errorWithLoc("Member access on non-struct type", ma->loc));
        auto structName = static_cast<StructType*>(objType.get())->name;
        if (structs.count(structName) == 0) throw std::runtime_error(errorWithLoc("Undefined struct: " + structName, ma->loc));
        auto* sd = structs[structName];
        bool found = false;
        for (auto& field : sd->fields) {
            if (field.name == ma->member) {
                ma->evaluatedType = field.type;
                found = true;
                break;
            }
        }
        if (!found) throw std::runtime_error(errorWithLoc("Undefined member: " + ma->member, ma->loc));
    } else if (auto* mc = dynamic_cast<MethodCallExpr*>(expr)) {
        visitExpr(mc->object.get());
        auto objType = mc->object->evaluatedType;
        if (objType->kind == TypeKind::Pointer) {
            objType = static_cast<PointerType*>(objType.get())->base;
        }
        if (objType->kind != TypeKind::Struct) throw std::runtime_error(errorWithLoc("Method call on non-struct type", mc->loc));
        auto structName = static_cast<StructType*>(objType.get())->name;
        if (methods[structName].count(mc->methodName)) {
            mc->evaluatedType = methods[structName][mc->methodName]->funcDecl->returnType;
        } else {
            throw std::runtime_error(errorWithLoc("Undefined method: " + mc->methodName, mc->loc));
        }
        for (auto& arg : mc->args) visitExpr(arg.get());
    } else if (auto* ie = dynamic_cast<IndexExpr*>(expr)) {
        visitExpr(ie->array.get());
        visitExpr(ie->index.get());
        if (ie->array->evaluatedType->kind == TypeKind::Array) {
            ie->evaluatedType = static_cast<ArrayType*>(ie->array->evaluatedType.get())->base;
        } else if (ie->array->evaluatedType->kind == TypeKind::Pointer) {
            ie->evaluatedType = static_cast<PointerType*>(ie->array->evaluatedType.get())->base;
        } else {
            throw std::runtime_error(errorWithLoc("Indexing non-array/pointer type", ie->loc));
        }
    } else if (auto* c = dynamic_cast<CastExpr*>(expr)) {
        visitExpr(c->expr.get());
        c->evaluatedType = c->targetType;
    }
}

bool SemanticAnalyzer::isAssignable(std::shared_ptr<Type> target, std::shared_ptr<Type> source) {
    if (target->equals(source.get())) return true;
    if (target->kind == TypeKind::Float && source->kind == TypeKind::Int) return true;
    if (target->kind == TypeKind::String && source->kind == TypeKind::Pointer) {
         auto* pt = static_cast<PointerType*>(source.get());
         if (pt->base->kind == TypeKind::Char) return true;
    }
    if (target->kind == TypeKind::Pointer && source->kind == TypeKind::Pointer) {
        auto* tp = static_cast<PointerType*>(target.get());
        auto* sp = static_cast<PointerType*>(source.get());
        if (tp->base->kind == TypeKind::Void || sp->base->kind == TypeKind::Void) return true;
    }
    return false;
}

} // namespace novus
