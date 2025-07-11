add_library(
  ${PROJECT_NAME}
  obd-access/bluetooth-provider.cpp
  obd-access/bluetooth-obd-access.cpp
  obd-access/obd-access.cpp
  obd-access/serial-obd-access.cpp
  obd-access/obd-serial-provider.cpp
  CommandProcessor/interface/ICommandProcessor.cpp
  CommandProcessor/interface/response.cpp
  CommandProcessor/elm327/elm327-command-repository.cpp
  CommandProcessor/elm327/elm327-data-decoder.cpp
  CommandProcessor/elm327/elm327-data-parser.cpp
  CommandProcessor/elm327/elm327-command-processor.cpp
  CommandProcessor/elm327/elm327-dtc-handler.cpp)

set_target_properties(${PROJECT_NAME} PROPERTIES
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
  PUBLIC obd-access/include CommandProcessor/interface/include
  CommandProcessor/elm327/decoders CommandProcessor/elm327/include)

find_package(spdlog REQUIRED)

find_package(
  Qt5
  COMPONENTS Bluetooth
  REQUIRED)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)
target_link_libraries(${PROJECT_NAME} spdlog::spdlog Qt5::Bluetooth)

if(${ENABLE_WARNINGS})
    target_set_warnings(
        TARGET
        ${PROJECT_NAME}
        ENABLE
        ${ENABLE_WARNINGS}
        AS_ERRORS
        ${ENABLE_WARNINGS_AS_ERRORS})
endif()

if(${ENABLE_CLANG_TIDY})
    add_clang_tidy_to_target(${PROJECT_NAME})
endif()
