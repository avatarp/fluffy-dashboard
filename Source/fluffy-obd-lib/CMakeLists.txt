cmake_minimum_required(VERSION 3.10)
project(fluffy-obd-lib VERSION 0.1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++2a")

message("Compiler Version: ${CMAKE_CXX_COMPILER_VERSION}")

find_program(CLANG_TIDY_EXE NAMES "clang-tidy")
find_package(Qt5 COMPONENTS Bluetooth REQUIRED)
set(CLANG_TIDY_COMMAND "${CLANG_TIDY_EXE}" )
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

add_library(${PROJECT_NAME}

obd-access/bluetooth-provider.cpp
obd-access/bluetooth-obd-access.cpp
obd-access/device.cpp
obd-access/obd-access.cpp
obd-access/serial-obd-access.cpp
obd-access/obd-serial-provider.cpp
obd-access/logging.cpp

diagnostics-engine/base/dtc-handler.cpp
diagnostics-engine/base/diagnostics-engine.cpp
diagnostics-engine/base/response.cpp

diagnostics-engine/elm327/elm327-command-repository.cpp
diagnostics-engine/elm327/elm327-data-decoder.cpp
diagnostics-engine/elm327/elm327-data-parser.cpp
diagnostics-engine/elm327/elm327-engine.cpp

)

target_include_directories(${PROJECT_NAME} 
PUBLIC obd-access/include 
PUBLIC diagnostics-engine/base/include
PUBLIC diagnostics-engine/elm327/decoders
PUBLIC diagnostics-engine/elm327/include)

set_target_properties(${PROJECT_NAME} PROPERTIES CXX_CLANG_TIDY "${CLANG_TIDY_COMMAND}")
set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(${PROJECT_NAME} Qt5::Bluetooth)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)