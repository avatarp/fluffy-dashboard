#include "elm327-command-repository.hpp"

std::string Elm327CommandRepository::GetSupportedPIDs1()
{
    return std::string { "0100\r" };
}

std::string Elm327CommandRepository::GetMonitorStatus()
{
    return std::string { "0101\r" };
}

std::string Elm327CommandRepository::GetFreezeDTCs()
{
    return std::string { "0102\r" };
}

std::string Elm327CommandRepository::GetFuelSystemStatus()
{
    return std::string { "0103\r" };
}

std::string Elm327CommandRepository::GetEngineLoad()
{
    return std::string { "0104\r" };
}

std::string Elm327CommandRepository::GetEngineCoolantTemperature()
{
    return std::string { "0105\r" };
}

std::string Elm327CommandRepository::GetShortTermFuelTrimBank1()
{
    return std::string { "0106\r" };
}

std::string Elm327CommandRepository::GetLongTermFuelTrimBank1()
{
    return std::string { "0107\r" };
}

std::string Elm327CommandRepository::GetShortTermFuelTrimBank2()
{
    return std::string { "0108\r" };
}

std::string Elm327CommandRepository::GetLongTermFuelTrimBank2()
{
    return std::string { "0109\r" };
}

std::string Elm327CommandRepository::GetFuelPressure()
{
    return std::string { "010A\r" };
}

std::string Elm327CommandRepository::GetIntakeManifoldPressure()
{
    return std::string { "010B\r" };
}

std::string Elm327CommandRepository::GetEngineRpm()
{
    return std::string { "010C\r" };
}

std::string Elm327CommandRepository::GetSpeed()
{
    return std::string { "010D\r" };
}

std::string Elm327CommandRepository::GetTimingAdvance()
{
    return std::string { "010E\r" };
}

std::string Elm327CommandRepository::GetIntakeAirTemperature()
{
    return std::string { "010F\r" };
}

std::string Elm327CommandRepository::GetMafAirFlowRate()
{
    return std::string { "0110\r" };
}

std::string Elm327CommandRepository::GetThrottlePosition()
{
    return std::string { "0111\r" };
}

std::string Elm327CommandRepository::GetSecondaryAirStatus()
{
    return std::string { "0112\r" };
}

std::string Elm327CommandRepository::GetOxygenSensorsPresent1()
{
    return std::string { "0113\r" };
}

std::string Elm327CommandRepository::GetOxygenSensorFtV1()
{
    return std::string { "0114\r" };
}

std::string Elm327CommandRepository::GetOxygenSensorFtV2()
{
    return std::string { "0115\r" };
}

std::string Elm327CommandRepository::GetOxygenSensorFtV3()
{
    return std::string { "0116\r" };
}

std::string Elm327CommandRepository::GetOxygenSensorFtV4()
{
    return std::string { "0117\r" };
}

std::string Elm327CommandRepository::GetOxygenSensorFtV5()
{
    return std::string { "0118\r" };
}

std::string Elm327CommandRepository::GetOxygenSensorFtV6()
{
    return std::string { "0119\r" };
}

std::string Elm327CommandRepository::GetOxygenSensorFtV7()
{
    return std::string { "011A\r" };
}

std::string Elm327CommandRepository::GetOxygenSensorFtV8()
{
    return std::string { "011B\r" };
}

std::string Elm327CommandRepository::GetObdStandard()
{
    return std::string { "011C\r" };
}

std::string Elm327CommandRepository::GetOxygenSensorsPresent2()
{
    return std::string { "011D\r" };
}

std::string Elm327CommandRepository::GetAuxiliaryInputStatus()
{
    return std::string { "011E\r" };
}

std::string Elm327CommandRepository::GetRunTime()
{
    return std::string { "011F`\r" };
}

std::string Elm327CommandRepository::GetSupportedPIDs2()
{
    return std::string { "0120\r" };
}

std::string Elm327CommandRepository::GetDistanceWithMilOn()
{
    return std::string { "0121\r" };
}

std::string Elm327CommandRepository::GetFuelRailPressure()
{
    return std::string { "0122\r" };
}

std::string Elm327CommandRepository::GetFuelRailGaugePressure()
{
    return std::string { "0123\r" };
}

std::string Elm327CommandRepository::GetOxygenSensorEqV1()
{
    return std::string { "0124\r" };
}

std::string Elm327CommandRepository::GetOxygenSensorEqV2()
{
    return std::string { "0125\r" };
}

std::string Elm327CommandRepository::GetOxygenSensorEqV3()
{
    return std::string { "0126\r" };
}

std::string Elm327CommandRepository::GetOxygenSensorEqV4()
{
    return std::string { "0127\r" };
}

std::string Elm327CommandRepository::GetOxygenSensorEqV5()
{
    return std::string { "0128\r" };
}

std::string Elm327CommandRepository::GetOxygenSensorEqV6()
{
    return std::string { "0129\r" };
}

std::string Elm327CommandRepository::GetOxygenSensorEqV7()
{
    return std::string { "012A\r" };
}

std::string Elm327CommandRepository::GetOxygenSensorEqV8()
{
    return std::string { "012B\r" };
}

std::string Elm327CommandRepository::GetCommandedEgr()
{
    return std::string { "012C\r" };
}

std::string Elm327CommandRepository::GetEgrError()
{
    return std::string { "012D\r" };
}

std::string Elm327CommandRepository::GetCommandedEvaporativePurge()
{
    return std::string { "012E\r" };
}

std::string Elm327CommandRepository::GetFuelTankLevelInput()
{
    return std::string { "012F\r" };
}

std::string Elm327CommandRepository::GetWarmupsSinceDtcCleared()
{
    return std::string { "0130\r" };
}

std::string Elm327CommandRepository::GetDistanceSinceDtcCleared()
{
    return std::string { "0131\r" };
}

std::string Elm327CommandRepository::GetEvapVaporPressure()
{
    return std::string { "0132\r" };
}

std::string Elm327CommandRepository::GetAbsoluteBarometricPressure()
{
    return std::string { "0133\r" };
}

std::string Elm327CommandRepository::GetOxygenSensorEqC1()
{
    return std::string { "0134\r" };
}

std::string Elm327CommandRepository::GetOxygenSensorEqC2()
{
    return std::string { "0135\r" };
}

std::string Elm327CommandRepository::GetOxygenSensorEqC3()
{
    return std::string { "0136\r" };
}

std::string Elm327CommandRepository::GetOxygenSensorEqC4()
{
    return std::string { "0137\r" };
}

std::string Elm327CommandRepository::GetOxygenSensorEqC5()
{
    return std::string { "0138\r" };
}

std::string Elm327CommandRepository::GetOxygenSensorEqC6()
{
    return std::string { "0139\r" };
}

std::string Elm327CommandRepository::GetOxygenSensorEqC7()
{
    return std::string { "013A\r" };
}

std::string Elm327CommandRepository::GetOxygenSensorEqC8()
{
    return std::string { "013B\r" };
}

std::string Elm327CommandRepository::GetCatalystTemperatureB1S1()
{
    return std::string { "013C\r" };
}

std::string Elm327CommandRepository::GetCatalystTemperatureB2S1()
{
    return std::string { "013D\r" };
}

std::string Elm327CommandRepository::GetCatalystTemperatureB1S2()
{
    return std::string { "013E\r" };
}

std::string Elm327CommandRepository::GetCatalystTemperatureB2S2()
{
    return std::string { "013F\r" };
}
