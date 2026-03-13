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
Novus uses **monomorphization**. When a generic struct or function is used with concrete types, the `SemanticAnalyzer::instantiateStruct` (and related logic) handles the specialization:

1.  **Mangling**: A unique name is generated based on the base name and type arguments (e.g., `Box_int`).
2.  **Cloning**: The AST of the generic template is cloned.
3.  **Substitution**: Type parameters (e.g., `@T`) are replaced with concrete types.
4.  **Registration**: The specialized declarations are added to `Program::decls`.
5.  **Validation**: The specialized code is re-analyzed to ensure type safety.
6.  **Code Generation**: The `CodeGenerator` produces optimized LLVM IR for each specialization.

## Coding Style
- Follow existing naming conventions (CamelCase for classes/structs in AST).
- Ensure new features are accompanied by documentation and tests.
