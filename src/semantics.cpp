#include "ast.h"
#include "semantics.h"
#include <stdexcept>
#include <sstream>
#include <iostream>
#include <algorithm>

namespace novus {

std::unique_ptr<Expr> CastExpr::clone(const SubstitutionMap& subs) const {
        std::map<std::string, std::shared_ptr<novus::Type>> iCache;
        auto n = std::make_unique<CastExpr>(SemanticAnalyzer::resolveTypeStatic(targetType.get(), subs, {}, iCache), expr->clone(subs));
    n->loc = loc;
    return n;
}

std::unique_ptr<Stmt> VarDeclStmt::clone(const SubstitutionMap& subs) const {
        std::map<std::string, std::shared_ptr<novus::Type>> iCache;
        auto n = std::make_unique<VarDeclStmt>(SemanticAnalyzer::resolveTypeStatic(type.get(), subs, {}, iCache), name, init ? init->clone(subs) : nullptr);
    n->loc = loc;
    return n;
}

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
            if (!sd->typeParams.empty()) {
                genericStructs[sd->name] = sd;
            } else {
                structs[sd->name] = sd;
            }
        } else if (auto* fd = dynamic_cast<FunctionDecl*>(decl.get())) {
            if (!fd->typeParams.empty()) {
                genericFunctions[fd->name] = fd;
            } else {
                symbolTable.define(fd->name, fd->returnType, true);
            }
        } else if (auto* id = dynamic_cast<ImplDecl*>(decl.get())) {
            if (!id->typeParams.empty()) {
                genericImpls[id->structName].push_back(id);
            } else {
                for (auto& md : id->methods) {
                    methods[id->structName][md->funcDecl->name] = md.get();
                }
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
        if (!fd->typeParams.empty()) return; // Skip generic templates
        if (!fd->body) return;
        symbolTable.pushScope();
        currentReturnType = fd->returnType;
        for (auto& param : fd->params) {
            symbolTable.define(param.name, param.type);
        }
        visitStmt(fd->body.get());
        symbolTable.popScope();
    } else if (auto* id = dynamic_cast<ImplDecl*>(decl)) {
        if (!id->typeParams.empty()) return; // Skip generic templates
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
        if (vs->type->kind == TypeKind::GenericInstantiation) {
            auto vt = vs->type.get();
            vs->type = resolveType(vt, {});
        }
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
            if (currentReturnType && !isAssignable(currentReturnType, rs->expr->evaluatedType)) {
                throw std::runtime_error(errorWithLoc("Type mismatch in return statement", rs->loc));
            }
        } else if (currentReturnType && currentReturnType->kind != TypeKind::Void) {
            throw std::runtime_error(errorWithLoc("Return without value in non-void function", rs->loc));
        }
    }
}

std::shared_ptr<novus::Type> SemanticAnalyzer::resolveTypeStatic(novus::Type* type, const SubstitutionMap& substitutions, const std::map<std::string, StructDecl*>& genericStructs, std::map<std::string, std::shared_ptr<novus::Type>>& instantiationCache) {
    if (!type) return nullptr;
    if (auto* scalar = dynamic_cast<ScalarType*>(type)) {
        return std::make_shared<ScalarType>(scalar->kind);
    } else if (auto* ptr = dynamic_cast<PointerType*>(type)) {
        auto res = resolveTypeStatic(ptr->base.get(), substitutions, genericStructs, instantiationCache);
        if (!res) return nullptr;
        return std::make_shared<PointerType>(res);
    } else if (auto* arr = dynamic_cast<ArrayType*>(type)) {
        auto res = resolveTypeStatic(arr->base.get(), substitutions, genericStructs, instantiationCache);
        if (!res) return nullptr;
        return std::make_shared<ArrayType>(res, arr->size);
    } else if (auto* st = dynamic_cast<StructType*>(type)) {
        return std::make_shared<StructType>(st->name);
    } else if (auto* tp = dynamic_cast<TypeParameterType*>(type)) {
        auto it = substitutions.find(tp->name);
        if (it != substitutions.end()) {
            return it->second;
        }
        return std::make_shared<TypeParameterType>(tp->name);
    } else if (auto* gi = dynamic_cast<GenericInstantiationType*>(type)) {
        std::vector<std::shared_ptr<novus::Type>> resolvedArgs;
        for (auto& arg : gi->typeArgs) {
            resolvedArgs.push_back(resolveTypeStatic(arg.get(), substitutions, genericStructs, instantiationCache));
        }
        return std::make_shared<GenericInstantiationType>(gi->baseName, std::move(resolvedArgs));
    }
    return nullptr;
}

std::shared_ptr<novus::Type> SemanticAnalyzer::resolveType(novus::Type* type, const SubstitutionMap& substitutions) {
    auto res = resolveTypeStatic(type, substitutions, genericStructs, instantiationCache);
    if (res && res->kind == TypeKind::GenericInstantiation) {
        auto* gi = static_cast<GenericInstantiationType*>(res.get());
        return instantiateStruct(gi->baseName, gi->typeArgs);
    }
    return res;
}

