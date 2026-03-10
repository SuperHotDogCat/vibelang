#ifndef SEMANTICS_H
#define SEMANTICS_H

#include "ast.h"
#include <map>
#include <string>
#include <vector>
#include <memory>

namespace novus {

class SymbolTable {
public:
    struct Symbol {
        std::shared_ptr<Type> type;
        bool isFunction;
    };

    void pushScope();
    void popScope();
    void define(const std::string& name, std::shared_ptr<Type> type, bool isFunction = false);
    Symbol* resolve(const std::string& name);

private:
    std::vector<std::map<std::string, Symbol>> scopes;
};

class SemanticAnalyzer {
public:
    void analyze(Program* program);
    void collectDecls(Program* program);
    void analyzeOnly(Program* program);

    SymbolTable symbolTable;
    std::map<std::string, StructDecl*> structs;
    std::map<std::string, std::map<std::string, MethodDecl*>> methods;

    void visitDecl(Decl* decl);
    void visitStmt(Stmt* stmt);
    void visitExpr(Expr* expr);

    std::shared_ptr<Type> currentReturnType;

    // Helpers
    bool isAssignable(std::shared_ptr<Type> target, std::shared_ptr<Type> source);
};

} // namespace novus

#endif
