QT       += core gui
QT       += bluetooth
QT       += charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QMAKE_CC = gcc-11
QMAKE_CXX = g++-11

QMAKE_CXXFLAGS += -std=c++2a
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

HEADERS += \
    mainwindow.h \
    obd-access/bluetooth-obd-access.h \
    obd-access/bluetooth-provider.h \
    obd-access/device.h \
    obd-access/obd-access.h \
    obd-access/usb-obd-access.h \
    obd-access/usb-serial-provider.h \
    parameters-engine/Decoders/DecodeAirFlow.h \
    parameters-engine/Decoders/DecodeBitEncoded.h \
    parameters-engine/Decoders/DecodeDTC.h \
    parameters-engine/Decoders/DecodeEquivalenceRatio.h \
    parameters-engine/Decoders/DecodeEvapPressure.h \
    parameters-engine/Decoders/DecodeFuelPressure.h \
    parameters-engine/Decoders/DecodeFuelRailPressure.h \
    parameters-engine/Decoders/DecodeOxygenSensorCurrent.h \
    parameters-engine/Decoders/DecodeOxygenSensorVoltage.h \
    parameters-engine/Decoders/DecodePercentage.h \
    parameters-engine/Decoders/DecodeRPM.h \
    parameters-engine/Decoders/DecodeSimpleA.h \
    parameters-engine/Decoders/DecodeSimpleAB.h \
    parameters-engine/Decoders/DecodeStrategy.h \
    parameters-engine/Decoders/DecodeTemperature.h \
    parameters-engine/Decoders/DecodeTimingAdvance.h \
    parameters-engine/ELM327/elm327-command-repository.h \
    parameters-engine/ELM327/elm327-data-decoder.h \
    parameters-engine/ELM327/elm327-data-filter.h \
    parameters-engine/ELM327/elm327-dtc-handler.h \
    parameters-engine/ELM327/elm327-engine.h \
    parameters-engine/command-repository.h \
    parameters-engine/data-decoding-handler.h \
    parameters-engine/data-filters.h \
    parameters-engine/dtc-handler.h \
    parameters-engine/obd-command-pid.h \
    parameters-engine/parameters-engine.h \
    parameters-engine/response.h \
    utils/system-calls.h

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    obd-access/bluetooth-obd-access.cpp \
    obd-access/bluetooth-provider.cpp \
    obd-access/device.cpp \
    obd-access/obd-access.cpp \
    obd-access/usb-obd-access.cpp \
    obd-access/usb-serial-provider.cpp \
    parameters-engine/ELM327/elm327-command-repository.cpp \
    parameters-engine/ELM327/elm327-data-decoder.cpp \
    parameters-engine/ELM327/elm327-data-filter.cpp \
    parameters-engine/ELM327/elm327-dtc-handler.cpp \
    parameters-engine/ELM327/elm327-engine.cpp \
    parameters-engine/dtc-handler.cpp \
    parameters-engine/parameters-engine.cpp \
    parameters-engine/response.cpp

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res/icons.qrc

DISTFILES +=
