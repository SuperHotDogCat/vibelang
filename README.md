# Novus Programming Language

Novus is a statically typed, LLVM-based language with support for structs, methods, pointers, built-in strings, and C/C++ interoperability.

## Features

- **Types**: `int` (i64), `float` (f64), `bool` (i1), `char` (i8), `string` (i8*), pointers (`T*`), arrays (`T[N]`), and structs.
- **Functions & Methods**: Support for top-level functions and methods on structs using `impl` blocks.
- **Control Flow**: `if-else`, `while` loops.
- **Operators**: `+`, `-`, `*`, `/`, `%`, `<<`, `>>`, `==`, `!=`, `<`, `>`, `<=`, `>=`, `!`, `&` (address-of), `*` (dereference).
- **Casting**: Explicit casting using `as` keyword (e.g., `ptr as int*`).
- **Standard Library**: Functional `Vector` and `Set` implementations in `lib/std.nov`.
- **Module System**: `import` support for multi-file projects.
- **Error Reporting**: Semantic errors include line and column information.
- **Interoperability**: Call C/C++ functions and be called from C/C++ via standard calling conventions.

## Docker Usage

A `Dockerfile` is provided to build and run the Novus environment.

```bash
docker build -t novus .
docker run -it novus
```

## Syntax Example

```rust
import "lib/std.nov";

fn main() -> int {
    printf("Novus language demo\n", 0, 0, 0);
    return 0;
}
```

## Compiling and Running

### Building the Compiler
First, build the `novusc` compiler using `make`:
```bash
make
```

### Compiling a Novus file to an Executable
To compile a `.nov` file into a standalone executable, follow these three steps:

1. **Emit LLVM IR**:
   ```bash
   ./novusc main.nov
   ```
2. **Convert IR to Object File**:
   ```bash
   llc-18 main.ll -relocation-model=pic -filetype=obj -o main.o
   ```
3. **Link with libc and Create Executable**:
   ```bash
   gcc main.o -o main
   ```

**One-liner command:**
```bash
./novusc main.nov && llc-18 main.ll -relocation-model=pic -filetype=obj -o main.o && gcc main.o -o main && ./main
```

## C/C++ Interoperability

### Calling C from Novus
Declare the C function in your Novus code without a body:
```rust
fn printf(fmt: string, a: int, b: int, c: int) -> int;
```
Then call it normally.

### Calling Novus from C
Compile your Novus code to an object file and link it with your C code:
```bash
./novusc mycode.nov
llc-18 mycode.ll -relocation-model=pic -filetype=obj -o mycode.o
gcc main.c mycode.o -o demo
```

## Project Structure

- `src/`: Compiler source code.
- `lib/`: Standard library written in Novus.
- `tests/`: Integration tests and interoperability demos.
- `Dockerfile`: Containerized build environment.
- `Makefile`: Build script.
```
