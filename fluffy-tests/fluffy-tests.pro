include(gtest_dependency.pri)

TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG += thread
CONFIG -= qt

HEADERS += \
        tst_obd.h \
        ../obd.h \
        ../utils.h
SOURCES += \
        main.cpp \
        ../obd.cpp \
        ../utils.cpp
