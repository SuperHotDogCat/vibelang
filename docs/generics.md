# Generics in Novus

Novus supports generic programming through a process called **monomorphization**. This allows you to write reusable code that works with any type while maintaining the performance of statically-typed code.

## 1. Syntax

### Generic Structs
To define a generic struct, use square brackets `[]` to specify one or more type parameters.

```rust
struct Box[T] {
    value: @T;
}

struct Pair[K, V] {
    first: @K;
    second: @V;
}
```

-   **Type Parameters**: Declared after the struct name in `[]`.
-   **Reference**: Use `@` followed by the type parameter name (e.g., `@T`) to refer to the type within the struct definition.

### Implementation Blocks
Behavior for generic structs is defined in `impl` blocks that also specify the type parameters.

```rust
impl[T] Box {
    fn set(val: @T) -> void {
        self.value = val;
    }

    fn get() -> @T {
        return self.value;
    }
}
```

### Generic Functions
Standalone functions can also be generic.

```rust
fn identity[T](val: @T) -> @T {
    return val;
}
```

## 2. Usage and Specialization

When you use a generic struct with concrete type arguments, the compiler creates a specialized version of the struct and its methods.

```rust
fn main() -> int {
    var b: Box[int];
    b.set(42);

    var s: Box[string];
    s.set("Hello Generics");

    return b.get();
}
```

In the example above, the compiler generates:
1.  A version of `Box` specialized for `int`.
2.  A version of `Box` specialized for `string`.

## 3. How it Works: Monomorphization

Novus uses monomorphization, similar to C++ templates or Rust generics.

1.  **Parsing**: The compiler parses the generic template and stores it.
2.  **Instantiation**: When a concrete instantiation (like `Box[int]`) is encountered during semantic analysis:
    -   The compiler checks if it has already generated this specialization.
    -   If not, it clones the AST of the generic struct and its `impl` blocks.
    -   It substitutes all occurrences of `@T` with the concrete type `int`.
    -   The new, specialized declarations are added to the program.
3.  **Code Generation**: The specialized code is then compiled into optimized LLVM IR.

## 4. Limitations
-   Currently, Novus does not support type constraints (concepts/traits).
-   Generic type parameters are only available within the scope of the struct or function they are declared in.
