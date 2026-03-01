# loggerd Usage Guide

This document describes how to integrate and use `loggerd` in your own C++ projects.

## 1. Requirements

- CMake 3.16+
- C++17-compatible compiler

## 2. Integration with `add_subdirectory`

Recommended layout:

```text
your-app/
  CMakeLists.txt
  src/
  external/
    loggerd/
```

In your project `CMakeLists.txt`:

```cmake
cmake_minimum_required(VERSION 3.16)
project(my_app LANGUAGES CXX)

add_subdirectory(external/loggerd)

add_executable(my_app src/main.cpp)
target_link_libraries(my_app PRIVATE loggerd::loggerd)
```

`loggerd` provides the target alias `loggerd::loggerd`, which is the preferred way to link it.

## 3. Headers and core types

Main headers:

- `Loggerd.h` - singleton logger and logging macros
- `MessageHandler.h` - base handler (writes to stdout by default)
- `TxtMessageHandler.h` - file handler (`.txt`, append mode)

## 4. Minimal example

```cpp
#include "Loggerd.h"
#include "MessageHandler.h"
#include "TxtMessageHandler.h"

int main() {
    Loggerd* logger = Loggerd::getInstance();

    MessageHandler consoleHandler;
    TxtMessageHandler fileHandler("app.log");

    logger->addMessageHandler(&consoleHandler);
    logger->addMessageHandler(&fileHandler);

    LOG_DEBUG_MSG("App started");
    LOG_INFO_MSG("Service initialized");
    LOG_TRACE_MSG("Trace checkpoint");
    LOG_CRITICAL_MSG("Critical event example");

    return 0;
}
```

Typical output:

```text
[INFO] [2026-03-01 23:14:31] [main.cpp:15] Service initialized
```

## 5. Log levels and compile-time switches

The library uses compile-time macros:

- `LOG_DEBUG`
- `LOG_INFO`
- `LOG_TRACE`
- `LOG_CRITICAL`

Defaults are defined in `config.h` (all enabled by default).

### Option A: change defaults in `config.h`

```cpp
#define LOG_TRACE 0
```

### Option B: override from your app CMake (recommended)

```cmake
target_compile_definitions(my_app PRIVATE
    LOG_DEBUG=1
    LOG_INFO=1
    LOG_TRACE=0
    LOG_CRITICAL=1
)
```

If a level is set to `0`, corresponding macro calls compile to no-op.

## 6. Available macros

- `LOG_DEBUG_MSG(message)`
- `LOG_INFO_MSG(message)`
- `LOG_TRACE_MSG(message)`
- `LOG_CRITICAL_MSG(message)`

All macros automatically pass `__FILE__` and `__LINE__`, so source location is included in the log entry.

## 7. Built-in handlers

### `MessageHandler`

- Base class
- Default implementation prints to stdout via `sendMessage(...)`

### `TxtMessageHandler`

- Writes to a text file
- Opens file in append mode (`std::ios::app`)
- Useful for persistent local logs

## 8. Creating custom handlers

Implement your own handler by inheriting from `MessageHandler` and overriding `sendMessage`:

```cpp
class MyHandler : public MessageHandler {
public:
    void sendMessage(const std::string& message) override {
        // send to network, syslog, ring buffer, etc.
    }
};
```

Then register it:

```cpp
MyHandler handler;
Loggerd::getInstance()->addMessageHandler(&handler);
```

## 9. Notes and best practices

- Register handlers before first log call.
- Keep handler objects alive while logger uses them.
- Avoid expensive string construction in disabled log levels.
- For production builds, disable noisy levels (for example `LOG_TRACE=0`).
