QT       += core gui
QT       += bluetooth

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QMAKE_CC = gcc-11
QMAKE_CXX = g++-11

QMAKE_CXXFLAGS += -std=c++20
CONFIG += c++20

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    obd-access/bluetooth-obd-access.cpp \
    obd-access/bluetooth-provider.cpp \
    obd-access/device.cpp \
    obd-access/obd-access.cpp \
    obd-access/usb-obd-access.cpp \
    obd.cpp \
    utils.cpp

HEADERS += \
    Decoders/DecodeAirFlow.h \
    Decoders/DecodeBitEncoded.h \
    Decoders/DecodeEquivalenceRatio.h \
    Decoders/DecodeEvapPressure.h \
    Decoders/DecodeFuelPressure.h \
    Decoders/DecodeFuelRailPressure.h \
    Decoders/DecodeFuelTrim.h \
    Decoders/DecodeOxygenSensorCurrent.h \
    Decoders/DecodeOxygenSensorVoltage.h \
    Decoders/DecodePercentage.h \
    Decoders/DecodeRPM.h \
    Decoders/DecodeSimpleA.h \
    Decoders/DecodeSimpleAB.h \
    Decoders/DecodeStrategy.h \
    Decoders/DecodeTemperature.h \
    Decoders/DecodeTimingAdvance.h \
    mainwindow.h \
    obd-access/bluetooth-obd-access.h \
    obd-access/bluetooth-provider.h \
    obd-access/device.h \
    obd-access/obd-access.h \
    obd-access/usb-obd-access.h \
    obd.h \
    utils.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
