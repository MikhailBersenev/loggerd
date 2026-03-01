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
    config.h
)

add_library(loggerd
    ${LOGGERD_SOURCES}
    ${LOGGERD_HEADERS}
)

add_library(loggerd::loggerd ALIAS loggerd)

target_compile_features(loggerd PUBLIC cxx_std_17)

target_include_directories(loggerd PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)