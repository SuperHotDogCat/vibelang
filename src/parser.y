%{
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "ast.h"
#include "parser.tab.hpp"

extern int yylex();
extern int yylineno;
void yyerror(const char *s);

std::unique_ptr<novus::Program> root;

using namespace novus;

template<typename T>
T* setLoc(T* node, const YYLTYPE& loc) {
    if (node) {
        node->loc.line = loc.first_line;
        node->loc.col = loc.first_column;
    }
    return node;
}
%}

%locations

%union {
    long long ival;
    double fval;
    std::string *sval;
    novus::Expr *expr;
    novus::Stmt *stmt;
    novus::Decl *decl;
    novus::Type *type;
    std::vector<std::unique_ptr<novus::Expr>> *expr_list;
    std::vector<std::unique_ptr<novus::Stmt>> *stmt_list;
    std::vector<std::unique_ptr<novus::Decl>> *decl_list;
    std::vector<novus::FunctionDecl::Param> *param_list;
    std::vector<novus::StructDecl::Field> *field_list;
}

%token <ival> IVAL
%token <fval> FVAL
%token <sval> SVAL IDENT
%token IMPORT STRUCT IMPL FN VAR IF ELSE WHILE RETURN TRUE FALSE AS
%token VOID INT FLOAT BOOL CHAR STRING
%token SHL SHR EQ NE LE GE ARROW

%type <expr> expr primary_expr postfix_expr unary_expr cast_expr mul_expr add_expr shift_expr relational_expr equality_expr
%type <stmt> stmt expr_stmt var_decl_stmt block_stmt if_stmt while_stmt return_stmt import_stmt
%type <decl> decl func_decl struct_decl impl_block
%type <type> type base_type
%type <expr_list> arg_list
%type <stmt_list> stmt_list import_list
%type <decl_list> decl_list
%type <param_list> param_list
%type <field_list> field_list

%right '='
%left EQ NE
%left '<' '>' LE GE
%left SHL SHR
%left '+' '-'
%left '*' '/' '%'
%right '!' '&'
%left '.' '[' '('

%%

program:
    import_list decl_list {
        root = std::make_unique<Program>();
        if ($1) {
            for (auto& s : *$1) root->imports.push_back(std::move(s));
            delete $1;
        }
        if ($2) {
            for (auto& d : *$2) root->decls.push_back(std::move(d));
            delete $2;
        }
    }
    ;

import_list:
    /* empty */ { $$ = new std::vector<std::unique_ptr<Stmt>>(); }
    | import_list import_stmt { if ($1 && $2) $1->push_back(std::unique_ptr<Stmt>($2)); $$ = $1; }
    ;

import_stmt:
    IMPORT SVAL ';' { $$ = setLoc(new ImportStmt(*$2), @1); delete $2; }
    ;

decl_list:
    /* empty */ { $$ = new std::vector<std::unique_ptr<Decl>>(); }
    | decl_list decl { if ($1 && $2) $1->push_back(std::unique_ptr<Decl>($2)); $$ = $1; }
    ;

decl:
    func_decl { $$ = $1; }
    | struct_decl { $$ = $1; }
    | impl_block { $$ = $1; }
    ;

func_decl:
    FN IDENT '(' param_list ')' ARROW type block_stmt {
        $$ = setLoc(new FunctionDecl(std::shared_ptr<Type>($7), *$2, std::move(*$4), std::unique_ptr<BlockStmt>(static_cast<BlockStmt*>($8))), @1);
        delete $2; delete $4;
    }
    | FN IDENT '(' param_list ')' ARROW type ';' {
        $$ = setLoc(new FunctionDecl(std::shared_ptr<Type>($7), *$2, std::move(*$4), nullptr), @1);
        delete $2; delete $4;
    }
    ;

param_list:
    /* empty */ { $$ = new std::vector<FunctionDecl::Param>(); }
    | IDENT ':' type { $$ = new std::vector<FunctionDecl::Param>(); $$->push_back({std::shared_ptr<Type>($3), *$1}); delete $1; }
    | param_list ',' IDENT ':' type { if ($1) $1->push_back({std::shared_ptr<Type>($5), *$3}); delete $3; $$ = $1; }
    ;

struct_decl:
    STRUCT IDENT '{' field_list '}' {
        $$ = setLoc(new StructDecl(*$2, std::move(*$4)), @1);
        delete $2; delete $4;
    }
    ;

field_list:
    /* empty */ { $$ = new std::vector<StructDecl::Field>(); }
    | IDENT ':' type ';' { $$ = new std::vector<StructDecl::Field>(); $$->push_back({std::shared_ptr<Type>($3), *$1}); delete $1; }
    | field_list IDENT ':' type ';' { if ($1) $1->push_back({std::shared_ptr<Type>($4), *$2}); delete $2; $$ = $1; }
    ;

