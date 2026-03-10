# Novus Programming Language

Novus is a statically typed, LLVM-based language with support for structs, methods, pointers, and built-in strings.

## Features

- **Types**: `int`, `float`, `bool`, `char`, `string`, pointers (`T*`), arrays (`T[N]`), and structs.
- **Functions & Methods**: Support for top-level functions and methods on structs using `impl` blocks.
- **Control Flow**: `if-else`, `while` loops.
- **Operators**: `+`, `-`, `*`, `/`, `%`, `<<`, `>>`, `==`, `!=`, `<`, `>`, `<=`, `>=`, `!`, `&` (address-of), `*` (dereference).
- **Casting**: Explicit casting using `as` keyword (e.g., `ptr as int`).
- **Standard Library**: Functional `Vector` and `Set` implementations in `lib/std.nov`.
- **Module System**: `import` support for multi-file projects.
- **Error Reporting**: Semantic errors include line and column information.

## Syntax Example

```rust
import "lib/std.nov";

struct Point {
    x: int;
    y: int;
}

impl Point {
    fn set(x: int, y: int) -> void {
        self.x = x;
        self.y = y;
    }

    fn area() -> int {
        return self.x * self.y;
    }
}

fn main() -> int {
    var p: Point;
    p.set(10, 20);

    var msg: string = "Area calculated: ";
    // print(msg); // if print was implemented

    return p.area();
}
```

## Building

To build the compiler:
```bash
make
```

To compile a Novus program:
```bash
./novusc tests/test_lib.nov
```
This generates `tests/test_lib.ll`.

To generate assembly for different architectures:

**x86_64:**
```bash
llc-18 tests/test_lib.ll -o test.s
```

**ARM64:**
```bash
llc-18 tests/test_lib.ll -march=aarch64 -o test_arm.s
```

## Project Structure

- `src/`: Compiler source code.
    - `lexer.l`: Tokenization (Flex).
    - `parser.y`: Grammar and AST construction (Bison).
    - `ast.h`: AST node definitions.
    - `semantics.cpp`: Type checking and symbol management.
    - `codegen.cpp`: LLVM IR generation.
    - `compiler.cpp`: Driver for multi-file compilation.
- `lib/`: Standard library written in Novus.
- `tests/`: Integration tests.
- `Makefile`: Build script.
```