std::shared_ptr<novus::Type> SemanticAnalyzer::instantiateStruct(const std::string& name, const std::vector<std::shared_ptr<novus::Type>>& args) {
    std::string mangledName = name;
    for (auto& arg : args) {
        mangledName += "_" + arg->toString();
    }

    if (instantiationCache.count(mangledName)) {
        return instantiationCache[mangledName];
    }

    if (structs.count(mangledName)) {
        auto res_existing = std::make_shared<StructType>(mangledName);
        instantiationCache[mangledName] = res_existing;
        return res_existing;
    }

    if (genericStructs.count(name)) {
        // Pre-populate cache to prevent infinite recursion
        auto res_new = std::make_shared<StructType>(mangledName);
        instantiationCache[mangledName] = res_new;

        auto* sd = genericStructs.at(name);
        SubstitutionMap substitutions;
        for (size_t i = 0; i < sd->typeParams.size(); ++i) {
            substitutions[sd->typeParams[i]] = args[i];
        }

        std::vector<StructDecl::Field> specializedFields;
        for (auto& field : sd->fields) {
            auto ft = field.type.get();
            auto resType = resolveType(ft, substitutions);
            if (!resType) throw std::runtime_error("Failed to resolve field type: " + field.name);
            specializedFields.push_back({resType, field.name});
        }

        auto specializedSd = std::make_unique<StructDecl>(mangledName, std::move(specializedFields));
        auto* specializedSdPtr = specializedSd.get();
        structs[mangledName] = specializedSdPtr;
        specializedDecls.push_back(std::move(specializedSd));

        if (genericImpls.count(name)) {
            auto& impls = genericImpls.at(name);
            for (auto* id : impls) {
                SubstitutionMap implSubstitutions;
                for (size_t i = 0; i < id->typeParams.size(); ++i) {
                    implSubstitutions[id->typeParams[i]] = args[i];
                }

                for (auto& md : id->methods) {
                    if (!md->funcDecl) { continue; }

                    std::vector<FunctionDecl::Param> specializedParams;
                    for (auto& p : md->funcDecl->params) {
                        specializedParams.push_back({resolveType(p.type.get(), implSubstitutions), p.name});
                    }
                    auto specializedReturnType = resolveType(md->funcDecl->returnType.get(), implSubstitutions);

                    std::unique_ptr<BlockStmt> specializedBody = nullptr;
                    if (md->funcDecl->body) {
                        auto cloned = md->funcDecl->body->clone(implSubstitutions);
                        specializedBody.reset(static_cast<BlockStmt*>(cloned.release()));
                    }

                    auto specializedFd = std::make_unique<FunctionDecl>(
                        specializedReturnType, md->funcDecl->name, std::move(specializedParams),
                        std::move(specializedBody)
                    );

                    auto specializedMd = std::make_unique<MethodDecl>(mangledName, std::move(specializedFd));
                    methods[mangledName][md->funcDecl->name] = specializedMd.get();

                    // Store the specialized method to keep it alive
                    specializedDecls.push_back(std::move(specializedMd));

                    // Analyze specialized method
                    auto* analyzedMd = static_cast<MethodDecl*>(specializedDecls.back().get());
                    symbolTable.pushScope();
                    auto oldRet = currentReturnType;
                    currentReturnType = specializedReturnType;
                    auto selfType = std::make_shared<PointerType>(std::make_shared<StructType>(mangledName));
                    symbolTable.define("self", selfType);
                    for (auto& param : analyzedMd->funcDecl->params) {
                        symbolTable.define(param.name, param.type);
                    }
                    if (analyzedMd->funcDecl->body) {
                        visitStmt(analyzedMd->funcDecl->body.get());
                    }
                    currentReturnType = oldRet;
                    symbolTable.popScope();
                }
            }
        }

        return res_new;
    }

    throw std::runtime_error("Undefined generic struct: " + name);
}

void SemanticAnalyzer::visitExpr(Expr* expr) {
    if (auto* il = dynamic_cast<IntLiteral*>(expr)) {
        il->evaluatedType = std::make_shared<ScalarType>(TypeKind::Int64);
    } else if (auto* fl = dynamic_cast<FloatLiteral*>(expr)) {
        fl->evaluatedType = std::make_shared<ScalarType>(TypeKind::Float64);
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
        if (objType && objType->kind == TypeKind::GenericInstantiation) {
             objType = resolveType(objType.get(), {});
        }
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
        if (c->targetType->kind == TypeKind::GenericInstantiation) {
            c->targetType = resolveType(c->targetType.get(), {});
        }
        visitExpr(c->expr.get());
        c->evaluatedType = c->targetType;
    }
}

bool SemanticAnalyzer::isAssignable(std::shared_ptr<Type> target, std::shared_ptr<Type> source) {
    if (target->equals(source.get())) return true;

    // Integer types are mutually assignable
    bool isTargetInt = (target->kind == TypeKind::Int || target->kind == TypeKind::Int64 || target->kind == TypeKind::Int32 || target->kind == TypeKind::Int16);
    bool isSourceInt = (source->kind == TypeKind::Int || source->kind == TypeKind::Int64 || source->kind == TypeKind::Int32 || source->kind == TypeKind::Int16);
    if (isTargetInt && isSourceInt) return true;

    // Float types are mutually assignable
    bool isTargetFloat = (target->kind == TypeKind::Float || target->kind == TypeKind::Float64 || target->kind == TypeKind::Float32 || target->kind == TypeKind::Float16);
    bool isSourceFloat = (source->kind == TypeKind::Float || source->kind == TypeKind::Float64 || source->kind == TypeKind::Float32 || source->kind == TypeKind::Float16);
    if (isTargetFloat && isSourceFloat) return true;

    // Cross-type promotion (Int to Float)
    if ((target->kind == TypeKind::Float || target->kind == TypeKind::Float64) &&
        (source->kind == TypeKind::Int || source->kind == TypeKind::Int64 || source->kind == TypeKind::Int32 || source->kind == TypeKind::Int16)) return true;
    if (target->kind == TypeKind::Float32 && (source->kind == TypeKind::Int32 || source->kind == TypeKind::Int16)) return true;

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
