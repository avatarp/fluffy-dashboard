cmake_minimum_required(VERSION 3.10)
project(obd-access VERSION 0.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Bluetooth REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

add_library(${PROJECT_NAME} SHARED
device.h
obd-access.h
usb-obd-access.h
bluetooth-provider.h
usb-serial-provider.h
 bluetooth-obd-access.h
 bluetooth-provider.cpp
 bluetooth-obd-access.cpp
 device.cpp
 obd-access.cpp
 usb-obd-access.cpp
 usb-serial-provider.cpp
)

qt5_use_modules(${PROJECT_NAME} Bluetooth)

target_link_libraries(${PROJECT_NAME} Qt5::Bluetooth)