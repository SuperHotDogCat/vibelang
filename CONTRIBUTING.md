# Contributing to Novus

Thank you for your interest in contributing to Novus! This document provides an overview of the compiler architecture and instructions for building and testing your changes.

## Compiler Architecture

The Novus compiler follows a standard pipeline:

1.  **Lexer (`src/lexer.l`)**: Tokenizes the source code using Flex.
2.  **Parser (`src/parser.y`)**: Generates the Abstract Syntax Tree (AST) using Bison.
3.  **Semantic Analyzer (`src/semantics.cpp`)**: Performs type checking, scope resolution, and monomorphization of generics.
4.  **IR Generator (`src/codegen.cpp`)**: Generates LLVM IR using the LLVM 18 API.
5.  **Compiler Driver (`src/compiler.cpp`)**: Manages the compilation process, including path resolution and recursive imports.

## Development Environment

### Prerequisites
- LLVM 18 (`llvm-18-dev`)
- Clang 18 (`clang-18`)
- Flex
- Bison
- Make
- G++ (C++17 support)

### Building the Compiler
Run `make` in the root directory to build the `novusc` executable:
```bash
make
```

## Testing

Always run the full test suite before submitting changes:
```bash
./tests/run_tests.sh
```

### Adding New Tests
Create a `.nov` file in the `tests/` directory. If the test should pass, ensure it returns `0` from the `main` function. The `run_tests.sh` script automatically detects and executes all `.nov` files in the `tests/` folder.

## Generics Implementation
Novus uses **monomorphization**. When a generic struct is used with concrete types, the `SemanticAnalyzer` clones the AST of the struct and its methods, substituting type parameters with concrete types. These specialized declarations are then added to the program for code generation.

## Coding Style
- Follow existing naming conventions (CamelCase for classes/structs in AST).
- Ensure new features are accompanied by documentation and tests.
