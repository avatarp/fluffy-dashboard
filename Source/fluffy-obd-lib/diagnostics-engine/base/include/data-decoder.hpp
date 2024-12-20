#ifndef DATA_DECODING_HANDLER_HPP_
#define DATA_DECODING_HANDLER_HPP_

#include <bitset>
#include <functional>
#include <optional>
#include <string>
#include <utility>

class DataDecoder {
public:
    DataDecoder() = default;
    virtual ~DataDecoder() = default;
    /////////////////////////////////////////////////////////////////////////////////////
    // Service 01 Show current data
    // Service 02 Show freeze frame data
    // Commands below are interchangeable for both services
    /////////////////////////////////////////////////////////////////////////////////////
    // 00 PIDs supported [01 - 20]
    virtual std::bitset<32>
    GetSupportedPIDs1(const std::string& data) = 0;

    // 01 Monitor status since DTCs cleared
    virtual std::bitset<32> GetMonitorStatus(const std::string& data) = 0;

    // 02 Freeze DTC => DTC
    virtual std::string GetFreezeDTCs(const std::string& data) = 0;

    // 03 Fuel system status => enum
    virtual std::bitset<32> GetFuelSystemStatus(const std::string& data) = 0;

    // 04 Calculated engine load => %
    virtual float GetEngineLoad(const std::string& data) = 0;

    // 05 Engine coolant temperature => °C
    virtual float GetEngineCoolantTemperature(const std::string& data) = 0;

    // 06 Short term fuel trim—Bank 1 => %
    virtual float GetShortTermFuelTrimBank1(const std::string& data) = 0;

    // 07 Long term fuel trim—Bank 1 => %
    virtual float GetLongTermFuelTrimBank1(const std::string& data) = 0;

    // 08 Short term fuel trim—Bank 2 => %
    virtual float GetShortTermFuelTrimBank2(const std::string& data) = 0;

    // 09 Long term fuel trim—Bank 2 => %
    virtual float GetLongTermFuelTrimBank2(const std::string& data) = 0;

    // 0A Fuel pressure => kPa
    virtual float GetFuelPressure(const std::string& data) = 0;

    // 0B Intake manifold absolute pressure => kPa
    virtual float GetIntakeManifoldPressure(const std::string& data) = 0;

    // 0C Engine rpm => rpm
    virtual float GetEngineRpm(const std::string& data) = 0;

    // 0D Vehicle speed => km/h
    virtual float GetSpeed(const std::string& data) = 0;

    // 0E Timing advance => ° before TDC
    virtual float GetTimingAdvance(const std::string& data) = 0;

    // 0E Intake air temperature => °C
    virtual float GetIntakeAirTemperature(const std::string& data) = 0;

    // 10 Mass air flow sensor (MAF) air flow rate => g/s
    virtual float GetMafAirFlowRate(const std::string& data) = 0;

    // 11 Throttle position => %
    virtual float GetThrottlePosition(const std::string& data) = 0;

    // 12 Commanded secondary air status => enum
    virtual std::bitset<32> GetSecondaryAirStatus(const std::string& data) = 0;

    // 13 Oxygen sensors present
    virtual std::bitset<32> GetOxygenSensorsPresent1(const std::string& data) = 0;

    // 14 Oxygen Sensor 1
    // voltage, Short term fuel trim => V, %
    virtual std::pair<float, float> GetOxygenSensorFtV1(const std::string& data) = 0;

    // 15 Oxygen Sensor 2
    // voltage, Short term fuel trim => V, %
    virtual std::pair<float, float> GetOxygenSensorFtV2(const std::string& data) = 0;

    // 16 Oxygen Sensor 3
    // voltage, Short term fuel trim => V, %
    virtual std::pair<float, float> GetOxygenSensorFtV3(const std::string& data) = 0;

    // 17 Oxygen Sensor 4
    // voltage, Short term fuel trim => V, %
    virtual std::pair<float, float> GetOxygenSensorFtV4(const std::string& data) = 0;

    // 18 Oxygen Sensor 5
    // voltage, Short term fuel trim => V, %
    virtual std::pair<float, float> GetOxygenSensorFtV5(const std::string& data) = 0;

    // 19 Oxygen Sensor 6
    // voltage, Short term fuel trim => V, %
    virtual std::pair<float, float> GetOxygenSensorFtV6(const std::string& data) = 0;

