#pragma once
#include "../data-decoding-handler.h"
#include "../Decoders/DecodeBitEncoded.h"
#include "../Decoders/DecodePercentage.h"
#include "../Decoders/DecodeTemperature.h"
#include "../Decoders/DecodeFuelPressure.h"
#include "../Decoders/DecodeEvapPressure.h"
#include "../Decoders/DecodeSimpleA.h"
#include "../Decoders/DecodeSimpleAB.h"
#include "../Decoders/DecodeRPM.h"
#include "../Decoders/DecodeTimingAdvance.h"
#include "../Decoders/DecodeAirFlow.h"
#include "../Decoders/DecodeOxygenSensorVoltage.h"
#include "../Decoders/DecodeOxygenSensorCurrent.h"
#include "../Decoders/DecodeFuelRailPressure.h"
#include "../Decoders/DecodeEquivalenceRatio.h"

class Elm327DataDecoder : public DataDecodingHandler
{
public:
    Elm327DataDecoder();

    //00 PIDs supported [01 - 20]
    virtual std::optional <std::bitset<32>>
    GetSupportedPIDs1(const std::string& data);

    //01 Monitor status since DTCs cleared
    virtual std::optional <std::bitset<32>>
    GetMonitorStatus(const std::string& data);

    //02 Freeze DTC => DTC
    virtual std::optional <std::string>
    GetFreezeDTCs(const std::string& data);

    //03 Fuel system status => enum
    virtual std::optional <std::bitset<32>>
    GetFuelSystemStatus(const std::string& data);

    //04 Calculated engine load => %
    virtual std::optional <float>
    GetEngineLoad(const std::string& data);

    //05 Engine coolant temperature => °C
    virtual std::optional <float>
    GetEngineCoolantTemperature(const std::string& data);

    //06 Short term fuel trim—Bank 1 => %
    virtual std::optional <float>
    GetShortTermFuelTrimBank1(const std::string& data);

    //07 Long term fuel trim—Bank 1 => %
    virtual std::optional <float>
    GetLongTermFuelTrimBank1(const std::string& data);

    //08 Short term fuel trim—Bank 2 => %
    virtual std::optional <float>
    GetShortTermFuelTrimBank2(const std::string& data);

    //09 Long term fuel trim—Bank 2 => %
    virtual std::optional <float>
    GetLongTermFuelTrimBank2(const std::string& data);

    //0A Fuel pressure => kPa
    virtual std::optional <float>
    GetFuelPressure(const std::string& data);

    //0B Intake manifold absolute pressure => kPa
    virtual std::optional <float>
    GetIntakeManifoldPressure(const std::string& data);

    //0C Engine rpm => rpm
    virtual std::optional <float>
    GetEngineRpm(const std::string& data);

    //0D Vehicle speed => km/h
    virtual std::optional <float>
    GetSpeed(const std::string& data);

    //0E Timing advance => ° before TDC
    virtual std::optional <float>
    GetTimingAdvance(const std::string& data);

    //0E Intake air temperature => °C
    virtual std::optional <float>
    GetIntakeAirTemperature(const std::string& data);

    //10 Mass air flow sensor (MAF) air flow rate => g/s
    virtual std::optional <float>
    GetMafAirFlowRate(const std::string& data);

    //11 Throttle position => %
    virtual std::optional <float>
    GetThrottlePosition(const std::string& data);

    //12 Commanded secondary air status => enum
    virtual std::optional <std::bitset<32>>
    GetSecondaryAirStatus(const std::string& data);

    //13 Oxygen sensors present
    virtual std::optional <std::bitset<32>>
    GetOxygenSensorsPresent1(const std::string& data);

    //14 Oxygen Sensor 1
    //voltage, Short term fuel trim => V, %
    virtual std::optional <std::pair<std::optional<float>, std::optional<float>>>
    GetOxygenSensorFtV1(const std::string& data);

    //15 Oxygen Sensor 2
    //voltage, Short term fuel trim => V, %
    virtual std::optional <std::pair<std::optional<float>, std::optional<float>>>
    GetOxygenSensorFtV2(const std::string& data);

    //16 Oxygen Sensor 3
    //voltage, Short term fuel trim => V, %
    virtual std::optional <std::pair<std::optional<float>, std::optional<float>>>
    GetOxygenSensorFtV3(const std::string& data);

    //17 Oxygen Sensor 4
    //voltage, Short term fuel trim => V, %
    virtual std::optional <std::pair<std::optional<float>, std::optional<float>>>
    GetOxygenSensorFtV4(const std::string& data);

    //18 Oxygen Sensor 5
    //voltage, Short term fuel trim => V, %
    virtual std::optional <std::pair<std::optional<float>, std::optional<float>>>
    GetOxygenSensorFtV5(const std::string& data);