impl_block:
    IMPL IDENT '{' decl_list '}' {
        std::vector<std::unique_ptr<MethodDecl>> methods;
        if ($4) {
            for(auto& d : *$4) {
                if (auto* fd = dynamic_cast<FunctionDecl*>(d.release())) {
                    methods.push_back(std::make_unique<MethodDecl>(*$2, std::unique_ptr<FunctionDecl>(fd)));
                }
            }
            delete $4;
        }
        $$ = setLoc(new ImplDecl(*$2, std::move(methods)), @1);
        delete $2;
    }
    ;

type:
    base_type { $$ = $1; }
    | type '*' { $$ = new PointerType(std::shared_ptr<Type>($1)); }
    | type '[' IVAL ']' { $$ = new ArrayType(std::shared_ptr<Type>($1), (int)$3); }
    ;

base_type:
    VOID { $$ = new ScalarType(TypeKind::Void); }
    | INT { $$ = new ScalarType(TypeKind::Int); }
    | FLOAT { $$ = new ScalarType(TypeKind::Float); }
    | BOOL { $$ = new ScalarType(TypeKind::Bool); }
    | CHAR { $$ = new ScalarType(TypeKind::Char); }
    | STRING { $$ = new ScalarType(TypeKind::String); }
    | IDENT { $$ = new StructType(*$1); delete $1; }
    ;

stmt:
    expr_stmt { $$ = $1; }
    | var_decl_stmt { $$ = $1; }
    | block_stmt { $$ = $1; }
    | if_stmt { $$ = $1; }
    | while_stmt { $$ = $1; }
    | return_stmt { $$ = $1; }
    ;

expr_stmt:
    expr ';' { $$ = setLoc(new ExprStmt(std::unique_ptr<Expr>($1)), @1); }
    ;

var_decl_stmt:
    VAR IDENT ':' type ';' { $$ = setLoc(new VarDeclStmt(std::shared_ptr<Type>($4), *$2), @1); delete $2; }
    | VAR IDENT ':' type '=' expr ';' { $$ = setLoc(new VarDeclStmt(std::shared_ptr<Type>($4), *$2, std::unique_ptr<Expr>($6)), @1); delete $2; }
    ;

block_stmt:
    '{' stmt_list '}' { $$ = setLoc(new BlockStmt(std::move(*$2)), @1); delete $2; }
    ;

stmt_list:
    /* empty */ { $$ = new std::vector<std::unique_ptr<Stmt>>(); }
    | stmt_list stmt { if ($1 && $2) $1->push_back(std::unique_ptr<Stmt>($2)); $$ = $1; }
    ;

if_stmt:
    IF '(' expr ')' stmt { $$ = setLoc(new IfStmt(std::unique_ptr<Expr>($3), std::unique_ptr<Stmt>($5)), @1); }
    | IF '(' expr ')' stmt ELSE stmt { $$ = setLoc(new IfStmt(std::unique_ptr<Expr>($3), std::unique_ptr<Stmt>($5), std::unique_ptr<Stmt>($7)), @1); }
    ;

while_stmt:
    WHILE '(' expr ')' stmt { $$ = setLoc(new WhileStmt(std::unique_ptr<Expr>($3), std::unique_ptr<Stmt>($5)), @1); }
    ;

return_stmt:
    RETURN ';' { $$ = setLoc(new ReturnStmt(), @1); }
    | RETURN expr ';' { $$ = setLoc(new ReturnStmt(std::unique_ptr<Expr>($2)), @1); }
    ;

expr:
    equality_expr { $$ = $1; }
    | postfix_expr '=' expr { $$ = setLoc(new BinaryExpr("=", std::unique_ptr<Expr>($1), std::unique_ptr<Expr>($3)), @1); }
    ;

equality_expr:
    relational_expr { $$ = $1; }
    | equality_expr EQ relational_expr { $$ = setLoc(new BinaryExpr("==", std::unique_ptr<Expr>($1), std::unique_ptr<Expr>($3)), @1); }
    | equality_expr NE relational_expr { $$ = setLoc(new BinaryExpr("!=", std::unique_ptr<Expr>($1), std::unique_ptr<Expr>($3)), @1); }
    ;

relational_expr:
    shift_expr { $$ = $1; }
    | relational_expr '<' shift_expr { $$ = setLoc(new BinaryExpr("<", std::unique_ptr<Expr>($1), std::unique_ptr<Expr>($3)), @1); }
    | relational_expr '>' shift_expr { $$ = setLoc(new BinaryExpr(">", std::unique_ptr<Expr>($1), std::unique_ptr<Expr>($3)), @1); }
    | relational_expr LE shift_expr { $$ = setLoc(new BinaryExpr("<=", std::unique_ptr<Expr>($1), std::unique_ptr<Expr>($3)), @1); }
    | relational_expr GE shift_expr { $$ = setLoc(new BinaryExpr(">=", std::unique_ptr<Expr>($1), std::unique_ptr<Expr>($3)), @1); }
    ;

