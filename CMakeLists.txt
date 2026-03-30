cmake_minimum_required(VERSION 3.16)
project(loggerd LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(LOGGERD_SOURCES
    src/Loggerd.cpp
    src/MessageHandler.cpp
    src/TxtMessageHandler.cpp
)

set(LOGGERD_HEADERS
    src/Loggerd.h
    src/MessageHandler.h
    src/TxtMessageHandler.h
)

add_library(loggerd
    ${LOGGERD_SOURCES}
    ${LOGGERD_HEADERS}
)

add_library(loggerd::loggerd ALIAS loggerd)

target_compile_features(loggerd PUBLIC cxx_std_17)

# Directory containing `config.h` for this build.
# In the recommended integration scheme the application provides `config.h`.
set(LOGGERD_CONFIG_DIR "" CACHE PATH "Directory containing config.h for loggerd")

set(_loggerd_config_include_dirs "")
if(LOGGERD_CONFIG_DIR)
    set(_loggerd_config_h "${LOGGERD_CONFIG_DIR}/config.h")
    if(EXISTS "${_loggerd_config_h}")
        set(_loggerd_config_include_dirs "${LOGGERD_CONFIG_DIR}")
    endif()
endif()

# Fallback: generate config.h from the shipped example (in build dir).
if(NOT _loggerd_config_include_dirs)
    set(_loggerd_config_example "${CMAKE_CURRENT_SOURCE_DIR}/config.h.example")
    if(EXISTS "${_loggerd_config_example}")
        configure_file("${_loggerd_config_example}" "${CMAKE_CURRENT_BINARY_DIR}/config.h" COPYONLY)
        set(_loggerd_config_include_dirs "${CMAKE_CURRENT_BINARY_DIR}")
        message(WARNING "loggerd: config.h not provided by the application; using default generated from config.h.example")
    else()
        message(FATAL_ERROR "loggerd: neither config.h nor config.h.example were found")
    endif()
endif()

target_include_directories(loggerd PUBLIC
    ${_loggerd_config_include_dirs}
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)