    //19 Oxygen Sensor 6
    //voltage, Short term fuel trim => V, %
    virtual std::optional <std::pair<std::optional<float>, std::optional<float>>>
    GetOxygenSensorFtV6(const std::string& data);

    //1A Oxygen Sensor 7
    //voltage, Short term fuel trim => V, %
    virtual std::optional <std::pair<std::optional<float>, std::optional<float>>>
    GetOxygenSensorFtV7(const std::string& data);

    //1B Oxygen Sensor 8
    //voltage, Short term fuel trim => V, %
    virtual std::optional <std::pair<std::optional<float>, std::optional<float>>>
    GetOxygenSensorFtV8(const std::string& data);

    //1C OBD standard => Enum
    virtual std::optional <std::bitset<32>>
    GetObdStandard(const std::string& data);

    //1D Oxygen sensors present
    virtual std::optional <std::bitset<32>>
    GetOxygenSensorsPresent2(const std::string& data);

    //1E Auxiliary input status
    virtual std::optional <std::bitset<32>>
    GetAuxiliaryInputStatus(const std::string& data);

    //1F Run time since engine start => s
    virtual std::optional <float>
    GetRunTime(const std::string& data);

    //20 PIDs supported [21 - 40]
    virtual std::optional <std::bitset<32>>
    GetSupportedPIDs2(const std::string& data);

    //21 Distance traveled with malfunction indicator lamp (MIL) on => km
    virtual std::optional <float>
    GetDistanceWithMilOn(const std::string& data);

    //22 Fuel Rail Pressure (relative to manifold vacuum) => kPa
    virtual std::optional <float>
    GetFuelRailPressure(const std::string& data);

    //23 Fuel Rail Gauge Pressure (diesel/gasoline direct injection) => kPa
    virtual std::optional <float>
    GetFuelRailGaugePressure(const std::string& data);

    //24 Oxygen Sensor 1
    //Air-Fuel Equivalence Ratio (lambda,λ), voltage => ratio, V
    virtual std::optional <std::pair<std::optional<float>, std::optional<float>>>
    GetOxygenSensorEqV1(const std::string& data);

    //25 Oxygen Sensor 2
    //Air-Fuel Equivalence Ratio (lambda,λ), voltage => ratio, V
    virtual std::optional <std::pair<std::optional<float>, std::optional<float>>>
    GetOxygenSensorEqV2(const std::string& data);

    //26 Oxygen Sensor 3
    //Air-Fuel Equivalence Ratio (lambda,λ), voltage => ratio, V
    virtual std::optional <std::pair<std::optional<float>, std::optional<float>>>
    GetOxygenSensorEqV3(const std::string& data);

    //27 Oxygen Sensor 4
    //Air-Fuel Equivalence Ratio (lambda,λ), voltage => ratio, V
    virtual std::optional <std::pair<std::optional<float>, std::optional<float>>>
    GetOxygenSensorEqV4(const std::string& data);

    //28 Oxygen Sensor 5
    //Air-Fuel Equivalence Ratio (lambda,λ), voltage => ratio, V
    virtual std::optional <std::pair<std::optional<float>, std::optional<float>>>
    GetOxygenSensorEqV5(const std::string& data);

    //29 Oxygen Sensor 6
    //Air-Fuel Equivalence Ratio (lambda,λ), voltage => ratio, V
    virtual std::optional <std::pair<std::optional<float>, std::optional<float>>>
    GetOxygenSensorEqV6(const std::string& data);

    //2A Oxygen Sensor 7
    //Air-Fuel Equivalence Ratio (lambda,λ), voltage => ratio, V
    virtual std::optional <std::pair<std::optional<float>, std::optional<float>>>
    GetOxygenSensorEqV7(const std::string& data);

    //2B Oxygen sensor 8
    //air-fuel equivalence ratio (lambda,λ), voltage => ratio, V
    virtual std::optional <std::pair<std::optional<float>, std::optional<float>>>
    GetOxygenSensorEqV8(const std::string& data);

    //2C Commanded EGR => %
    virtual std::optional <float>
    GetCommandedEgr(const std::string& data);

    //2D EGR error => %
    virtual std::optional <float>
    GetEgrError(const std::string& data);

    //2E Commanded evaporative purge  => %
    virtual std::optional <float>
    GetCommandedEvaporativePurge(const std::string& data);

    //2F Fuel tank level input => %
    virtual std::optional <float>
    GetFuelTankLevelInput(const std::string& data);

    //30 Warm-ups since codes cleared => count
    virtual std::optional <float>
    GetWarmupsSinceDtcCleared(const std::string& data);

    //31 Distance traveled since codes cleared => km
    virtual std::optional <float>
    GetDistanceSinceDtcCleared(const std::string& data);

    //32 Evap. System Vapor Pressure  => Pa
    virtual std::optional <float>
    GetEvapVaporPressure(const std::string& data);

