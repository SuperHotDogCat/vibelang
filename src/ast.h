#ifndef AST_H
#define AST_H

#include <string>
#include <vector>
#include <memory>
#include <iostream>

namespace novus {

enum class TypeKind {
    Void,
    Int,
    Float,
    Bool,
    Char,
    String,
    Pointer,
    Array,
    Struct,
    Function
};

class Type {
public:
    TypeKind kind;
    Type(TypeKind k) : kind(k) {}
    virtual ~Type() = default;
    virtual std::string toString() const = 0;
    virtual bool equals(const Type* other) const = 0;
};

class ScalarType : public Type {
public:
    ScalarType(TypeKind k) : Type(k) {}
    std::string toString() const override {
        switch (kind) {
            case TypeKind::Void: return "void";
            case TypeKind::Int: return "int";
            case TypeKind::Float: return "float";
            case TypeKind::Bool: return "bool";
            case TypeKind::Char: return "char";
            case TypeKind::String: return "string";
            default: return "unknown";
        }
    }
    bool equals(const Type* other) const override {
        return other->kind == kind;
    }
};

class PointerType : public Type {
public:
    std::shared_ptr<Type> base;
    PointerType(std::shared_ptr<Type> b) : Type(TypeKind::Pointer), base(b) {}
    std::string toString() const override {
        return base->toString() + "*";
    }
    bool equals(const Type* other) const override {
        if (other->kind != TypeKind::Pointer) return false;
        return base->equals(static_cast<const PointerType*>(other)->base.get());
    }
};

class ArrayType : public Type {
public:
    std::shared_ptr<Type> base;
    int size;
    ArrayType(std::shared_ptr<Type> b, int s) : Type(TypeKind::Array), base(b), size(s) {}
    std::string toString() const override {
        return base->toString() + "[" + std::to_string(size) + "]";
    }
    bool equals(const Type* other) const override {
        if (other->kind != TypeKind::Array) return false;
        auto* o = static_cast<const ArrayType*>(other);
        return size == o->size && base->equals(o->base.get());
    }
};

class StructType : public Type {
public:
    std::string name;
    StructType(const std::string& n) : Type(TypeKind::Struct), name(n) {}
    std::string toString() const override {
        return "struct " + name;
    }
    bool equals(const Type* other) const override {
        if (other->kind != TypeKind::Struct) return false;
        return name == static_cast<const StructType*>(other)->name;
    }
};

// AST Nodes

struct Location {
    int line;
    int col;
};

class Node {
public:
    Location loc;
    virtual ~Node() = default;
};

class Expr : public Node {
public:
    std::shared_ptr<Type> evaluatedType;
};

class IntLiteral : public Expr {
public:
    long long value;
    IntLiteral(long long v) : value(v) {}
};

class FloatLiteral : public Expr {
public:
    double value;
    FloatLiteral(double v) : value(v) {}
};

class BoolLiteral : public Expr {
public:
    bool value;
    BoolLiteral(bool v) : value(v) {}
};

class StringLiteral : public Expr {
public:
    std::string value;
    StringLiteral(const std::string& v) : value(v) {}
};

class VariableExpr : public Expr {
public:
    std::string name;
    VariableExpr(const std::string& n) : name(n) {}
};

class BinaryExpr : public Expr {
public:
    std::string op;
    std::unique_ptr<Expr> left;
    std::unique_ptr<Expr> right;
    BinaryExpr(const std::string& o, std::unique_ptr<Expr> l, std::unique_ptr<Expr> r)
        : op(o), left(std::move(l)), right(std::move(r)) {}
};

class UnaryExpr : public Expr {
public:
    std::string op;
    std::unique_ptr<Expr> expr;
    UnaryExpr(const std::string& o, std::unique_ptr<Expr> e)
        : op(o), expr(std::move(e)) {}
};

class CallExpr : public Expr {
public:
    std::string funcName;
    std::vector<std::unique_ptr<Expr>> args;
    CallExpr(const std::string& n, std::vector<std::unique_ptr<Expr>> a)
        : funcName(n), args(std::move(a)) {}
};

class MemberAccessExpr : public Expr {
public:
    std::unique_ptr<Expr> object;
    std::string member;
    MemberAccessExpr(std::unique_ptr<Expr> o, const std::string& m)
        : object(std::move(o)), member(m) {}
};

class MethodCallExpr : public Expr {
public:
    std::unique_ptr<Expr> object;
    std::string methodName;
    std::vector<std::unique_ptr<Expr>> args;
    MethodCallExpr(std::unique_ptr<Expr> o, const std::string& m, std::vector<std::unique_ptr<Expr>> a)
        : object(std::move(o)), methodName(m), args(std::move(a)) {}
};

class IndexExpr : public Expr {
public:
    std::unique_ptr<Expr> array;
    std::unique_ptr<Expr> index;
    IndexExpr(std::unique_ptr<Expr> a, std::unique_ptr<Expr> i)
        : array(std::move(a)), index(std::move(i)) {}
};

class CastExpr : public Expr {
public:
    std::shared_ptr<Type> targetType;
    std::unique_ptr<Expr> expr;
    CastExpr(std::shared_ptr<Type> t, std::unique_ptr<Expr> e)
        : targetType(t), expr(std::move(e)) {}
};

class Stmt : public Node {};

class ExprStmt : public Stmt {
public:
    std::unique_ptr<Expr> expr;
    ExprStmt(std::unique_ptr<Expr> e) : expr(std::move(e)) {}
};

class VarDeclStmt : public Stmt {
public:
    std::shared_ptr<Type> type;
    std::string name;
    std::unique_ptr<Expr> init;
    VarDeclStmt(std::shared_ptr<Type> t, const std::string& n, std::unique_ptr<Expr> i = nullptr)
        : type(t), name(n), init(std::move(i)) {}
};

class BlockStmt : public Stmt {
public:
    std::vector<std::unique_ptr<Stmt>> stmts;
    BlockStmt(std::vector<std::unique_ptr<Stmt>> s) : stmts(std::move(s)) {}
};

class IfStmt : public Stmt {
public:
    std::unique_ptr<Expr> condition;
    std::unique_ptr<Stmt> thenStmt;
    std::unique_ptr<Stmt> elseStmt;
    IfStmt(std::unique_ptr<Expr> c, std::unique_ptr<Stmt> t, std::unique_ptr<Stmt> e = nullptr)
        : condition(std::move(c)), thenStmt(std::move(t)), elseStmt(std::move(e)) {}
};

class WhileStmt : public Stmt {
public:
    std::unique_ptr<Expr> condition;
    std::unique_ptr<Stmt> body;
    WhileStmt(std::unique_ptr<Expr> c, std::unique_ptr<Stmt> b)
        : condition(std::move(c)), body(std::move(b)) {}
};

class ReturnStmt : public Stmt {
public:
    std::unique_ptr<Expr> expr;
    ReturnStmt(std::unique_ptr<Expr> e = nullptr) : expr(std::move(e)) {}
};

class ImportStmt : public Stmt {
public:
    std::string path;
    ImportStmt(const std::string& p) : path(p) {}
};

class Decl : public Node {};

class FunctionDecl : public Decl {
public:
    std::shared_ptr<Type> returnType;
    std::string name;
    struct Param {
        std::shared_ptr<Type> type;
        std::string name;
    };
    std::vector<Param> params;
    std::unique_ptr<BlockStmt> body;
    FunctionDecl(std::shared_ptr<Type> r, const std::string& n, std::vector<Param> p, std::unique_ptr<BlockStmt> b)
        : returnType(r), name(n), params(std::move(p)), body(std::move(b)) {}
};

class StructDecl : public Decl {
public:
    std::string name;
    struct Field {
        std::shared_ptr<Type> type;
        std::string name;
    };
    std::vector<Field> fields;
    StructDecl(const std::string& n, std::vector<Field> f) : name(n), fields(std::move(f)) {}
};

class MethodDecl : public Decl {
public:
    std::string structName;
    std::unique_ptr<FunctionDecl> funcDecl;
    MethodDecl(const std::string& sn, std::unique_ptr<FunctionDecl> fd)
        : structName(sn), funcDecl(std::move(fd)) {}
};

class ImplDecl : public Decl {
public:
    std::string structName;
    std::vector<std::unique_ptr<MethodDecl>> methods;
    ImplDecl(const std::string& sn, std::vector<std::unique_ptr<MethodDecl>> m)
        : structName(sn), methods(std::move(m)) {}
};

class Program : public Node {
public:
    std::vector<std::unique_ptr<Stmt>> imports;
    std::vector<std::unique_ptr<Decl>> decls;
};

} // namespace novus

#endif
