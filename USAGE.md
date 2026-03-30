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

    LOG_DEBUG_MSG(LOG_MAIN, "App started");
    LOG_INFO_MSG(LOG_MAIN, "Service initialized");
    LOG_TRACE_MSG(LOG_MAIN, "Trace checkpoint");
    LOG_CRITICAL_MSG(LOG_MAIN, "Critical event example");

    return 0;
}
```

`LOG_MAIN` is defined in your application's `config.h` (copy it from `config.h.example` shipped with `loggerd`; default `LOG_CRITICAL`). Override it in your build or replace it with another threshold constant (see below).

Typical output:

```text
[INFO] [2026-03-01 23:14:31] [main.cpp:61] Service initialized
```

## 5. Log levels and compile-time switches

The library uses compile-time macros:

- `LOG_DEBUG`
- `LOG_INFO`
- `LOG_TRACE`
- `LOG_CRITICAL`

Defaults are defined in `config.h.example` (copied to your application's `config.h`).

### Option A: change defaults in your application's `config.h`

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

Each macro takes two arguments: `(level, message)`.

- `LOG_DEBUG_MSG(level, message)`
- `LOG_INFO_MSG(level, message)`
- `LOG_TRACE_MSG(level, message)`
- `LOG_CRITICAL_MSG(level, message)`

The `message` is the text written to the log. The `level` argument is compared to the matching `LOG_*` constant when that category is compiled out globally (when `LOG_LEVEL` in `config.h` is below that category); otherwise it is unused. In application code it is typical to pass `LOG_MAIN` or your own threshold macro.

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

## 10. Mini-recipe: Where to put `config.h` (CMake and qmake)
`loggerd` includes `config.h` via `#include "config.h"` in `Loggerd.h`, so `config.h` should be provided by your project (application), not the library itself.

### CMake (`add_subdirectory`)
1. Copy `loggerd/config.h.example` to your application folder as `config.h`:
- `your-app/config.h`
2. In `CMakeLists.txt`, before `add_subdirectory(external/loggerd ...)`, set:
```cmake
set(LOGGERD_CONFIG_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
add_subdirectory(external/loggerd loggerd_build)
```
3. Then build as usual:
```cmake
add_executable(my_app src/main.cpp)
target_link_libraries(my_app PRIVATE loggerd::loggerd)
```

### qmake (`.pro`)
1. Copy Add `loggerd/config.h.example` to your application folder as `config.h`:
- `your-app/config.h`
2. In your `.pro`, add the include path to the `config.h` directory and include `loggerd.pri`:
```qmake
INCLUDEPATH += $$PWD
HEADERS += $$PWD/config.h
include(../../loggerd.pri)
```