    //33 Absolute Barometric Pressure => kPa
    virtual std::optional <float>
    GetAbsoluteBarometricPressure(const std::string& data);

    //34 Oxygen Sensor 1
    //Air-Fuel Equivalence Ratio (lambda,λ), current => ratio, mA
    virtual std::optional <std::pair<std::optional<float>, std::optional<float>>>
    GetOxygenSensorEqC1(const std::string& data);

    //35 Oxygen Sensor 2
    //Air-Fuel Equivalence Ratio (lambda,λ), current => ratio, mA
    virtual std::optional <std::pair<std::optional<float>, std::optional<float>>>
    GetOxygenSensorEqC2(const std::string& data);

    //36 Oxygen Sensor 3
    //Air-Fuel Equivalence Ratio (lambda,λ), current => ratio, mA
    virtual std::optional <std::pair<std::optional<float>, std::optional<float>>>
    GetOxygenSensorEqC3(const std::string& data);

    //37 Oxygen Sensor 4
    //Air-Fuel Equivalence Ratio (lambda,λ), current => ratio, mA
    virtual std::optional <std::pair<std::optional<float>, std::optional<float>>>
    GetOxygenSensorEqC4(const std::string& data);

    //38 Oxygen Sensor 5
    //Air-Fuel Equivalence Ratio (lambda,λ), current => ratio, mA
    virtual std::optional <std::pair<std::optional<float>, std::optional<float>>>
    GetOxygenSensorEqC5(const std::string& data);

    //39 Oxygen Sensor 6
    //Air-Fuel Equivalence Ratio (lambda,λ), current => ratio, mA
    virtual std::optional <std::pair<std::optional<float>, std::optional<float>>>
    GetOxygenSensorEqC6(const std::string& data);

    //3A Oxygen Sensor 7
    //Air-Fuel Equivalence Ratio (lambda,λ), current => ratio, mA
    virtual std::optional <std::pair<std::optional<float>, std::optional<float>>>
    GetOxygenSensorEqC7(const std::string& data);

    //3B Oxygen sensor 8
    //air-fuel equivalence ratio (lambda,λ), current => ratio, mA
    virtual std::optional <std::pair<std::optional<float>, std::optional<float>>>
    GetOxygenSensorEqC8(const std::string& data);

    //3C Catalyst Temperature: Bank 1, Sensor 1 => °C
    virtual std::optional <float>
    GetCatalystTemperatureB1S1(const std::string& data);

    //3D Catalyst Temperature: Bank 2, Sensor 1 => °C
    virtual std::optional <float>
    GetCatalystTemperatureB2S1(const std::string& data);

    //3E Catalyst Temperature: Bank 1, Sensor 2 => °C
    virtual std::optional <float>
    GetCatalystTemperatureB1S2(const std::string& data);

    //3F Catalyst Temperature: Bank 2, Sensor 2 => °C
    virtual std::optional <float>
    GetCatalystTemperatureB2S2(const std::string& data);

    /////////////////////////////////////////////////////////////////////////////////////
    //09 Request vehicle information
    /////////////////////////////////////////////////////////////////////////////////////

    //00 Service 9 supported PIDs [0-20]
    virtual std::optional <std::bitset<32>>
    GetSupportedVIPIDs(const std::string& data);

    //01 VIN Message Count
    //Only for ISO 9141-2, ISO 14230-4 and SAE J1850.
    virtual std::optional <float>
    GetVinMessageCount(const std::string& data);

    //02 VIN
    virtual std::optional <std::string>
    GetVin(const std::string& data);

    //03 Calibration ID Message Count
    virtual std::optional <float>
    GetCalibrationIdMessageCount(const std::string& data);

    //04 Calibration ID
    virtual std::optional <std::string>
    GetCalibrationId(const std::string& data);

    //05 Calibration Verification Numbers Message Count
    virtual std::optional <float>
    GetCalibrationVerificationNumbersMessageCount(const std::string& data);

    //06 Calibration Verification Numbers
    virtual std::optional <std::string>
    GetCalibrationVerificationNumbers(const std::string& data);

    //07 In-use performance tracking message count for 08 and 0B
    //Only for ISO 9141-2, ISO 14230-4 and SAE J1850.
    virtual std::optional <float>
    GetPerformanceTrackingMessageCount(const std::string& data);

    //08 In-use performance tracking for spark ignition vehicles
    virtual std::optional <std::string>
    GetPerformanceTracking1(const std::string& data);

    //09 ECU name message count
    virtual std::optional <float>
    GetEcuNameMessageCount(const std::string& data);

    //0A ECU name
    virtual std::optional <std::string>
    GetEcuName(const std::string& data);

    //0B In-use performance tracking for compression ignition vehicles
    virtual std::optional <std::string>
    GetPerformanceTracking2(const std::string& data);
};