    // 1A Oxygen Sensor 7
    // voltage, Short term fuel trim => V, %
    virtual std::pair<float, float> GetOxygenSensorFtV7(const std::string& data) = 0;

    // 1B Oxygen Sensor 8
    // voltage, Short term fuel trim => V, %
    virtual std::pair<float, float> GetOxygenSensorFtV8(const std::string& data) = 0;

    // 1C OBD standard => Enum
    virtual std::bitset<32> GetObdStandard(const std::string& data) = 0;

    // 1D Oxygen sensors present
    virtual std::bitset<32> GetOxygenSensorsPresent2(const std::string& data) = 0;

    // 1E Auxiliary input status
    virtual std::bitset<32> GetAuxiliaryInputStatus(const std::string& data) = 0;

    // 1F Run time since engine start => s
    virtual float GetRunTime(const std::string& data) = 0;

    // 20 PIDs supported [21 - 40]
    virtual std::bitset<32> GetSupportedPIDs2(const std::string& data) = 0;

    // 21 Distance traveled with malfunction indicator lamp (MIL) on => km
    virtual float GetDistanceWithMilOn(const std::string& data) = 0;

    // 22 Fuel Rail Pressure (relative to manifold vacuum) => kPa
    virtual float GetFuelRailPressure(const std::string& data) = 0;

    // 23 Fuel Rail Gauge Pressure (diesel/gasoline direct injection) => kPa
    virtual float GetFuelRailGaugePressure(const std::string& data) = 0;

    // 24 Oxygen Sensor 1
    // Air-Fuel Equivalence Ratio (lambda,λ), voltage => ratio, V
    virtual std::pair<float, float> GetOxygenSensorEqV1(const std::string& data) = 0;

    // 25 Oxygen Sensor 2
    // Air-Fuel Equivalence Ratio (lambda,λ), voltage => ratio, V
    virtual std::pair<float, float> GetOxygenSensorEqV2(const std::string& data) = 0;

    // 26 Oxygen Sensor 3
    // Air-Fuel Equivalence Ratio (lambda,λ), voltage => ratio, V
    virtual std::pair<float, float> GetOxygenSensorEqV3(const std::string& data) = 0;

    // 27 Oxygen Sensor 4
    // Air-Fuel Equivalence Ratio (lambda,λ), voltage => ratio, V
    virtual std::pair<float, float> GetOxygenSensorEqV4(const std::string& data) = 0;

    // 28 Oxygen Sensor 5
    // Air-Fuel Equivalence Ratio (lambda,λ), voltage => ratio, V
    virtual std::pair<float, float> GetOxygenSensorEqV5(const std::string& data) = 0;

    // 29 Oxygen Sensor 6
    // Air-Fuel Equivalence Ratio (lambda,λ), voltage => ratio, V
    virtual std::pair<float, float> GetOxygenSensorEqV6(const std::string& data) = 0;

    // 2A Oxygen Sensor 7
    // Air-Fuel Equivalence Ratio (lambda,λ), voltage => ratio, V
    virtual std::pair<float, float> GetOxygenSensorEqV7(const std::string& data) = 0;

    // 2B Oxygen sensor 8
    // air-fuel equivalence ratio (lambda,λ), voltage => ratio, V
    virtual std::pair<float, float> GetOxygenSensorEqV8(const std::string& data) = 0;

    // 2C Commanded EGR => %
    virtual float GetCommandedEgr(const std::string& data) = 0;

    // 2D EGR error => %
    virtual float GetEgrError(const std::string& data) = 0;

    // 2E Commanded evaporative purge  => %
    virtual float GetCommandedEvaporativePurge(const std::string& data) = 0;

    // 2F Fuel tank level input => %
    virtual float GetFuelTankLevelInput(const std::string& data) = 0;

    // 30 Warm-ups since codes cleared => count
    virtual float GetWarmupsSinceDtcCleared(const std::string& data) = 0;

    // 31 Distance traveled since codes cleared => km
    virtual float GetDistanceSinceDtcCleared(const std::string& data) = 0;

    // 32 Evap. System Vapor Pressure  => Pa
    virtual float GetEvapVaporPressure(const std::string& data) = 0;

    // 33 Absolute Barometric Pressure => kPa
    virtual float GetAbsoluteBarometricPressure(const std::string& data) = 0;

