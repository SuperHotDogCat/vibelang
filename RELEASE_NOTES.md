# Release Notes: Novus v1.0.0

We are proud to announce the initial stable release of the **Novus Programming Language**. Novus is a statically-typed, systems-oriented language designed for performance, safety, and seamless integration with existing C ecosystems.

## Key Features

### 🚀 High-Performance Backend
- Built on **LLVM 18**, generating optimized machine code for **x86_64** and **ARM64**.
- Statically typed with rigorous compile-time checks.

### 💎 Modern Language Constructs
- **Rich Type System**: Support for `int` (64-bit), `float` (double), `bool`, `char`, and built-in `string`.
- **Memory Safety & Control**: First-class support for pointers (`T*`), arrays (`T[N]`), and explicit casting (`as`).
- **Object-Oriented**: Data encapsulation with `struct` and associated behavior via `impl` blocks.
- **Top-level Globals**: Support for global variable declarations and cross-file state.

### 📦 Ecosystem & Tooling
- **`novum` Project Manager**: A unified tool for scaffolding (`init`), building (`build`), and executing (`run`) projects.
- **Robust Module System**: Recursive `import` with intelligent path resolution (supporting `NOVUS_PATH`).
- **Advanced Standard Library**: Functional implementations of `Vector` (dynamic resizing), `HashSet`, `HashMap`, `Queue`, `Deque`, `Stack`, and `PriorityQueue`.
- **Docker Support**: Containerized build environment for reproducible development across architectures.

### 🔗 C Interoperability
- **Direct libc Calls**: Call any C function (including variadic ones like `printf`) using the `extern fn` keyword.
- **Seamless Integration**: Novus functions follow standard calling conventions, allowing them to be linked and called from C/C++ projects.

## Recent Improvements
- **Robust Hashing**: Added native hashing for `int`, `float`, and `string`.
- **Improved Module Resolution**: Imports are now resolved relative to the importing file.
- **Enhanced Syntax**: Added support for C-style declarations (`int x = 1;`) at both global and local scopes.
- **Precise Error Reporting**: Semantic errors now include exact line and column information.

## Getting Started
To install Novus on your system:
```bash
make
sudo make install
```
Start a new project with:
```bash
novum init my_app
cd my_app
novum run
```

For more details, see the [Programming Guide](docs/programming_guide.md) and [Installation Guide](docs/installation.md).
