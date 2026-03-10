# Module Path Resolution in Novus

This document explains how the Novus compiler resolves file paths during the `import` process.

## The `import` Statement

In Novus, you include external code using the `import` keyword:

```rust
import "std.nov";
import "utils/math.nov";
```

## Resolution Algorithm

When the compiler encounters an `import "filename.nov"` statement, it follows these steps to find the file:

1.  **Local Path**: It first checks if the file exists relative to the current working directory.
2.  **NOVUS_PATH Search**: If not found locally, it checks the directories listed in the `NOVUS_PATH` environment variable.
3.  **Error**: If the file is not found in any of these locations, the compiler throws a "Could not open file" error.

## Setting `NOVUS_PATH`

The `NOVUS_PATH` environment variable is a colon-separated (on Linux/macOS) list of directories.

### Temporary Setting (Command Line)
You can set it for a single command:
```bash
NOVUS_PATH=./lib:./custom_modules ./novusc main.nov
```

### Persistent Setting (Shell Profile)
Add it to your `~/.bashrc` or `~/.zshrc`:
```bash
export NOVUS_PATH=$HOME/novus/lib:$HOME/my_project/modules
```

## Internal Implementation (`src/compiler.cpp`)

The `resolvePath` method handles this logic:

```cpp
std::string Compiler::resolvePath(const std::string& path) {
    if (access(path.c_str(), F_OK) == 0) return path;

    const char* envPath = getenv("NOVUS_PATH");
    if (!envPath) return path;

    std::stringstream ss(envPath);
    std::string dir;
    while (std::getline(ss, dir, ':')) {
        std::string fullPath = dir + "/" + path;
        if (access(fullPath.c_str(), F_OK) == 0) {
            return fullPath;
        }
    }
    return path;
}
```

## Best Practices
- Keep your standard library in a dedicated directory and include it in `NOVUS_PATH`.
- Use relative paths for modules within the same project.
- Use `NOVUS_PATH` for third-party libraries or shared utilities.
