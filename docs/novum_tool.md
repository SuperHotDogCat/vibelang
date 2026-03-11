# Novum: Novus Project Manager

`novum` is the official project management and build tool for the Novus programming language. It simplifies project creation, dependency resolution, and the compilation process.

## Commands

### `init <name>`
Creates a new Novus project in a directory named `<name>`.
- Generates `Project.toml` configuration.
- Creates `src/main.nov` entry point.
- Creates a `lib/` directory for project-specific libraries.

### `build`
Compiles the project based on the `Project.toml` configuration.
- Invokes `novusc` to generate LLVM IR.
- Invokes `llc-18` to generate object files.
- Invokes `gcc` to link with libc and produce a final binary.
- Outputs the executable to the `build/` directory.

### `run`
Executes the `build` command and then runs the resulting binary.

## Project Configuration: `Project.toml`

A simple configuration file that defines project metadata.

```toml
[project]
name = "my_app"
version = "0.1.0"
main = "src/main.nov"
```

## How it handles PATHs

`novum` automatically sets the `NOVUS_PATH` environment variable to include:
1. The global Novus `lib/` directory (containing the standard library).
2. The project root.
3. The project's local `lib/` directory.

This allows you to `import "std.nov"` or any local modules seamlessly.
