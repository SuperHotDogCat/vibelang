# Novus Programming Guide

Welcome to the Novus programming language! This guide will help you understand the core concepts and patterns used in Novus development.

## 1. Project Structure

A typical Novus project is organized as follows:

- `src/`: Your application source files.
- `lib/`: Local libraries or the Novus standard library.
- `tests/`: Integration and unit tests.

## 2. Core Concepts

### Statically Typed
Every variable and function parameter must have a type. Types cannot change once defined.

### Structs and Implementation
Novus uses a separation of data and behavior. Define data in `struct` and methods in `impl`.

```rust
struct Counter {
    val: int;
}

impl Counter {
    fn inc() -> void {
        self.val = self.val + 1;
    }
}
```

### Methods and `self`
All methods automatically receive a `self` parameter, which is a pointer to the instance. You access members using `self.member`.

### Generics and Monomorphization
Novus supports generics for structs and `impl` blocks. When a generic struct is instantiated with concrete type arguments (e.g., `Box[int]`), the compiler generates a specialized version of the struct and its methods.

- **Syntax**: `struct Name[T1, T2] { ... }`
- **Reference**: Use `@T` to refer to the type parameter within the struct or `impl` block.
- **Methods**: Methods in an `impl[T] StructName` block are specialized whenever `StructName[ConcreteType]` is used.

```rust
struct Pair[K, V] {
    first: @K;
    second: @V;
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

Novus provides low-level control over memory.

- **Stack Allocation**: Local variables of struct types are allocated on the stack.
- **Heap Allocation**: Use `malloc` from `std.nov` for heap allocation. Remember to `free`.

```rust
import "std.nov";

fn demo() -> void {
    var p: int* = malloc(8) as int*;
    *p = 100;
    free(p as void*);
}
```

## 4. Working with Strings

Novus strings are immutable pointers to characters (`i8*`).

```rust
var s: string = "Hello\n";
printf(s);
```

Escape sequences like `\n`, `\t`, `\r`, `\\`, and `\"` are supported.

## 5. Standard Library Data Structures

### Vector
A dynamic array that grows as needed.

```rust
var v: Vector;
v.init(10);
v.push(1);
var x: int = v.get(0);
```

### HashSet and HashMap
Efficient collections using open-addressing hashing with linear probing.

```rust
var map: HashMap;
map.init(16);
map.put(1, 100);
var val: int = map.get(1);
```

### Queue, Deque, and PriorityQueue
Additional data structures for various use cases:

- **Queue**: FIFO queue using a circular buffer.
- **Deque**: Double-ended queue.
- **PriorityQueue**: Max-heap implementation for prioritized processing.

```rust
var pq: PriorityQueue;
pq.init(10);
pq.push(50);
var top: int = pq.pop();
```

## 6. Debugging Tips

- **Compiler Errors**: The Novus compiler provides line and column numbers for semantic errors (type mismatches, undefined variables).
- **LLVM IR**: Examine the generated `.ll` file to see exactly what instructions are being generated.
- **GDB**: You can debug the final binary using `gdb` just like a C program.

## 7. Interop with C

You can call any C function by declaring it `extern`.

```rust
extern fn getchar() -> int;

fn main() -> int {
    var c: int = getchar();
    return 0;
}
```
Link with the appropriate library (usually libc is included by default with `gcc`).
