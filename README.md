# loggerd

Lightweight C++17 logging library.

Features:
- multiple handlers (`MessageHandler`, `TxtMessageHandler`),
- log levels (`DEBUG`, `INFO`, `TRACE`, `CRITICAL`),
- source location in logs (`[file.cpp:line]`),
- compile-time level toggles via macros (`LOG_*_MSG(level, message)`; see `USAGE.md`).

## Quick Start

```cmake
add_subdirectory(external/loggerd)
target_link_libraries(my_app PRIVATE loggerd::loggerd)
```

## Documentation

Detailed integration and usage guide:
- `USAGE.md`
