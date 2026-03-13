# Novus Programming Guide

Welcome to the Novus programming language! This guide will help you understand the core concepts and patterns used in Novus development.

## 1. Project Structure

A typical Novus project managed by `novum` is organized as follows:

- `src/`: Your application source files (e.g., `main.nov`).
- `lib/`: Local libraries or project-specific modules.
- `build/`: Output directory for compiled binaries and objects (created by `novum build`).
- `Project.toml`: Project configuration file.

## 2. Core Concepts

### Statically Typed
Every variable and function parameter must have a type. Types are checked at compile-time.

```rust
var x: int = 10;
var name: string = "Novus";
```

### Structs and Implementation
Novus uses a separation of data (structs) and behavior (impl blocks).

```rust
struct Rectangle {
    width: int;
    height: int;
}

impl Rectangle {
    // Methods receive an implicit 'self' pointer
    fn area() -> int {
        return self.width * self.height;
    }

    fn scale(factor: int) -> void {
        self.width = self.width * factor;
        self.height = self.height * factor;
    }
}
```

### Methods and `self`
Methods are defined within `impl` blocks. The `self` keyword refers to a pointer to the instance of the struct the method is called on.

### Generics and Monomorphization
Novus supports generics for structs, `impl` blocks, and functions. When a generic template is instantiated with concrete type arguments (e.g., `Box[int]`), the compiler generates a specialized version of the code.

For a deep dive, see the [Generics Reference](generics.md).

- **Syntax**: `struct Name[T] { ... }` or `fn name[T](...) -> ...`
- **Reference**: Use `@T` to refer to the type parameter within the scope.
- **Specialization**: Specialized whenever used with concrete types (e.g., `var v: Vector[int];`).

```rust
struct Pair[K, V] {
    first: @K;
    second: @V;
}

fn swap[T](a: @T*, b: @T*) -> void {
    var tmp: @T = *a;
    *a = *b;
    *b = tmp;
}
```

## 3. Numeric Types and Promotion
Novus provides a range of signed integer and floating-point types with specific bit-widths.

- **Integers**: `int16`, `int32`, `int64`, and `int` (alias for `int64`).
- **Floats**: `float16`, `float32`, `float64`, and `float` (alias for `float64`).

### Type Promotion Rules
The compiler automatically promotes smaller types to larger types when necessary:
- `int16` -> `int32` -> `int64`
- `float16` -> `float32` -> `float64`
- Any integer type can be promoted to `float` or `float64`.

For explicit conversion between incompatible types, use the `as` operator:
```rust
var x: float = 3.14;
var i: int = x as int;
```

## 4. Memory Management

Novus provides low-level control over memory, similar to C.

- **Stack Allocation**: Local variables are allocated on the stack.
- **Heap Allocation**: Use `malloc` from the standard library for heap allocation and `free` to deallocate.

```rust
import "std.nov";

fn heap_example() -> void {
    // Allocate space for 10 integers
    var v: Vector[int];
    v.init(10);
    v.push(42);
    printf("Value: %d\n", v.get(0));
}
```

## 4. Control Flow

Novus supports standard control flow constructs.

### If-Else
```rust
if (x > 10) {
    printf("Greater than 10\n");
} else if (x == 10) {
    printf("Exactly 10\n");
} else {
    printf("Less than 10\n");
}
```

### While Loops
```rust
var i: int = 0;
while (i < 5) {
    printf("i = %d\n", i);
    i = i + 1;
}
```

## 5. Pointers and Arrays

### Pointers
Pointers are declared with `*` and accessed with `&` (address-of) and `*` (dereference).

```rust
var x: int = 10;
var ptr: int* = &x;
*ptr = 20; // x is now 20
```

### Arrays
Fixed-size arrays are supported.

```rust
var arr: int[5];
arr[0] = 100;
var val: int = arr[0];
```

## 6. Advanced Topics

### C Interoperability
You can call C functions by declaring them with `extern fn`.

```rust
extern fn pow(base: float, exp: float) -> float;

fn main() -> int {
    var res: float = pow(2.0, 10.0);
    printf("2^10 = %f\n", res);
    return 0;
}
```

### Module System and Imports
Use `import` to include other files. The compiler searches the current directory and `NOVUS_PATH`.

```rust
import "std.nov";
import "my_module.nov";
```

### Explicit Casting
Use `as` for type conversions.

```rust
var f: float = 3.9;
var i: int = f as int; // i becomes 3
```

## 7. Standard Library
Novus comes with a standard library (`std.nov`) that includes:
- Dynamic arrays (`Vector`)
- Hash collections (`HashSet`, `HashMap`)
- Linear collections (`Stack`, `Queue`, `Deque`)
- Priority Queue

See the [Standard Library Reference](standard_library.md) for more details.
