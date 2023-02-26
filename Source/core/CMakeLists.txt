cmake_minimum_required(VERSION 3.10)
project(fluffy-obd VERSION 0.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Widgets Charts REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

add_subdirectory(obd-access)
#add_subdirectory(parameters-engine)
add_subdirectory(utils)

add_executable(${PROJECT_NAME}
 main.cpp
 mainwindow.h
 mainwindow.cpp 
)

qt5_use_modules(${PROJECT_NAME} Widgets Charts)

target_link_libraries(${PROJECT_NAME} obd-utils obd-access Qt5::Widgets Qt5::Charts)