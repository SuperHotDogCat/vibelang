#include "codegen.h"
#include <llvm/Support/raw_ostream.h>
#include <llvm/Support/FileSystem.h>
#include <llvm/IR/Verifier.h>
#include <llvm/IR/DerivedTypes.h>

namespace novus {

CodeGenerator::CodeGenerator() {
    context = std::make_unique<llvm::LLVMContext>();
    module = std::make_unique<llvm::Module>("novus", *context);
    builder = std::make_unique<llvm::IRBuilder<>>(*context);
}

void CodeGenerator::generate(Program* program) {
    // Declare common libc functions
    if (!module->getFunction("malloc")) {
        auto* mallocTy = llvm::FunctionType::get(builder->getPtrTy(), {builder->getInt64Ty()}, false);
        llvm::Function::Create(mallocTy, llvm::Function::ExternalLinkage, "malloc", *module);
    }
    if (!module->getFunction("free")) {
        auto* freeTy = llvm::FunctionType::get(builder->getVoidTy(), {builder->getPtrTy()}, false);
        llvm::Function::Create(freeTy, llvm::Function::ExternalLinkage, "free", *module);
    }
    if (!module->getFunction("printf")) {
        auto* printfTy = llvm::FunctionType::get(builder->getInt32Ty(), {builder->getPtrTy()}, true);
        llvm::Function::Create(printfTy, llvm::Function::ExternalLinkage, "printf", *module);
    }

    // First pass: declare structs
    for (auto& decl : program->decls) {
        if (auto* sd = dynamic_cast<StructDecl*>(decl.get())) {
            if (structTypes.count(sd->name)) continue;
            std::vector<llvm::Type*> fields;
            for (int i = 0; i < sd->fields.size(); ++i) {
                fields.push_back(getLLVMType(sd->fields[i].type.get()));
                structFieldIndices[sd->name][sd->fields[i].name] = i;
            }
            auto* st = llvm::StructType::create(*context, fields, sd->name);
            structTypes[sd->name] = st;
        }
    }

    // Second pass: declare functions
    for (auto& decl : program->decls) {
        if (auto* fd = dynamic_cast<FunctionDecl*>(decl.get())) {
            if (module->getFunction(fd->name)) {
                continue;
            }
            std::vector<llvm::Type*> argTypes;
            for (auto& param : fd->params) {
                argTypes.push_back(getLLVMType(param.type.get()));
            }
            auto* ft = llvm::FunctionType::get(getLLVMType(fd->returnType.get()), argTypes, false);
            llvm::Function::Create(ft, llvm::Function::ExternalLinkage, fd->name, *module);
        } else if (auto* id = dynamic_cast<ImplDecl*>(decl.get())) {
            for (auto& md : id->methods) {
                std::string mangledName = id->structName + "_" + md->funcDecl->name;
                if (module->getFunction(mangledName)) continue;
                std::vector<llvm::Type*> argTypes;
                // 'self' parameter
                argTypes.push_back(builder->getPtrTy());
                for (auto& param : md->funcDecl->params) {
                    argTypes.push_back(getLLVMType(param.type.get()));
                }
                auto* ft = llvm::FunctionType::get(getLLVMType(md->funcDecl->returnType.get()), argTypes, false);
                llvm::Function::Create(ft, llvm::Function::ExternalLinkage, mangledName, *module);
            }
        }
    }

    // Third pass: generate code
    for (auto& decl : program->decls) {
        codegenDecl(decl.get());
    }
}

llvm::Type* CodeGenerator::getLLVMType(Type* type) {
    switch (type->kind) {
        case TypeKind::Void: return builder->getVoidTy();
        case TypeKind::Int: return builder->getInt64Ty();
        case TypeKind::Float: return builder->getDoubleTy();
        case TypeKind::Bool: return builder->getInt1Ty();
        case TypeKind::Char: return builder->getInt8Ty();
        case TypeKind::String: return builder->getPtrTy();
        case TypeKind::Pointer: {
            return builder->getPtrTy();
        }
        case TypeKind::Array: {
            auto* at = static_cast<ArrayType*>(type);
            return llvm::ArrayType::get(getLLVMType(at->base.get()), at->size);
        }
        case TypeKind::Struct: {
            auto* st = static_cast<StructType*>(type);
            return structTypes[st->name];
        }
        default: return builder->getVoidTy();
    }
}

void CodeGenerator::codegenDecl(Decl* decl) {
    if (auto* fd = dynamic_cast<FunctionDecl*>(decl)) {
        if (!fd->body) return; // External function
        auto* func = module->getFunction(fd->name);
        currentFunction = func;
        auto* bb = llvm::BasicBlock::Create(*context, "entry", func);
        builder->SetInsertPoint(bb);

        namedValues.clear();
        int idx = 0;
        for (auto& arg : func->args()) {
            arg.setName(fd->params[idx].name);
            auto* alloca = builder->CreateAlloca(arg.getType(), nullptr, arg.getName());
            builder->CreateStore(&arg, alloca);
            namedValues[fd->params[idx].name] = alloca;
            idx++;
        }

        codegenStmt(fd->body.get());
        auto* lastBB = builder->GetInsertBlock();
        if (!lastBB->getTerminator()) {
             if (fd->returnType->kind == TypeKind::Int) builder->CreateRet(builder->getInt64(0));
             else if (fd->returnType->kind == TypeKind::Float) builder->CreateRet(llvm::ConstantFP::get(*context, llvm::APFloat(0.0)));
             else if (fd->returnType->kind == TypeKind::Bool) builder->CreateRet(builder->getInt1(false));
             else if (fd->returnType->kind == TypeKind::Pointer || fd->returnType->kind == TypeKind::String) builder->CreateRet(llvm::ConstantPointerNull::get(builder->getPtrTy()));
             else if (fd->returnType->kind == TypeKind::Void) builder->CreateRetVoid();
        }
        llvm::verifyFunction(*func);
    } else if (auto* id = dynamic_cast<ImplDecl*>(decl)) {
        for (auto& md : id->methods) {
            std::string mangledName = id->structName + "_" + md->funcDecl->name;
            auto* func = module->getFunction(mangledName);
            currentFunction = func;
            auto* bb = llvm::BasicBlock::Create(*context, "entry", func);
            builder->SetInsertPoint(bb);

            namedValues.clear();
            auto& selfArg = *func->arg_begin();
            selfArg.setName("self");
            auto* selfAlloca = builder->CreateAlloca(selfArg.getType(), nullptr, "self");
            builder->CreateStore(&selfArg, selfAlloca);
            namedValues["self"] = selfAlloca;

            int idx = 0;
            for (auto it = func->arg_begin() + 1; it != func->arg_end(); ++it) {
                auto& arg = *it;
                arg.setName(md->funcDecl->params[idx].name);
                auto* alloca = builder->CreateAlloca(arg.getType(), nullptr, arg.getName());
                builder->CreateStore(&arg, alloca);
                namedValues[md->funcDecl->params[idx].name] = alloca;
                idx++;
            }

            codegenStmt(md->funcDecl->body.get());
            auto* mlastBB = builder->GetInsertBlock();
            if (!mlastBB->getTerminator()) {
                 if (md->funcDecl->returnType->kind == TypeKind::Int) builder->CreateRet(builder->getInt64(0));
                 else if (md->funcDecl->returnType->kind == TypeKind::Float) builder->CreateRet(llvm::ConstantFP::get(*context, llvm::APFloat(0.0)));
                 else if (md->funcDecl->returnType->kind == TypeKind::Bool) builder->CreateRet(builder->getInt1(false));
                 else if (md->funcDecl->returnType->kind == TypeKind::Pointer || md->funcDecl->returnType->kind == TypeKind::String) builder->CreateRet(llvm::ConstantPointerNull::get(builder->getPtrTy()));
                 else if (md->funcDecl->returnType->kind == TypeKind::Void) builder->CreateRetVoid();
            }
            llvm::verifyFunction(*func);
        }
    }
}

void CodeGenerator::codegenStmt(Stmt* stmt) {
    if (auto* bs = dynamic_cast<BlockStmt*>(stmt)) {
        for (auto& s : bs->stmts) {
            codegenStmt(s.get());
        }
    } else if (auto* vs = dynamic_cast<VarDeclStmt*>(stmt)) {
        auto* type = getLLVMType(vs->type.get());
        auto* alloca = builder->CreateAlloca(type, nullptr, vs->name);
        if (vs->type->kind == TypeKind::Int || vs->type->kind == TypeKind::Float || vs->type->kind == TypeKind::Pointer || vs->type->kind == TypeKind::String) {
             alloca->setAlignment(llvm::Align(8));
        }
        if (vs->init) {
            auto* val = codegenExpr(vs->init.get());
            builder->CreateStore(val, alloca);
        }
        namedValues[vs->name] = alloca;
    } else if (auto* es = dynamic_cast<ExprStmt*>(stmt)) {
        codegenExpr(es->expr.get());
    } else if (auto* rs = dynamic_cast<ReturnStmt*>(stmt)) {
        if (rs->expr) {
            auto* val = codegenExpr(rs->expr.get());
            builder->CreateRet(val);
        } else {
            builder->CreateRetVoid();
        }
    } else if (auto* is = dynamic_cast<IfStmt*>(stmt)) {
        auto* cond = codegenExpr(is->condition.get());
        auto* thenBB = llvm::BasicBlock::Create(*context, "then", currentFunction);
        auto* elseBB = llvm::BasicBlock::Create(*context, "else");
        auto* mergeBB = llvm::BasicBlock::Create(*context, "ifcont");

        builder->CreateCondBr(cond, thenBB, is->elseStmt ? elseBB : mergeBB);

        builder->SetInsertPoint(thenBB);
        codegenStmt(is->thenStmt.get());
        if (!builder->GetInsertBlock()->getTerminator()) builder->CreateBr(mergeBB);

        if (is->elseStmt) {
            currentFunction->insert(currentFunction->end(), elseBB);
            builder->SetInsertPoint(elseBB);
            codegenStmt(is->elseStmt.get());
            if (!builder->GetInsertBlock()->getTerminator()) builder->CreateBr(mergeBB);
        } else {
            delete elseBB;
        }
        currentFunction->insert(currentFunction->end(), mergeBB);
        builder->SetInsertPoint(mergeBB);
        if (mergeBB->use_empty()) {
            mergeBB->eraseFromParent();
        }
    } else if (auto* ws = dynamic_cast<WhileStmt*>(stmt)) {
        auto* condBB = llvm::BasicBlock::Create(*context, "whilecond", currentFunction);
        auto* bodyBB = llvm::BasicBlock::Create(*context, "whilebody", currentFunction);
        auto* afterBB = llvm::BasicBlock::Create(*context, "whileafter", currentFunction);

        builder->CreateBr(condBB);
        builder->SetInsertPoint(condBB);
        auto* cond = codegenExpr(ws->condition.get());
        builder->CreateCondBr(cond, bodyBB, afterBB);

        builder->SetInsertPoint(bodyBB);
        codegenStmt(ws->body.get());
        builder->CreateBr(condBB);

        builder->SetInsertPoint(afterBB);
    }
}

llvm::Value* CodeGenerator::codegenExpr(Expr* expr) {
    if (auto* il = dynamic_cast<IntLiteral*>(expr)) {
        return builder->getInt64(il->value);
    } else if (auto* fl = dynamic_cast<FloatLiteral*>(expr)) {
        return llvm::ConstantFP::get(*context, llvm::APFloat(fl->value));
    } else if (auto* bl = dynamic_cast<BoolLiteral*>(expr)) {
        return builder->getInt1(bl->value);
    } else if (auto* sl = dynamic_cast<StringLiteral*>(expr)) {
        return builder->CreateGlobalStringPtr(sl->value);
    } else if (auto* ve = dynamic_cast<VariableExpr*>(expr)) {
        auto* v = namedValues[ve->name];
        return builder->CreateLoad(getLLVMType(ve->evaluatedType.get()), v, ve->name);
    } else if (auto* be = dynamic_cast<BinaryExpr*>(expr)) {
        if (be->op == "=") {
            llvm::Value* ptr = nullptr;
            if (auto* vve = dynamic_cast<VariableExpr*>(be->left.get())) {
                ptr = namedValues[vve->name];
            } else if (auto* ma = dynamic_cast<MemberAccessExpr*>(be->left.get())) {
                auto* obj = codegenExpr(ma->object.get());
                llvm::Value* structPtr = obj;
                auto structType = ma->object->evaluatedType;
                if (structType->kind == TypeKind::Pointer) structType = static_cast<PointerType*>(structType.get())->base;
                auto structName = static_cast<StructType*>(structType.get())->name;
                int idx = structFieldIndices[structName][ma->member];
                ptr = builder->CreateStructGEP(structTypes[structName], structPtr, idx);
            } else if (auto* ie = dynamic_cast<IndexExpr*>(be->left.get())) {
                auto* arr = codegenExpr(ie->array.get());
                auto* idx = codegenExpr(ie->index.get());
                if (ie->array->evaluatedType->kind == TypeKind::Array) {
                     ptr = builder->CreateInBoundsGEP(getLLVMType(ie->array->evaluatedType.get()), namedValues[static_cast<VariableExpr*>(ie->array.get())->name], {builder->getInt64(0), idx});
                } else {
                     ptr = builder->CreateInBoundsGEP(getLLVMType(static_cast<PointerType*>(ie->array->evaluatedType.get())->base.get()), arr, idx);
                }
            }
            auto* val = codegenExpr(be->right.get());
            builder->CreateStore(val, ptr);
            return val;
        }
        auto* l = codegenExpr(be->left.get());
        auto* r = codegenExpr(be->right.get());
        bool isFloat = be->left->evaluatedType->kind == TypeKind::Float;
        if (be->op == "+") return isFloat ? builder->CreateFAdd(l, r) : builder->CreateAdd(l, r);
        if (be->op == "-") return isFloat ? builder->CreateFSub(l, r) : builder->CreateSub(l, r);
        if (be->op == "*") return isFloat ? builder->CreateFMul(l, r) : builder->CreateMul(l, r);
        if (be->op == "/") return isFloat ? builder->CreateFDiv(l, r) : builder->CreateSDiv(l, r);
        if (be->op == "%") return builder->CreateSRem(l, r);
        if (be->op == "<<") return builder->CreateShl(l, r);
        if (be->op == ">>") return builder->CreateAShr(l, r);
        if (be->op == "==") return isFloat ? builder->CreateFCmpOEQ(l, r) : builder->CreateICmpEQ(l, r);
        if (be->op == "!=") return isFloat ? builder->CreateFCmpONE(l, r) : builder->CreateICmpNE(l, r);
        if (be->op == "<") return isFloat ? builder->CreateFCmpOLT(l, r) : builder->CreateICmpSLT(l, r);
        if (be->op == ">") return isFloat ? builder->CreateFCmpOGT(l, r) : builder->CreateICmpSGT(l, r);
        if (be->op == "<=") return isFloat ? builder->CreateFCmpOLE(l, r) : builder->CreateICmpSLE(l, r);
        if (be->op == ">=") return isFloat ? builder->CreateFCmpOGE(l, r) : builder->CreateICmpSGE(l, r);
        return nullptr;
    } else if (auto* ue = dynamic_cast<UnaryExpr*>(expr)) {
        if (ue->op == "&") {
            if (auto* ve = dynamic_cast<VariableExpr*>(ue->expr.get())) {
                return namedValues[ve->name];
            }
        } else if (ue->op == "*") {
            auto* ptr = codegenExpr(ue->expr.get());
            return builder->CreateLoad(getLLVMType(ue->evaluatedType.get()), ptr);
        }
        auto* val = codegenExpr(ue->expr.get());
        if (ue->op == "-") return ue->evaluatedType->kind == TypeKind::Float ? builder->CreateFNeg(val) : builder->CreateNeg(val);
        if (ue->op == "!") return builder->CreateNot(val);
        return nullptr;
    } else if (auto* ce = dynamic_cast<CallExpr*>(expr)) {
        auto* func = module->getFunction(ce->funcName);
        std::vector<llvm::Value*> args;
        for (auto& arg : ce->args) args.push_back(codegenExpr(arg.get()));
        return builder->CreateCall(func, args);
    } else if (auto* ma = dynamic_cast<MemberAccessExpr*>(expr)) {
        auto* obj = codegenExpr(ma->object.get());
        auto structType = ma->object->evaluatedType;
        if (structType->kind == TypeKind::Pointer) structType = static_cast<PointerType*>(structType.get())->base;
        auto structName = static_cast<StructType*>(structType.get())->name;
        int idx = structFieldIndices[structName][ma->member];
        auto* ptr = builder->CreateStructGEP(structTypes[structName], obj, idx);
        return builder->CreateLoad(getLLVMType(ma->evaluatedType.get()), ptr, ma->member);
    } else if (auto* mc = dynamic_cast<MethodCallExpr*>(expr)) {
        auto structType = mc->object->evaluatedType;
        bool isPointer = structType->kind == TypeKind::Pointer;
        if (isPointer) structType = static_cast<PointerType*>(structType.get())->base;
        auto structName = static_cast<StructType*>(structType.get())->name;
        std::string mangledName = structName + "_" + mc->methodName;
        auto* func = module->getFunction(mangledName);
        std::vector<llvm::Value*> args;

        llvm::Value* selfPtr = nullptr;
        if (auto* ve = dynamic_cast<VariableExpr*>(mc->object.get())) {
            selfPtr = namedValues[ve->name];
        } else if (auto* ma = dynamic_cast<MemberAccessExpr*>(mc->object.get())) {
            auto* obj = codegenExpr(ma->object.get());
            auto stype = ma->object->evaluatedType;
            if (stype->kind == TypeKind::Pointer) stype = static_cast<PointerType*>(stype.get())->base;
            auto sname = static_cast<StructType*>(stype.get())->name;
            int idx = structFieldIndices[sname][ma->member];
            selfPtr = builder->CreateStructGEP(structTypes[sname], obj, idx);
        } else {
            selfPtr = codegenExpr(mc->object.get());
        }

        args.push_back(selfPtr);
        for (auto& arg : mc->args) args.push_back(codegenExpr(arg.get()));
        return builder->CreateCall(func, args);
    } else if (auto* ie = dynamic_cast<IndexExpr*>(expr)) {
        auto* arr = codegenExpr(ie->array.get());
        auto* idx = codegenExpr(ie->index.get());
        llvm::Value* ptr;
        if (ie->array->evaluatedType->kind == TypeKind::Array) {
             ptr = builder->CreateInBoundsGEP(getLLVMType(ie->array->evaluatedType.get()), namedValues[static_cast<VariableExpr*>(ie->array.get())->name], {builder->getInt64(0), idx});
        } else {
             ptr = builder->CreateInBoundsGEP(getLLVMType(static_cast<PointerType*>(ie->array->evaluatedType.get())->base.get()), arr, idx);
        }
        return builder->CreateLoad(getLLVMType(ie->evaluatedType.get()), ptr);
    } else if (auto* c = dynamic_cast<CastExpr*>(expr)) {
        auto* val = codegenExpr(c->expr.get());
        auto* targetTy = getLLVMType(c->targetType.get());
        if (val->getType()->isPointerTy() && targetTy->isIntegerTy()) return builder->CreatePtrToInt(val, targetTy);
        if (val->getType()->isIntegerTy() && targetTy->isPointerTy()) return builder->CreateIntToPtr(val, targetTy);
        return builder->CreateBitCast(val, targetTy);
    }
    return nullptr;
}

void CodeGenerator::print() {
    module->print(llvm::outs(), nullptr);
}

void CodeGenerator::save(const std::string& filename) {
    std::error_code ec;
    llvm::raw_fd_ostream dest(filename, ec, llvm::sys::fs::OF_None);
    module->print(dest, nullptr);
}

} // namespace novus
