include(gtest_dependency.pri)

TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG += thread
CONFIG -= qt

QMAKE_CC = gcc-11
QMAKE_CXX = g++-11

QMAKE_CXXFLAGS += -std=c++20
CONFIG += c++20

HEADERS += \
        ../core \
        bluetooth-obd-access.h \
        decorders.h \
        obd-access-utils.h \
        usb-obd-access.h
SOURCES += \
        ../core/obd-access/bluetooth-obd-access.cpp \
        main.cpp \
        ../core/obd-access/device.cpp \
        ../core/obd-access/obd-access.cpp \
        ../core/obd-access/usb-obd-access.cpp \
        ../core/obd.cpp \
        ../core/utils.cpp
