cmake_minimum_required(VERSION 3.16.3)
project(diagnostics-engine)

find_program(CLANG_TIDY_EXE NAMES "clang-tidy")
set(CLANG_TIDY_COMMAND "${CLANG_TIDY_EXE}" )

add_library(diagnostics-engine 

base/command-repository.hpp
base/data-decoding-handler.hpp
base/data-filters.hpp
base/dtc-handler.hpp
base/dtc-handler.cpp
base/obd-command-pid.hpp
base/diagnostics-engine.cpp
base/diagnostics-engine.hpp
base/response.cpp
base/response.hpp

elm327/elm327-command-repository.cpp
elm327/elm327-command-repository.hpp
elm327/elm327-data-decoder.cpp
elm327/elm327-data-decoder.hpp
elm327/elm327-data-parser.cpp
elm327/elm327-data-parser.hpp
elm327/elm327-dtc-handler.hpp
elm327/elm327-engine.cpp
elm327/elm327-engine.hpp

elm327/decoders/Decode.hpp
elm327/decoders/DecodeAirFlow.hpp
elm327/decoders/DecodeDTC.hpp
elm327/decoders/DecodeEquivalenceRatio.hpp
elm327/decoders/DecodeEvapPressure.hpp
elm327/decoders/DecodeFuelPressure.hpp
elm327/decoders/DecodeFuelRailPressure.hpp
elm327/decoders/DecodeOxygenSensorCurrent.hpp
elm327/decoders/DecodeOxygenSensorVoltage.hpp
elm327/decoders/DecodePercentage.hpp
elm327/decoders/DecodeRPM.hpp
elm327/decoders/DecodeCountA.hpp
elm327/decoders/DecodeCountAB.hpp
elm327/decoders/DecodeTemperature.hpp
elm327/decoders/DecodeTimingAdvance.hpp
)

set_target_properties(${PROJECT_NAME} PROPERTIES CXX_CLANG_TIDY "${CLANG_TIDY_COMMAND}")