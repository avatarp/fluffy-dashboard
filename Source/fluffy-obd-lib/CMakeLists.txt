cmake_minimum_required(VERSION 3.10)
project(fluffy-obd-lib VERSION 0.1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++2a")

message("Compiler Version: ${CMAKE_CXX_COMPILER_VERSION}")

add_subdirectory(obd-access)

find_program(CLANG_TIDY_EXE NAMES "clang-tidy")
find_package(Qt5 COMPONENTS Bluetooth REQUIRED)
set(CLANG_TIDY_COMMAND "${CLANG_TIDY_EXE}" )
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

add_library(${PROJECT_NAME}

obd-access/device.hpp
obd-access/obd-access.hpp
obd-access/usb-obd-access.hpp
obd-access/bluetooth-provider.hpp
obd-access/usb-serial-provider.hpp
obd-access/bluetooth-obd-access.hpp
obd-access/logging.hpp
obd-access/bluetooth-provider.cpp
obd-access/bluetooth-obd-access.cpp
obd-access/device.cpp
obd-access/obd-access.cpp
obd-access/usb-obd-access.cpp
obd-access/usb-serial-provider.cpp
obd-access/logging.cpp
obd-access/system-calls.hpp

diagnostics-engine/base/command-repository.hpp
diagnostics-engine/base/data-decoding-handler.hpp
diagnostics-engine/base/data-filters.hpp
diagnostics-engine/base/dtc-handler.hpp
diagnostics-engine/base/dtc-handler.cpp
diagnostics-engine/base/obd-command-pid.hpp
diagnostics-engine/base/diagnostics-engine.cpp
diagnostics-engine/base/diagnostics-engine.hpp
diagnostics-engine/base/response.cpp
diagnostics-engine/base/response.hpp

diagnostics-engine/elm327/elm327-command-repository.cpp
diagnostics-engine/elm327/elm327-command-repository.hpp
diagnostics-engine/elm327/elm327-data-decoder.cpp
diagnostics-engine/elm327/elm327-data-decoder.hpp
diagnostics-engine/elm327/elm327-data-parser.cpp
diagnostics-engine/elm327/elm327-data-parser.hpp
diagnostics-engine/elm327/elm327-dtc-handler.hpp
diagnostics-engine/elm327/elm327-engine.cpp
diagnostics-engine/elm327/elm327-engine.hpp

diagnostics-engine/elm327/decoders/Decode.hpp
diagnostics-engine/elm327/decoders/DecodeAirFlow.hpp
diagnostics-engine/elm327/decoders/DecodeDTC.hpp
diagnostics-engine/elm327/decoders/DecodeEquivalenceRatio.hpp
diagnostics-engine/elm327/decoders/DecodeEvapPressure.hpp
diagnostics-engine/elm327/decoders/DecodeFuelPressure.hpp
diagnostics-engine/elm327/decoders/DecodeFuelRailPressure.hpp
diagnostics-engine/elm327/decoders/DecodeOxygenSensorCurrent.hpp
diagnostics-engine/elm327/decoders/DecodeOxygenSensorVoltage.hpp
diagnostics-engine/elm327/decoders/DecodePercentage.hpp
diagnostics-engine/elm327/decoders/DecodeRPM.hpp
diagnostics-engine/elm327/decoders/DecodeCountA.hpp
diagnostics-engine/elm327/decoders/DecodeCountAB.hpp
diagnostics-engine/elm327/decoders/DecodeTemperature.hpp
diagnostics-engine/elm327/decoders/DecodeTimingAdvance.hpp
)

set_target_properties(${PROJECT_NAME} PROPERTIES CXX_CLANG_TIDY "${CLANG_TIDY_COMMAND}")
set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(${PROJECT_NAME} Qt5::Bluetooth)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)