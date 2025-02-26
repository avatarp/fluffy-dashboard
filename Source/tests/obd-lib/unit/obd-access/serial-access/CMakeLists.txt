add_executable(
  serial-access-ut
  main.cpp
  ../../mocks/obd-access-mock.hpp
  ../../common/obd-access-utils.h
  serial-obd-access-test.h)

set_target_properties(
  serial-access-ut PROPERTIES CMAKE_CXX_STANDARD 20)

target_compile_features(serial-access-ut PRIVATE cxx_std_20)

target_link_libraries(
  serial-access-ut
  fluffy-obd-lib
  gtest
  gmock
  gtest_main
  gmock_main
  pthread)

add_test(serial-access-ut serial-access-ut)

if(${ENABLE_WARNINGS})
    test_target_set_warnings(
        TARGET
        serial-access-ut
        ENABLE
        ${ENABLE_WARNINGS}
        AS_ERRORS
        ${ENABLE_WARNINGS_AS_ERRORS})
endif()