find_package(GTest REQUIRED)
include(GoogleTest)
enable_testing()

add_executable(
  fluffy-obd-ut
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

set_target_properties(
  fluffy-obd-ut PROPERTIES CMAKE_CXX_STANDARD 20 CMAKE_CXX_CLANG_TIDY
  "${CLANG_TIDY_EXE}")

target_compile_features(fluffy-obd-ut PRIVATE cxx_std_20)

target_link_libraries(
  fluffy-obd-ut
  fluffy-obd-lib
  gtest
  gmock
  gtest_main
  gmock_main
  pthread)

add_test(fluffy-obd-ut fluffy-obd-ut)
