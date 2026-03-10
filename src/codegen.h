#ifndef CODEGEN_H
#define CODEGEN_H

#include "ast.h"
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Value.h>
#include <map>
#include <string>

namespace novus {

class CodeGenerator {
public:
    CodeGenerator();
    void generate(Program* program);
    void print();
    void save(const std::string& filename);

private:
    std::unique_ptr<llvm::LLVMContext> context;
    std::unique_ptr<llvm::Module> module;
    std::unique_ptr<llvm::IRBuilder<>> builder;

    std::map<std::string, llvm::Value*> namedValues;
    std::map<std::string, llvm::StructType*> structTypes;
    std::map<std::string, std::map<std::string, int>> structFieldIndices;

    llvm::Type* getLLVMType(Type* type);
    llvm::Value* codegen(Node* node);
    llvm::Value* codegenExpr(Expr* expr);
    void codegenStmt(Stmt* stmt);
    void codegenDecl(Decl* decl);

    llvm::Function* currentFunction;
};

} // namespace novus

#endif
