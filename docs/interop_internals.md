# Internals: C Interoperability and libc Wrappers

This document explains how Novus implements its C interoperability and standard library wrappers (`malloc`, `free`, `printf`), providing a guide for extending the language.

## Overview

Interoperability with C is achieved by aligning the Novus function call semantics and type system with the standard C calling convention (via LLVM) and providing a way to declare functions that exist in the host environment.

## 1. External Function Declarations

The `extern` keyword in Novus allows declaring a function signature without a body.

### Grammar (`src/parser.y`)
```bison
extern_decl:
    EXTERN FN IDENT '(' param_list ')' ARROW type ';' {
        auto* fd = new FunctionDecl(std::shared_ptr<Type>($8), *$3, std::move(*$5), nullptr);
        fd->isVariadic = false;
        $$ = setLoc(fd, @1);
    }
    | EXTERN FN IDENT '(' param_list ',' ELLIPSIS ')' ARROW type ';' {
        auto* fd = new FunctionDecl(std::shared_ptr<Type>($10), *$3, std::move(*$5), nullptr);
        fd->isVariadic = true;
        $$ = setLoc(fd, @1);
    }
```

When the compiler sees `extern`, it creates a `FunctionDecl` node where the `body` pointer is `nullptr`.

## 2. LLVM IR Generation (`src/codegen.cpp`)

The `CodeGenerator` handles external declarations during its function declaration pass.

```cpp
if (auto* fd = dynamic_cast<FunctionDecl*>(decl.get())) {
    if (module->getFunction(fd->name)) continue;

    std::vector<llvm::Type*> argTypes;
    for (auto& param : fd->params) {
        argTypes.push_back(getLLVMType(param.type.get()));
    }

    // Create the function with ExternalLinkage
    auto* ft = llvm::FunctionType::get(getLLVMType(fd->returnType.get()), argTypes, fd->isVariadic);
    llvm::Function::Create(ft, llvm::Function::ExternalLinkage, fd->name, *module);
}
```

By using `llvm::Function::ExternalLinkage` and not providing a basic block for the body, LLVM treats this as an external symbol that the linker (like `gcc` or `clang`) will resolve from the system libraries (like `libc`).

## 3. Type Mapping

To ensure compatibility with C, Novus types are mapped to LLVM types that match C's typical 64-bit ABI:

| Novus Type | LLVM Type | C Equivalent (x86_64/ARM64) |
|------------|-----------|-----------------------------|
| `int`      | `i64`     | `long long`                 |
| `float`    | `double`  | `double`                    |
| `bool`     | `i1`      | `_Bool`                     |
| `char`     | `i8`      | `char`                      |
| `string`   | `ptr`     | `const char*`               |
| `void*`    | `ptr`     | `void*`                     |
| `T*`       | `ptr`     | `T*`                        |

## 4. Variadic Functions (`printf`)

Novus supports variadic functions using the `...` syntax in declarations. This maps directly to LLVM's `isVarArg` attribute in `llvm::FunctionType`.

**Novus Declaration:**
```rust
extern fn printf(fmt: string, ...) -> int;
```

**Generated IR:**
```llvm
declare i32 @printf(ptr, ...)
```

## 5. Standard Wrappers in `lib/std.nov`

The standard library uses these mechanisms to expose libc functionality:

```rust
extern fn malloc(size: int) -> void*;
extern fn free(ptr: void*) -> void;
extern fn printf(fmt: string, ...) -> int;
```

When you link the resulting object file (`main.o`) with `gcc`, these symbols are automatically resolved from the default C library.

## How to Extend

To add more libc functions (e.g., `exit`, `open`, `read`):
1. Find the C signature (e.g., `void exit(int status)`).
2. Add an `extern fn` declaration in `lib/std.nov` or your local file.
3. Map C types to Novus types (e.g., `int` -> `int`).
4. Link your final object with `gcc`.
