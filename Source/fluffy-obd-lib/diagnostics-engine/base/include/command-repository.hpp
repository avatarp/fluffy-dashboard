#ifndef COMMAND_REPOSITORY_HPP_
#define COMMAND_REPOSITORY_HPP_

#include <string>

class CommandRepository {
public:
    CommandRepository() {};
    // SID 01
    //###########################################################################
    // 00 PIDs supported [01 - 20]
    virtual std::string GetSupportedPIDs1() = 0;

    // 01 Monitor status since DTCs cleared
    virtual std::string GetMonitorStatus() = 0;

    // 02 Freeze DTC => DTC
    virtual std::string GetFreezeDTCs() = 0;

    // 03 Fuel system status => enum
    virtual std::string GetFuelSystemStatus() = 0;

    // 04 Calculated engine load => %
    virtual std::string GetEngineLoad() = 0;

    // 05 Engine coolant temperature => °C
    virtual std::string GetEngineCoolantTemperature() = 0;

    // 06 Short term fuel trim—Bank 1 => %
    virtual std::string GetShortTermFuelTrimBank1() = 0;

    // 07 Long term fuel trim—Bank 1 => %
    virtual std::string GetLongTermFuelTrimBank1() = 0;

    // 08 Short term fuel trim—Bank 2 => %
    virtual std::string GetShortTermFuelTrimBank2() = 0;

    // 09 Long term fuel trim—Bank 2 => %
    virtual std::string GetLongTermFuelTrimBank2() = 0;

    // 0A Fuel pressure => kPa
    virtual std::string GetFuelPressure() = 0;

    // 0B Intake manifold absolute pressure => kPa
    virtual std::string GetIntakeManifoldPressure() = 0;

    // 0C Engine rpm => rpm
    virtual std::string GetEngineRpm() = 0;

    // 0D Vehicle speed => km/h
    virtual std::string GetSpeed() = 0;

    // 0E Timing advance => ° before TDC
    virtual std::string GetTimingAdvance() = 0;

    // 0F Intake air temperature => °C
    virtual std::string GetIntakeAirTemperature() = 0;

    // 10 Mass air flow sensor () air flow rate => g/s
    virtual std::string GetMafAirFlowRate() = 0;

    // 11 Throttle position => %
    virtual std::string GetThrottlePosition() = 0;

    // 12 Commanded secondary air status => enum
    virtual std::string GetSecondaryAirStatus() = 0;

    // 13 Oxygen sensors present
    virtual std::string GetOxygenSensorsPresent1() = 0;

    // 14 Oxygen Sensor 1
    // voltage, Short term fuel trim => V, %
    virtual std::string GetOxygenSensorFtV1() = 0;

    // 15 Oxygen Sensor 2
    // voltage, Short term fuel trim => V, %
    virtual std::string GetOxygenSensorFtV2() = 0;

    // 16 Oxygen Sensor 3
    // voltage, Short term fuel trim => V, %
    virtual std::string GetOxygenSensorFtV3() = 0;

    // 17 Oxygen Sensor 4
    // voltage, Short term fuel trim => V, %
    virtual std::string GetOxygenSensorFtV4() = 0;

    // 18 Oxygen Sensor 5
    // voltage, Short term fuel trim => V, %
    virtual std::string GetOxygenSensorFtV5() = 0;

    // 19 Oxygen Sensor 6
    // voltage, Short term fuel trim => V, %
    virtual std::string GetOxygenSensorFtV6() = 0;

    // 1A Oxygen Sensor 7
    // voltage, Short term fuel trim => V, %
    virtual std::string GetOxygenSensorFtV7() = 0;

    // 1B Oxygen Sensor 8
    // voltage, Short term fuel trim => V, %
    virtual std::string GetOxygenSensorFtV8() = 0;

    // 1C OBD standard => Enum
    virtual std::string GetObdStandard() = 0;

    // 1D Oxygen sensors present
    virtual std::string GetOxygenSensorsPresent2() = 0;

    // 1E Auxiliary input status
    virtual std::string GetAuxiliaryInputStatus() = 0;

    // 1F Run time since engine start => s
    virtual std::string GetRunTime() = 0;

    // 20 PIDs supported [21 - 40]
    virtual std::string GetSupportedPIDs2() = 0;

    // 21 Distance traveled with malfunction indicator lamp () on => km
    virtual std::string GetDistanceWithMilOn() = 0;

    // 22 Fuel Rail Pressure () => kPa
    virtual std::string GetFuelRailPressure() = 0;

