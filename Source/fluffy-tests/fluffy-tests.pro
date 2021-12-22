include(gtest_dependency.pri)

TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG += thread
CONFIG -= qt
CONFIG += c++17

HEADERS += \
        ../obd.h \
        ../utils.h \
        ../Decoders \
        decorders.h
SOURCES += \
        main.cpp \
        ../obd.cpp \
        ../utils.cpp
