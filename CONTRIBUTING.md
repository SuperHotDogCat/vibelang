# Contributing to Novus

First off, thank you for considering contributing to Novus! It's people like you who make Novus such a great tool.

## Code of Conduct

By participating in this project, you are expected to uphold our Code of Conduct. Please report unacceptable behavior to the project maintainers.

## How Can I Contribute?

### Reporting Bugs

- Use the GitHub issue tracker to report bugs.
- Describe the expected behavior and the actual behavior.
- Provide a minimal reproducible example if possible.

### Suggesting Enhancements

- Use the GitHub issue tracker to suggest enhancements.
- Describe the goal of the enhancement and why it would be useful.

### Pull Requests

- Pull requests are always welcome!
- Ensure your code follows the existing style of the project.
- Write tests for any new features or bug fixes.
- Ensure all tests pass before submitting your PR.

## Development Environment Setup

Novus development requires several dependencies, primarily LLVM 18.

### Using Docker (Recommended)

The easiest way to get started is using the provided `Dockerfile`.

```bash
docker build -t novus-dev .
docker run -it novus-dev
```

### Manual Setup (Ubuntu 24.04)

If you prefer to set up your environment manually:

```bash
sudo apt-get update
sudo apt-get install -y llvm-18-dev clang-18 flex bison make g++
```

### Building the Project

Use the `Makefile` to build the compiler and the project manager:

```bash
make
```

To install locally:

```bash
sudo make install
```

## Project Structure

- `src/`: Compiler source code (C++).
  - `lexer.l`: Flex lexer definition.
  - `parser.y`: Bison parser definition.
  - `ast.h`: Abstract Syntax Tree nodes.
  - `semantics.cpp`: Semantic analysis and type checking.
  - `codegen.cpp`: LLVM IR generation.
- `lib/`: Standard library (`std.nov`).
- `bin/`: Built-in tools like `novum`.
- `tests/`: Test suite.

## Coding Standards

- Use 4 spaces for indentation in C++ and Novus code.
- Follow standard C++ naming conventions.
- Comment complex logic in the compiler.
- Ensure Novus code is well-documented and readable.

## Running Tests

Before submitting a PR, ensure all tests pass:

```bash
bash tests/run_tests.sh
```

Adding new tests is highly encouraged! Create a `.nov` file in `tests/` and add it to the test runner if necessary.
