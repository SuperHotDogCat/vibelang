#ifndef SEMANTICS_H
#define SEMANTICS_H

#include "ast.h"
#include "common.h"
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

    // Generics support
    std::map<std::string, StructDecl*> genericStructs;
    std::map<std::string, FunctionDecl*> genericFunctions;
    std::map<std::string, std::vector<ImplDecl*>> genericImpls;

    std::map<std::string, std::shared_ptr<Type>> instantiationCache;
    std::vector<std::unique_ptr<Decl>> specializedDecls;

    static std::shared_ptr<Type> resolveTypeStatic(Type* type, const SubstitutionMap& substitutions, const std::map<std::string, StructDecl*>& genericStructs, std::map<std::string, std::shared_ptr<Type>>& instantiationCache);
    std::shared_ptr<Type> resolveType(Type* type, const SubstitutionMap& substitutions);
    std::shared_ptr<Type> instantiateStruct(const std::string& name, const std::vector<std::shared_ptr<Type>>& args);

    void visitDecl(Decl* decl);
    void visitStmt(Stmt* stmt);
    void visitExpr(Expr* expr);

    std::shared_ptr<Type> currentReturnType;

    // Helpers
    bool isAssignable(std::shared_ptr<Type> target, std::shared_ptr<Type> source);
};

} // namespace novus

#endif
