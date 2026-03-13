# Numeric Types and Bit-widths

Novus provides a variety of numeric types with specific bit-widths to give developers fine-grained control over memory usage and performance.

## Integer Types

| Type    | Bit-width | Description                     | LLVM Type |
|---------|-----------|---------------------------------|-----------|
| `int16` | 16-bit    | Signed short integer            | `i16`     |
| `int32` | 32-bit    | Signed integer                  | `i32`     |
| `int64` | 64-bit    | Signed long integer             | `i64`     |
| `int`   | 64-bit    | Default signed integer          | `i64`     |

### Default Type
Integer literals (e.g., `42`) default to `int64` unless assigned to a variable with an explicit type or cast.

## Floating-Point Types

| Type      | Bit-width | Description                     | LLVM Type |
|-----------|-----------|---------------------------------|-----------|
| `float16` | 16-bit    | Half-precision float            | `half`    |
| `float32` | 32-bit    | Single-precision float          | `float`   |
| `float64` | 64-bit    | Double-precision float          | `double`  |
| `float`   | 64-bit    | Default double-precision float | `double`  |

### Default Type
Floating-point literals (e.g., `3.14`) default to `float64` unless assigned to a variable with an explicit type or cast.

## Promotion Rules

Novus performs automatic promotion for numeric types in expressions to prevent precision loss.

1.  **Small to Large**: Smaller bit-width types are promoted to larger bit-width types (e.g., `int32` + `int64` results in `int64`).
2.  **Integer to Float**: If one operand is an integer and the other is a float, the integer is promoted to a float (e.g., `int` + `float` results in `float`).

## Explicit Casting

You can use the `as` operator for explicit casting between types.

```rust
var x: int64 = 100;
var y: int32 = x as int32; // Downcasting

var f: float64 = 3.14;
var i: int = f as int;     // Truncating float to int
```

Note: Downcasting or casting from float to int may result in data loss or truncation.
