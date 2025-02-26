add_subdirectory(bluetooth-access)
add_subdirectory(serial-access)

add_executable(
  obd-access-ut
  main.cpp
  obd-access-test.h)

set_target_properties(
  obd-access-ut PROPERTIES CMAKE_CXX_STANDARD 20)

target_compile_features(obd-access-ut PRIVATE cxx_std_20)

target_link_libraries(
  obd-access-ut
  fluffy-obd-lib
  gtest
  gmock
  gtest_main
  gmock_main
  pthread)

add_test(obd-access-ut obd-access-ut)

if(${ENABLE_WARNINGS})
    test_target_set_warnings(
        TARGET
        obd-access-ut
        ENABLE
        ${ENABLE_WARNINGS}
        AS_ERRORS
        ${ENABLE_WARNINGS_AS_ERRORS})
endif()