    // 34 Oxygen Sensor 1
    // Air-Fuel Equivalence Ratio (lambda,λ), current => ratio, mA
    virtual std::pair<float, float> GetOxygenSensorEqC1(const std::string& data) = 0;

    // 35 Oxygen Sensor 2
    // Air-Fuel Equivalence Ratio (lambda,λ), current => ratio, mA
    virtual std::pair<float, float> GetOxygenSensorEqC2(const std::string& data) = 0;

    // 36 Oxygen Sensor 3
    // Air-Fuel Equivalence Ratio (lambda,λ), current => ratio, mA
    virtual std::pair<float, float> GetOxygenSensorEqC3(const std::string& data) = 0;

    // 37 Oxygen Sensor 4
    // Air-Fuel Equivalence Ratio (lambda,λ), current => ratio, mA
    virtual std::pair<float, float> GetOxygenSensorEqC4(const std::string& data) = 0;

    // 38 Oxygen Sensor 5
    // Air-Fuel Equivalence Ratio (lambda,λ), current => ratio, mA
    virtual std::pair<float, float> GetOxygenSensorEqC5(const std::string& data) = 0;

    // 39 Oxygen Sensor 6
    // Air-Fuel Equivalence Ratio (lambda,λ), current => ratio, mA
    virtual std::pair<float, float> GetOxygenSensorEqC6(const std::string& data) = 0;

    // 3A Oxygen Sensor 7
    // Air-Fuel Equivalence Ratio (lambda,λ), current => ratio, mA
    virtual std::pair<float, float> GetOxygenSensorEqC7(const std::string& data) = 0;

    // 3B Oxygen sensor 8
    // air-fuel equivalence ratio (lambda,λ), current => ratio, mA
    virtual std::pair<float, float> GetOxygenSensorEqC8(const std::string& data) = 0;

    // 3C Catalyst Temperature: Bank 1, Sensor 1 => °C
    virtual float GetCatalystTemperatureB1S1(const std::string& data) = 0;

    // 3D Catalyst Temperature: Bank 2, Sensor 1 => °C
    virtual float GetCatalystTemperatureB2S1(const std::string& data) = 0;

    // 3E Catalyst Temperature: Bank 1, Sensor 2 => °C
    virtual float GetCatalystTemperatureB1S2(const std::string& data) = 0;

    // 3F Catalyst Temperature: Bank 2, Sensor 2 => °C
    virtual float GetCatalystTemperatureB2S2(const std::string& data) = 0;

    /////////////////////////////////////////////////////////////////////////////////////
    // 09 Request vehicle information
    /////////////////////////////////////////////////////////////////////////////////////

    // 00 Service 9 supported PIDs [0-20]
    virtual std::bitset<32> GetSupportedVIPIDs(const std::string& data) = 0;

    // 01 VIN Message Count
    // Only for ISO 9141-2, ISO 14230-4 and SAE J1850.
    virtual float GetVinMessageCount(const std::string& data) = 0;

    // 02 VIN
    virtual std::string GetVin(const std::string& data) = 0;

    // 03 Calibration ID Message Count
    virtual float GetCalibrationIdMessageCount(const std::string& data) = 0;

    // 04 Calibration ID
    virtual std::string GetCalibrationId(const std::string& data) = 0;

    // 05 Calibration Verification Numbers Message Count
    virtual float GetCalibrationVerificationNumbersMessageCount(const std::string& data) = 0;

    // 06 Calibration Verification Numbers
    virtual std::string GetCalibrationVerificationNumbers(const std::string& data) = 0;

    // 07 In-use performance tracking message count for 08 and 0B
    // Only for ISO 9141-2, ISO 14230-4 and SAE J1850.
    virtual float GetPerformanceTrackingMessageCount(const std::string& data) = 0;

    // 08 In-use performance tracking for spark ignition vehicles
    virtual std::string GetPerformanceTracking1(const std::string& data) = 0;

    // 09 ECU name message count
    virtual float GetEcuNameMessageCount(const std::string& data) = 0;

    // 0A ECU name
    virtual std::string GetEcuName(const std::string& data) = 0;

    // 0B In-use performance tracking for compression ignition vehicles
    virtual std::string GetPerformanceTracking2(const std::string& data) = 0;
};

#endif // DATA_DECODING_HANDLER_HPP_