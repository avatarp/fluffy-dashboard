#ifndef ELM327_DATA_DECODER_HPP_
#define ELM327_DATA_DECODER_HPP_

#include "data-decoder.hpp"
#include "response.hpp"

#include <functional>
#include <unordered_map>

class Elm327DataDecoder : public DataDecoder {

    using FunctionType = DecodedData (Elm327DataDecoder::*)(const std::string&);

    struct decoderFunction {
        FunctionType function;
        DataType dataType;
    };

    static std::unordered_map<ObdCommandPid, decoderFunction> getDecodingMap();

public:
    Elm327DataDecoder() = default;

    virtual void decodeResponse(Response& response) override;

    // 00 PIDs supported [01 - 20]
    virtual DecodedData
    GetSupportedPIDs1(const std::string& data);

    // 01 Monitor status since DTCs cleared
    virtual DecodedData
    GetMonitorStatus(const std::string& data);

    // 02 Freeze DTC => DTC
    virtual DecodedData
    GetFreezeDTCs(const std::string& data);

    // 03 Fuel system status => enum
    virtual DecodedData
    GetFuelSystemStatus(const std::string& data);

    // 04 Calculated engine load => %
    virtual DecodedData
    GetEngineLoad(const std::string& data);

    // 05 Engine coolant temperature => °C
    virtual DecodedData
    GetEngineCoolantTemperature(const std::string& data);

    // 06 Short term fuel trim—Bank 1 => %
    virtual DecodedData
    GetShortTermFuelTrimBank1(const std::string& data);

    // 07 Long term fuel trim—Bank 1 => %
    virtual DecodedData
    GetLongTermFuelTrimBank1(const std::string& data);

    // 08 Short term fuel trim—Bank 2 => %
    virtual DecodedData
    GetShortTermFuelTrimBank2(const std::string& data);

    // 09 Long term fuel trim—Bank 2 => %
    virtual DecodedData
    GetLongTermFuelTrimBank2(const std::string& data);

    // 0A Fuel pressure => kPa
    virtual DecodedData
    GetFuelPressure(const std::string& data);

    // 0B Intake manifold absolute pressure => kPa
    virtual DecodedData
    GetIntakeManifoldPressure(const std::string& data);

    // 0C Engine rpm => rpm
    virtual DecodedData
    GetEngineRpm(const std::string& data);

    // 0D Vehicle speed => km/h
    virtual DecodedData
    GetSpeed(const std::string& data);

    // 0E Timing advance => ° before TDC
    virtual DecodedData
    GetTimingAdvance(const std::string& data);

    // 0E Intake air temperature => °C
    virtual DecodedData
    GetIntakeAirTemperature(const std::string& data);

    // 10 Mass air flow sensor (MAF) air flow rate => g/s
    virtual DecodedData
    GetMafAirFlowRate(const std::string& data);

    // 11 Throttle position => %
    virtual DecodedData
    GetThrottlePosition(const std::string& data);

    // 12 Commanded secondary air status => enum
    virtual DecodedData
    GetSecondaryAirStatus(const std::string& data);

    // 13 Oxygen sensors present
    virtual DecodedData
    GetOxygenSensorsPresent1(const std::string& data);

    // 14 Oxygen Sensor 1
    // voltage, Short term fuel trim => V, %
    virtual DecodedData
    GetOxygenSensorFtV1(const std::string& data);

    // 15 Oxygen Sensor 2
    // voltage, Short term fuel trim => V, %
    virtual DecodedData
    GetOxygenSensorFtV2(const std::string& data);

    // 16 Oxygen Sensor 3
    // voltage, Short term fuel trim => V, %
    virtual DecodedData
    GetOxygenSensorFtV3(const std::string& data);

    // 17 Oxygen Sensor 4
    // voltage, Short term fuel trim => V, %
    virtual DecodedData
    GetOxygenSensorFtV4(const std::string& data);

    // 18 Oxygen Sensor 5
    // voltage, Short term fuel trim => V, %
    virtual DecodedData
    GetOxygenSensorFtV5(const std::string& data);

    // 19 Oxygen Sensor 6
    // voltage, Short term fuel trim => V, %
    virtual DecodedData
    GetOxygenSensorFtV6(const std::string& data);

