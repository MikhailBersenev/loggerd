TEMPLATE = app
TARGET = exampleApp

CONFIG += console c++17
CONFIG -= app_bundle

# Application provides `config.h` in the same directory as main.cpp.
INCLUDEPATH += $$PWD

HEADERS += \
    config.h

SOURCES += \
    main.cpp

include(../../loggerd.pri)

# Use local sources from loggerd.pri and do not require system pkg-config package.
CONFIG -= link_pkgconfig
PKGCONFIG -= loggerd
