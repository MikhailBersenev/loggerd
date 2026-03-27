TEMPLATE = app
TARGET = exampleApp

CONFIG += console c++17
CONFIG -= app_bundle

SOURCES += \
    main.cpp

include(../../loggerd.pri)

# Use local sources from loggerd.pri and do not require system pkg-config package.
CONFIG -= link_pkgconfig
PKGCONFIG -= loggerd
