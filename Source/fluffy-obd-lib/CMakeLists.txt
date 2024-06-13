cmake_minimum_required(VERSION 3.16)
project(fluffy-obd-lib
  VERSION 0.1
  LANGUAGES CXX)

add_library(
  ${PROJECT_NAME}
  obd-access/bluetooth-provider.cpp
  obd-access/bluetooth-obd-access.cpp
  obd-access/device.cpp
  obd-access/obd-access.cpp
  obd-access/serial-obd-access.cpp
  obd-access/obd-serial-provider.cpp
  diagnostics-engine/base/diagnostics-engine.cpp
  diagnostics-engine/base/response.cpp
  diagnostics-engine/elm327/elm327-command-repository.cpp
  diagnostics-engine/elm327/elm327-data-decoder.cpp
  diagnostics-engine/elm327/elm327-data-parser.cpp
  diagnostics-engine/elm327/elm327-engine.cpp)

find_program(CLANG_TIDY_EXE NAMES "clang-tidy")

set_target_properties(${PROJET_NAME} PROPERTIES
  CMAKE_CXX_CLANG_TIDY "${CLANG_TIDY_EXE}"
  CMAKE_CXX_STANDARD 20
  CMAKE_CXX_STANDARD_REQUIRED ON
  CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++2a"
  LINKER_LANGUAGE CXX
  CMAKE_AUTOMOC ON
  CMAKE_AUTORCC ON
  CMAKE_AUTOUIC ON
)

target_include_directories(
  ${PROJECT_NAME}
  PUBLIC obd-access/include diagnostics-engine/base/include
  diagnostics-engine/elm327/decoders diagnostics-engine/elm327/include)

find_package(
  Qt5
  COMPONENTS Bluetooth
  REQUIRED)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)
target_link_libraries(${PROJECT_NAME} Qt5::Bluetooth)
