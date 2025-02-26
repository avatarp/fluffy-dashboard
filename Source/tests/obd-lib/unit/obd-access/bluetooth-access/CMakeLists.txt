add_executable(
  bt-access-ut
  main.cpp
  ../../mocks/obd-access-mock.hpp
  ../../common/obd-access-utils.h
  bluetooth-obd-access-test.h)

set_target_properties(
  bt-access-ut PROPERTIES CMAKE_CXX_STANDARD 20)

target_compile_features(bt-access-ut PRIVATE cxx_std_20)

target_link_libraries(
  bt-access-ut
  fluffy-obd-lib
  gtest
  gmock
  gtest_main
  gmock_main
  pthread)

add_test(bt-access-ut bt-access-ut)

if(${ENABLE_WARNINGS})
    test_target_set_warnings(
        TARGET
        bt-access-ut
        ENABLE
        ${ENABLE_WARNINGS}
        AS_ERRORS
        ${ENABLE_WARNINGS_AS_ERRORS})
endif()