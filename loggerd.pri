# loggerd.pri - Qt module configuration for loggerd library

# Define the library name
LIBRARY_NAME = loggerd

# Headers
HEADERS += \
    $$PWD/src/Loggerd.h \
    $$PWD/src/MessageHandler.h \
    $$PWD/src/TxtMessageHandler.h

# Sources
SOURCES += \
    $$PWD/src/Loggerd.cpp \
    $$PWD/src/MessageHandler.cpp \
    $$PWD/src/TxtMessageHandler.cpp

# Additional include paths
INCLUDEPATH += \
    $$PWD/src

# Define config macros for conditional compilation
DEFINES += LOGGERD_LIBRARY

# Optional: define version if needed
VERSION = 1.0.0

# Export the configuration so it can be used by other projects
CONFIG += link_pkgconfig
PKGCONFIG += $$LIBRARY_NAME

# End of loggerd.pri