    // 1A Oxygen Sensor 7
    // voltage, Short term fuel trim => V, %
    virtual DecodedData
    GetOxygenSensorFtV7(const std::string& data);

    // 1B Oxygen Sensor 8
    // voltage, Short term fuel trim => V, %
    virtual DecodedData
    GetOxygenSensorFtV8(const std::string& data);

    // 1C OBD standard => Enum
    virtual DecodedData
    GetObdStandard(const std::string& data);

    // 1D Oxygen sensors present
    virtual DecodedData
    GetOxygenSensorsPresent2(const std::string& data);

    // 1E Auxiliary input status
    virtual DecodedData
    GetAuxiliaryInputStatus(const std::string& data);

    // 1F Run time since engine start => s
    virtual DecodedData
    GetRunTime(const std::string& data);

    // 20 PIDs supported [21 - 40]
    virtual DecodedData
    GetSupportedPIDs2(const std::string& data);

    // 21 Distance traveled with malfunction indicator lamp (MIL) on => km
    virtual DecodedData
    GetDistanceWithMilOn(const std::string& data);

    // 22 Fuel Rail Pressure (relative to manifold vacuum) => kPa
    virtual DecodedData
    GetFuelRailPressure(const std::string& data);

    // 23 Fuel Rail Gauge Pressure (diesel/gasoline direct injection) => kPa
    virtual DecodedData
    GetFuelRailGaugePressure(const std::string& data);

    // 24 Oxygen Sensor 1
    // Air-Fuel Equivalence Ratio (lambda,λ), voltage => ratio, V
    virtual DecodedData
    GetOxygenSensorEqV1(const std::string& data);

    // 25 Oxygen Sensor 2
    // Air-Fuel Equivalence Ratio (lambda,λ), voltage => ratio, V
    virtual DecodedData
    GetOxygenSensorEqV2(const std::string& data);

    // 26 Oxygen Sensor 3
    // Air-Fuel Equivalence Ratio (lambda,λ), voltage => ratio, V
    virtual DecodedData
    GetOxygenSensorEqV3(const std::string& data);

    // 27 Oxygen Sensor 4
    // Air-Fuel Equivalence Ratio (lambda,λ), voltage => ratio, V
    virtual DecodedData
    GetOxygenSensorEqV4(const std::string& data);

    // 28 Oxygen Sensor 5
    // Air-Fuel Equivalence Ratio (lambda,λ), voltage => ratio, V
    virtual DecodedData
    GetOxygenSensorEqV5(const std::string& data);

    // 29 Oxygen Sensor 6
    // Air-Fuel Equivalence Ratio (lambda,λ), voltage => ratio, V
    virtual DecodedData
    GetOxygenSensorEqV6(const std::string& data);

    // 2A Oxygen Sensor 7
    // Air-Fuel Equivalence Ratio (lambda,λ), voltage => ratio, V
    virtual DecodedData
    GetOxygenSensorEqV7(const std::string& data);

    // 2B Oxygen sensor 8
    // air-fuel equivalence ratio (lambda,λ), voltage => ratio, V
    virtual DecodedData
    GetOxygenSensorEqV8(const std::string& data);

    // 2C Commanded EGR => %
    virtual DecodedData
    GetCommandedEgr(const std::string& data);

    // 2D EGR error => %
    virtual DecodedData
    GetEgrError(const std::string& data);

    // 2E Commanded evaporative purge  => %
    virtual DecodedData
    GetCommandedEvaporativePurge(const std::string& data);

    // 2F Fuel tank level input => %
    virtual DecodedData
    GetFuelTankLevelInput(const std::string& data);

    // 30 Warm-ups since codes cleared => count
    virtual DecodedData
    GetWarmupsSinceDtcCleared(const std::string& data);

    // 31 Distance traveled since codes cleared => km
    virtual DecodedData
    GetDistanceSinceDtcCleared(const std::string& data);

    // 32 Evap. System Vapor Pressure  => Pa
    virtual DecodedData
    GetEvapVaporPressure(const std::string& data);

    // 33 Absolute Barometric Pressure => kPa
    virtual DecodedData
    GetAbsoluteBarometricPressure(const std::string& data);

