include(gtest_dependency.pri)
QT       += bluetooth

TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG += thread
#CONFIG -= qt
QMAKE_CC = gcc-11
QMAKE_CXX = g++-11

QMAKE_CXXFLAGS += -std=c++20
CONFIG += c++20

HEADERS += \
        ../core \
        bluetooth-obd-access.h \
        decorders.h \
        elm327-live-data.h \
        elm327/decorders.h \
        elm327/elm327-live-data.h \
        elm327/parser.h \
        obd-access-utils.h \
        usb-obd-access.h \
        ../core/utils/system-calls.h

SOURCES += \
    ../core/obd-access/bluetooth-obd-access.cpp \
    ../core/obd-access/bluetooth-provider.cpp \
    ../core/obd-access/device.cpp \
    ../core/obd-access/obd-access.cpp \
    ../core/obd-access/usb-obd-access.cpp \
    ../core/obd-access/usb-serial-provider.cpp \
    ../core/parameters-engine/ELM327/elm327-command-repository.cpp \
    ../core/parameters-engine/ELM327/elm327-data-decoder.cpp \
    ../core/parameters-engine/ELM327/elm327-dtc-handler.cpp \
    ../core/parameters-engine/ELM327/elm327-engine.cpp \
    ../core/parameters-engine/ELM327/elm327-data-filter.cpp \
    ../core/parameters-engine/dtc-handler.cpp \
    ../core/parameters-engine/parameters-engine.cpp \
    ../core/parameters-engine/response.cpp \
    main.cpp

