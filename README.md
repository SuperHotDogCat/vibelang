# Novus Programming Language

Novus is a statically typed, systems-oriented programming language with an LLVM backend. It combines a clean, modern syntax with the power and performance of LLVM, featuring a robust type system, object-oriented constructs, and seamless C interoperability.

## Table of Contents
- [Features](#features)
- [Language Specification](#language-specification)
  - [Basic Types](#basic-types)
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
- `int`: 64-bit signed integer (LLVM `i64`).
- `float`: 64-bit double-precision floating point (LLVM `double`).
- `bool`: Boolean type (`true` or `false`).
- `char`: 8-bit character.
- `string`: Immutable UTF-8 string (internally `i8*`).
- `void`: Represents the absence of a value.

### Variables
Variables are declared using the `var` keyword.
```rust
var x: int = 10;
var pi: float = 3.14159;
var is_valid: bool = true;
var msg: string = "Hello, Novus!\n";
```

### Functions
Functions are defined using the `fn` keyword.
```rust
fn add(a: int, b: int) -> int {
    return a + b;
}

fn greet() -> void {
    printf("Hello!\n");
}
```

### Structs and Methods
Structs define data layouts, and `impl` blocks define methods for those structs. Methods always receive a `self` pointer as the first argument.
```rust
struct Point {
    x: int;
    y: int;
}

impl Point {
    fn init(x: int, y: int) -> void {
        self.x = x;
        self.y = y;
    }

    fn distance_sq() -> int {
        return self.x * self.x + self.y * self.y;
    }
}
```

### Control Flow
Supports standard `if-else` and `while` loops.
```rust
if (x > 0) {
    printf("Positive\n");
} else {
    printf("Non-positive\n");
}

while (i < 10) {
    i = i + 1;
}
```

### Operators
- **Arithmetic**: `+`, `-`, `*`, `/`, `%`
- **Relational**: `==`, `!=`, `<`, `>`, `<=`, `>=`
- **Bitwise**: `<<`, `>>`
- **Logical**: `!`
- **Pointer**: `&` (address-of), `*` (dereference)

### Pointers and Memory
Novus allows low-level memory access and explicit casting.
```rust
var p: int*;
var x: int = 42;
p = &x;
var val: int = *p;

// Casting
var raw: void* = malloc(8);
var ptr: int* = raw as int*;
```

### Module System
Import other Novus files using the `import` statement. The compiler searches in the current directory and directories specified in the `NOVUS_PATH` environment variable.
```rust
import "std.nov";
```

## C Interoperability

### Calling C from Novus
Use `extern fn` to declare C functions. Support for variadic functions is included (e.g., `printf`).
```rust
extern fn printf(fmt: string, ...) -> int;
extern fn malloc(size: int) -> void*;
```

### Calling Novus from C
Any function defined in Novus uses the standard C calling convention and can be called from C if declared `extern`.

## Installation
To install Novus on your system:
```bash
make
sudo make install
```
See the [Installation Guide](docs/installation.md) for more details.

## Project Management with Novum
`novum` is the primary tool for managing Novus projects. It handles scaffolding, building, and running your code.

```bash
# Create a new project
novum init my_app
cd my_app

# Build and run
novum run
```
See [Novum Tool Guide](docs/novum_tool.md) for more details.

## Standard Library (`lib/std.nov`)
- `Vector`: Dynamic array with automatic resizing.
- `HashSet`: Efficient set implementation using hashing.
- `HashMap`: Key-value store using hashing.
- Memory: `malloc`, `free`, and `printf` wrappers.

## Documentation Index
Comprehensive documentation can be found in the `docs/` directory:

- [C Interoperability Internals](docs/interop_internals.md): Technical details on how Novus talks to C.
- [Module Path Resolution](docs/path_resolution.md): How `import` and `NOVUS_PATH` work.
- [Novum Tool Guide](docs/novum_tool.md): Usage of the project management tool.
- [Installation Guide](docs/installation.md): How to install Novus on your system.
- [Programming Guide](docs/programming_guide.md): A guide for developers writing Novus code.

## Compilation Guide

1. **Build the Compiler**:
   ```bash
   make
   ```
2. **Compile to LLVM IR**:
   ```bash
   ./novusc my_program.nov
   ```
3. **Compile to Executable**:
   ```bash
   llc-18 my_program.ll -relocation-model=pic -filetype=obj -o my_program.o
   gcc my_program.o -o my_program
   ```

## Docker Usage
The provided `Dockerfile` creates a complete development environment with all dependencies.
```bash
docker build -t novus .
docker run -it novus
```