    // 23 Fuel Rail Gauge Pressure () => kPa
    virtual std::string GetFuelRailGaugePressure() = 0;

    // 24 Oxygen Sensor 1
    // Air-Fuel Equivalence Ratio (), voltage => ratio, V
    virtual std::string GetOxygenSensorEqV1() = 0;

    // 25 Oxygen Sensor 2
    // Air-Fuel Equivalence Ratio (), voltage => ratio, V
    virtual std::string GetOxygenSensorEqV2() = 0;

    // 26 Oxygen Sensor 3
    // Air-Fuel Equivalence Ratio (), voltage => ratio, V
    virtual std::string GetOxygenSensorEqV3() = 0;

    // 27 Oxygen Sensor 4
    // Air-Fuel Equivalence Ratio (), voltage => ratio, V
    virtual std::string GetOxygenSensorEqV4() = 0;

    // 28 Oxygen Sensor 5
    // Air-Fuel Equivalence Ratio (), voltage => ratio, V
    virtual std::string GetOxygenSensorEqV5() = 0;

    // 29 Oxygen Sensor 6
    // Air-Fuel Equivalence Ratio (), voltage => ratio, V
    virtual std::string GetOxygenSensorEqV6() = 0;

    // 2A Oxygen Sensor 7
    // Air-Fuel Equivalence Ratio (), voltage => ratio, V
    virtual std::string GetOxygenSensorEqV7() = 0;

    // 2B Oxygen sensor 8
    // air-fuel equivalence ratio (), voltage => ratio, V
    virtual std::string GetOxygenSensorEqV8() = 0;

    // 2C Commanded EGR => %
    virtual std::string GetCommandedEgr() = 0;

    // 2D EGR error => %
    virtual std::string GetEgrError() = 0;

    // 2E Commanded evaporative purge  => %
    virtual std::string GetCommandedEvaporativePurge() = 0;

    // 2F Fuel tank level input => %
    virtual std::string GetFuelTankLevelInput() = 0;

    // 30 Warm-ups since codes cleared => count
    virtual std::string GetWarmupsSinceDtcCleared() = 0;

    // 31 Distance traveled since codes cleared => km
    virtual std::string GetDistanceSinceDtcCleared() = 0;

    // 32 Evap. System Vapor Pressure  => Pa
    virtual std::string GetEvapVaporPressure() = 0;

    // 33 Absolute Barometric Pressure => kPa
    virtual std::string GetAbsoluteBarometricPressure() = 0;

    // 34 Oxygen Sensor 1
    // Air-Fuel Equivalence Ratio (), current => ratio, mA
    virtual std::string GetOxygenSensorEqC1() = 0;

    // 35 Oxygen Sensor 2
    // Air-Fuel Equivalence Ratio (), current => ratio, mA
    virtual std::string GetOxygenSensorEqC2() = 0;

    // 36 Oxygen Sensor 3
    // Air-Fuel Equivalence Ratio (), current => ratio, mA
    virtual std::string GetOxygenSensorEqC3() = 0;

    // 37 Oxygen Sensor 4
    // Air-Fuel Equivalence Ratio (), current => ratio, mA
    virtual std::string GetOxygenSensorEqC4() = 0;

    // 38 Oxygen Sensor 5
    // Air-Fuel Equivalence Ratio (), current => ratio, mA
    virtual std::string GetOxygenSensorEqC5() = 0;

    // 39 Oxygen Sensor 6
    // Air-Fuel Equivalence Ratio (), current => ratio, mA
    virtual std::string GetOxygenSensorEqC6() = 0;

    // 3A Oxygen Sensor 7
    // Air-Fuel Equivalence Ratio (), current => ratio, mA
    virtual std::string GetOxygenSensorEqC7() = 0;

    // 3B Oxygen sensor 8
    // air-fuel equivalence ratio (), current => ratio, mA
    virtual std::string GetOxygenSensorEqC8() = 0;

    // 3C Catalyst Temperature: Bank 1, Sensor 1 => °C
    virtual std::string GetCatalystTemperatureB1S1() = 0;

    // 3D Catalyst Temperature: Bank 2, Sensor 1 => °C
    virtual std::string GetCatalystTemperatureB2S1() = 0;

    // 3E Catalyst Temperature: Bank 1, Sensor 2 => °C
    virtual std::string GetCatalystTemperatureB1S2() = 0;

    // 3F Catalyst Temperature: Bank 2, Sensor 2 => °C
    virtual std::string GetCatalystTemperatureB2S2() = 0;
};

#endif // COMMAND_REPOSITORY_HPP_