shift_expr:
    add_expr { $$ = $1; }
    | shift_expr SHL add_expr { $$ = setLoc(new BinaryExpr("<<", std::unique_ptr<Expr>($1), std::unique_ptr<Expr>($3)), @1); }
    | shift_expr SHR add_expr { $$ = setLoc(new BinaryExpr(">>", std::unique_ptr<Expr>($1), std::unique_ptr<Expr>($3)), @1); }
    ;

add_expr:
    mul_expr { $$ = $1; }
    | add_expr '+' mul_expr { $$ = setLoc(new BinaryExpr("+", std::unique_ptr<Expr>($1), std::unique_ptr<Expr>($3)), @1); }
    | add_expr '-' mul_expr { $$ = setLoc(new BinaryExpr("-", std::unique_ptr<Expr>($1), std::unique_ptr<Expr>($3)), @1); }
    ;

mul_expr:
    cast_expr { $$ = $1; }
    | mul_expr '*' cast_expr { $$ = setLoc(new BinaryExpr("*", std::unique_ptr<Expr>($1), std::unique_ptr<Expr>($3)), @1); }
    | mul_expr '/' cast_expr { $$ = setLoc(new BinaryExpr("/", std::unique_ptr<Expr>($1), std::unique_ptr<Expr>($3)), @1); }
    | mul_expr '%' cast_expr { $$ = setLoc(new BinaryExpr("%", std::unique_ptr<Expr>($1), std::unique_ptr<Expr>($3)), @1); }
    ;

cast_expr:
    unary_expr { $$ = $1; }
    | unary_expr AS type { $$ = setLoc(new CastExpr(std::shared_ptr<Type>($3), std::unique_ptr<Expr>($1)), @2); }
    ;

unary_expr:
    postfix_expr { $$ = $1; }
    | '-' unary_expr { $$ = setLoc(new UnaryExpr("-", std::unique_ptr<Expr>($2)), @1); }
    | '!' unary_expr { $$ = setLoc(new UnaryExpr("!", std::unique_ptr<Expr>($2)), @1); }
    | '&' unary_expr { $$ = setLoc(new UnaryExpr("&", std::unique_ptr<Expr>($2)), @1); }
    | '*' unary_expr { $$ = setLoc(new UnaryExpr("*", std::unique_ptr<Expr>($2)), @1); }
    ;

postfix_expr:
    primary_expr { $$ = $1; }
    | postfix_expr '.' IDENT { $$ = setLoc(new MemberAccessExpr(std::unique_ptr<Expr>($1), *$3), @2); delete $3; }
    | postfix_expr '(' arg_list ')' {
        if (auto* ve = dynamic_cast<VariableExpr*>($1)) {
            $$ = setLoc(new CallExpr(ve->name, std::move(*$3)), @1);
            delete ve;
        } else if (auto* ma = dynamic_cast<MemberAccessExpr*>($1)) {
            $$ = setLoc(new MethodCallExpr(std::move(ma->object), ma->member, std::move(*$3)), @1);
            delete ma;
        } else {
            yyerror("Invalid call target");
            $$ = $1;
        }
        delete $3;
    }
    | postfix_expr '[' expr ']' { $$ = setLoc(new IndexExpr(std::unique_ptr<Expr>($1), std::unique_ptr<Expr>($3)), @2); }
    ;

arg_list:
    /* empty */ { $$ = new std::vector<std::unique_ptr<Expr>>(); }
    | expr { $$ = new std::vector<std::unique_ptr<Expr>>(); $$->push_back(std::unique_ptr<Expr>($1)); }
    | arg_list ',' expr { if ($1) $1->push_back(std::unique_ptr<Expr>($3)); $$ = $1; }
    ;

primary_expr:
    IDENT { $$ = setLoc(new VariableExpr(*$1), @1); delete $1; }
    | IVAL { $$ = setLoc(new IntLiteral($1), @1); }
    | FVAL { $$ = setLoc(new FloatLiteral($1), @1); }
    | SVAL { $$ = setLoc(new StringLiteral(*$1), @1); delete $1; }
    | TRUE { $$ = setLoc(new BoolLiteral(true), @1); }
    | FALSE { $$ = setLoc(new BoolLiteral(false), @1); }
    | '(' expr ')' { $$ = $2; }
    ;

%%

void yyerror(const char *s) {
    std::cerr << "Parse error: " << s << " at line " << yylineno << std::endl;
}
