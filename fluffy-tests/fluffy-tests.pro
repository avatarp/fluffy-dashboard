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
        ../DecodeFloatStrategy.h \
        ../DecodeRPM.h \
        ../DecodeSimpleA.h \
        ../DecodeTemperature.h \
        ../DecodePercentage.h \
        ../DecodeAirFlow.h \
        ../DecodeTimingAdvance.h \
        ../DecodeFuelPressure.h \
        ../DecodeRunTime.h \
        ../DecodeFuelRailPressure.h \
        ../DecodeOxygenSensorVoltage.h \
        ../DecodeEquivalenceRatio.h \
        ../DecodeOxygenSensorCurrent.h \
        decorders.h
SOURCES += \
        main.cpp \
        ../obd.cpp \
        ../utils.cpp
