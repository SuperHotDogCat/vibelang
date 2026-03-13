# Novus Programming Language

Novus is a statically typed, systems-oriented programming language with an LLVM backend. It combines a clean, modern syntax with the power and performance of LLVM, featuring a robust type system, object-oriented constructs, and seamless C interoperability.

## Table of Contents
- [Features](#features)
- [Language Specification](#language-specification)
  - [Basic Types](#basic-types)
  - [Generics](#generics)
  - [Variables](#variables)
  - [Functions](#functions)
  - [Structs and Methods](#structs-and-methods)
  - [Control Flow](#control-flow)
  - [Operators](#operators)
  - [Pointers and Memory](#pointers-and-memory)
  - [Module System](#module-system)
- [Project Management with Novum](#project-management-with-novum)
- [C Interoperability](#c-interoperability)
- [Standard Library](#standard-library)
- [Documentation Index](#documentation-index)
- [Compilation Guide](#compilation-guide)
- [Docker Usage](#docker-usage)

## Features
- **Statically Typed**: Catch errors at compile-time with a rigorous type system.
- **LLVM Backend**: Generates optimized IR for x86_64 and ARM64.
- **Object-Oriented**: Structs and `impl` blocks for data encapsulation and methods.
- **Memory Control**: First-class support for pointers, arrays, and explicit memory management.
- **Built-in Strings**: Native `string` type with escape sequence support.
- **C Interop**: Call any C library function using `extern` and export Novus functions to C.
- **Module System**: Recursive `import` with support for `NOVUS_PATH`.

## Language Specification

### Basic Types
- `int`: Default 64-bit signed integer (LLVM `i64`).
- `int16`, `int32`, `int64`: Specific bit-width signed integers.
- `float`: Default 64-bit double-precision floating point (LLVM `double`).
- `float16`, `float32`, `float64`: Specific bit-width floating point types.
- `bool`: Boolean type (`true` or `false`).
- `char`: 8-bit character.
- `string`: Immutable UTF-8 string (internally `i8*`).
- `void`: Represents the absence of a value.

### Generics
Novus supports generic structs and implementation blocks through monomorphization. Use `[T]` for type parameters and `@T` to refer to them.

```rust
struct Box[T] {
    value: @T;
}

impl[T] Box {
    fn set(val: @T) -> void {
        self.value = val;
    }
    fn get() -> @T {
        return self.value;
    }
}

fn main() -> int {
    var b: Box[int];
    b.set(42);
    return b.get();
}
```

### Variables
Variables are declared using the `var` keyword.
```rust
var x: int = 42;          // default 64-bit int
var y: int32 = 100;       // explicit 32-bit int
var pi: float32 = 3.14;   // explicit 32-bit float
var msg: string = "Hello";
```

### Functions
```rust
fn add(a: int, b: int) -> int {
    return a + b;
}
```

### Structs & Methods
```rust
struct Point { x: int; y: int; }

impl Point {
    fn distance_sq() -> int {
        return self.x * self.x + self.y * self.y;
    }
}
```

## 🤝 Contributing

We welcome contributions! Please see our [Contributing Guidelines](CONTRIBUTING.md) to get started.

## 📄 License

Novus is released under the MIT License.
