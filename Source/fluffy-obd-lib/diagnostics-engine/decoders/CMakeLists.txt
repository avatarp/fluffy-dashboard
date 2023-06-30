cmake_minimum_required(VERSION 3.10)
project(decoders VERSION 0.1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++2a")


add_library(${PROJECT_NAME} SHARED
 Decode.hpp
 DecodeAirFlow.hpp
 DecodeDTC.hpp
 DecodeEquivalenceRatio.hpp
 DecodeEvapPressure.hpp
 DecodeFuelPressure.hpp
 DecodeFuelRailPressure.hpp
 DecodeOxygenSensorCurrent.hpp
 DecodeOxygenSensorVoltage.hpp
 DecodePercentage.hpp
 DecodeRPM.hpp
 DecodeCountA.hpp
 DecodeCountAB.hpp
 DecodeTemperature.hpp
 DecodeTimingAdvance.hpp
)

set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)