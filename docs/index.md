# Novus Programming Language

Novus is a statically typed, systems-oriented programming language with an LLVM backend. It combines a clean, modern syntax with the power and performance of LLVM, featuring a robust type system, object-oriented constructs, and seamless C interoperability.

## 🚀 Quick Start

### Installation

1.  **Clone and Build**:
    ```bash
    git clone https://github.com/your-repo/novus.git
    cd novus
    make
    sudo make install
    ```

2.  **Create your first project**:
    ```bash
    novum init hello_world
    cd hello_world
    ```

3.  **Run it**:
    ```bash
    novum run
    ```

## 💎 Features

-   **Statically Typed**: Catch errors at compile-time with a rigorous type system including explicit bit-widths (`int32`, `int64`, `float32`, etc.).
-   **LLVM Backend**: Generates optimized IR for x86_64 and ARM64 using LLVM 18.
-   **Object-Oriented**: Data encapsulation with `struct` and behavior with `impl` blocks.
-   **Memory Control**: First-class support for pointers, arrays, and explicit memory management.
-   **C Interop**: Seamlessly call C functions using `extern` and integrate Novus into C projects.
-   **Modern Tooling**: `novum` project manager for scaffolding, building, and running.
-   **Module System**: Intelligent recursive `import` with `NOVUS_PATH` support.

## 📖 Documentation

For full documentation, visit our [Documentation Website](https://your-username.github.io/novus/).

Key topics:
- [Programming Guide](programming_guide.md)
- [Standard Library Reference](standard_library.md)
- [C Interoperability](interop_internals.md)
- [Installation Guide](installation.md)
- [Numeric Types & Bit-widths](numeric_types.md)

## 🛠 Language at a Glance

### Variables & Types
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

We welcome contributions! Please see our [Contributing Guidelines](contributing.md) to get started.

## 📄 License

Novus is released under the MIT License.
