# cmake_minimum_required(VERSION 3.10)
# project(obd-access VERSION 0.1)

# set(CMAKE_CXX_STANDARD 20)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++2a")

# find_package(Qt5 COMPONENTS Bluetooth REQUIRED)

# set(CMAKE_AUTOMOC ON)
# set(CMAKE_AUTORCC ON)
# set(CMAKE_AUTOUIC ON)

# find_program(CLANG_TIDY_EXE NAMES "clang-tidy")
# set(CLANG_TIDY_COMMAND "${CLANG_TIDY_EXE}" )

# add_library(${PROJECT_NAME} SHARED
# device.hpp
# obd-access.hpp
# usb-obd-access.hpp
# bluetooth-provider.hpp
# usb-serial-provider.hpp
# bluetooth-obd-access.hpp
# logging.hpp
# bluetooth-provider.cpp
# bluetooth-obd-access.cpp
# device.cpp
# obd-access.cpp
# usb-obd-access.cpp
# usb-serial-provider.cpp
# logging.cpp
# system-calls.hpp
# )

# set_target_properties(${PROJECT_NAME} PROPERTIES CXX_CLANG_TIDY "${CLANG_TIDY_COMMAND}")
# target_link_libraries(${PROJECT_NAME} Qt5::Bluetooth)