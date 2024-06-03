cmake_minimum_required(VERSION 3.16)
project(lib-unit-test
LANGUAGES CXX)

find_package(GTest REQUIRED)
include(GoogleTest)
enable_testing()

add_executable(
  ${PROJECT_NAME}
  main.cpp
  bluetooth-obd-access.h
  obd-access-utils.h
  usb-obd-access.h
  mocks/mock-obd-access.hpp
  elm327/command-repo.h
  elm327/decoders.h
  elm327/live-data.h
  elm327/parser.h)

find_program(CLANG_TIDY_EXE NAMES "clang-tidy")

set_target_properties(${PROJECT_NAME} PROPERTIES
  CMAKE_CXX_STANDARD 20
  CMAKE_CXX_CLANG_TIDY "${CLANG_TIDY_EXE}"
)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)
add_subdirectory(../../../fluffy-obd-lib/ fluffy-obd-lib/)

target_link_libraries(
  ${PROJECT_NAME}
  fluffy-obd-lib
  gtest
  gmock
  gtest_main
  gmock_main
  pthread)

add_test(${PROJECT_NAME} ${PROJECT_NAME})