    // 34 Oxygen Sensor 1
    // Air-Fuel Equivalence Ratio (lambda,λ), current => ratio, mA
    virtual DecodedData
    GetOxygenSensorEqC1(const std::string& data);

    // 35 Oxygen Sensor 2
    // Air-Fuel Equivalence Ratio (lambda,λ), current => ratio, mA
    virtual DecodedData
    GetOxygenSensorEqC2(const std::string& data);

    // 36 Oxygen Sensor 3
    // Air-Fuel Equivalence Ratio (lambda,λ), current => ratio, mA
    virtual DecodedData
    GetOxygenSensorEqC3(const std::string& data);

    // 37 Oxygen Sensor 4
    // Air-Fuel Equivalence Ratio (lambda,λ), current => ratio, mA
    virtual DecodedData
    GetOxygenSensorEqC4(const std::string& data);

    // 38 Oxygen Sensor 5
    // Air-Fuel Equivalence Ratio (lambda,λ), current => ratio, mA
    virtual DecodedData
    GetOxygenSensorEqC5(const std::string& data);

    // 39 Oxygen Sensor 6
    // Air-Fuel Equivalence Ratio (lambda,λ), current => ratio, mA
    virtual DecodedData
    GetOxygenSensorEqC6(const std::string& data);

    // 3A Oxygen Sensor 7
    // Air-Fuel Equivalence Ratio (lambda,λ), current => ratio, mA
    virtual DecodedData
    GetOxygenSensorEqC7(const std::string& data);

    // 3B Oxygen sensor 8
    // air-fuel equivalence ratio (lambda,λ), current => ratio, mA
    virtual DecodedData
    GetOxygenSensorEqC8(const std::string& data);

    // 3C Catalyst Temperature: Bank 1, Sensor 1 => °C
    virtual DecodedData
    GetCatalystTemperatureB1S1(const std::string& data);

    // 3D Catalyst Temperature: Bank 2, Sensor 1 => °C
    virtual DecodedData
    GetCatalystTemperatureB2S1(const std::string& data);

    // 3E Catalyst Temperature: Bank 1, Sensor 2 => °C
    virtual DecodedData
    GetCatalystTemperatureB1S2(const std::string& data);

    // 3F Catalyst Temperature: Bank 2, Sensor 2 => °C
    virtual DecodedData
    GetCatalystTemperatureB2S2(const std::string& data);

    /////////////////////////////////////////////////////////////////////////////////////
    // 09 Request vehicle information
    /////////////////////////////////////////////////////////////////////////////////////

    // 00 Service 9 supported PIDs [0-20]
    virtual DecodedData
    GetSupportedVIPIDs(const std::string& data);

    // 01 VIN Message Count
    // Only for ISO 9141-2, ISO 14230-4 and SAE J1850.
    virtual DecodedData
    GetVinMessageCount(const std::string& data);

    // 02 VIN
    virtual DecodedData
    GetVin(const std::string& data);

    // 03 Calibration ID Message Count
    virtual DecodedData
    GetCalibrationIdMessageCount(const std::string& data);

    // 04 Calibration ID
    virtual DecodedData
    GetCalibrationId(const std::string& data);

    // 05 Calibration Verification Numbers Message Count
    virtual DecodedData
    GetCalibrationVerificationNumbersMessageCount(const std::string& data);

    // 06 Calibration Verification Numbers
    virtual DecodedData
    GetCalibrationVerificationNumbers(const std::string& data);

    // 07 In-use performance tracking message count for 08 and 0B
    // Only for ISO 9141-2, ISO 14230-4 and SAE J1850.
    virtual DecodedData
    GetPerformanceTrackingMessageCount(const std::string& data);

    // 08 In-use performance tracking for spark ignition vehicles
    virtual DecodedData
    GetPerformanceTracking1(const std::string& data);

    // 09 ECU name message count
    virtual DecodedData
    GetEcuNameMessageCount(const std::string& data);

    // 0A ECU name
    virtual DecodedData
    GetEcuName(const std::string& data);

    // 0B In-use performance tracking for compression ignition vehicles
    virtual DecodedData
    GetPerformanceTracking2(const std::string& data);
};

#endif // ELM327_DATA_DECODER_HPP_
