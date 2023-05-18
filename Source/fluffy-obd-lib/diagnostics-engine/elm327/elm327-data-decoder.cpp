#include "elm327-data-decoder.hpp"


Elm327DataDecoder::Elm327DataDecoder()
{

}

std::bitset<32> Elm327DataDecoder::GetSupportedPIDs1(const std::string &data)
{
    DecodeBitEncoded decoder;
    return decoder.decode(data);
}


std::bitset<32> Elm327DataDecoder::GetMonitorStatus(const std::string &data)
{
    DecodeBitEncoded decoder;
    return decoder.decode(data);
}

std::string Elm327DataDecoder::GetFreezeDTCs(const std::string &data)
{
    DecodeString decoder;
    return decoder.decode(data);
}

std::bitset<32> Elm327DataDecoder::GetFuelSystemStatus(const std::string &data)
{
    DecodeBitEncoded decoder;
    return decoder.decode(data);
}

float Elm327DataDecoder::GetEngineLoad(const std::string &data)
{
    DecodePercentage decoder;
    return decoder.decode(data);
}

float Elm327DataDecoder::GetEngineCoolantTemperature(const std::string &data)
{
    DecodeTemperature decoder;
    return decoder.decode(data);
}

float Elm327DataDecoder::GetShortTermFuelTrimBank1(const std::string &data)
{
    DecodeSignedPercentage decoder;
    return decoder.decode(data);
}

float Elm327DataDecoder::GetLongTermFuelTrimBank1(const std::string &data)
{
    DecodeSignedPercentage decoder;
    return decoder.decode(data);
}

float Elm327DataDecoder::GetShortTermFuelTrimBank2(const std::string &data)
{
    DecodeSignedPercentage decoder;
    return decoder.decode(data);
}

float Elm327DataDecoder::GetLongTermFuelTrimBank2(const std::string &data)
{
    DecodeSignedPercentage decoder;
    return decoder.decode(data);
}

float Elm327DataDecoder::GetFuelPressure(const std::string &data)
{
    DecodeFuelPressure decoder;
    return decoder.decode(data);
}

float Elm327DataDecoder::GetIntakeManifoldPressure(const std::string &data)
{
    DecodeSimpleA decoder;
    return decoder.decode(data);
}

float Elm327DataDecoder::GetEngineRpm(const std::string &data)
{
    DecodeRPM decoder;
    return decoder.decode(data);
}

float Elm327DataDecoder::GetSpeed(const std::string &data)
{
    DecodeSimpleA decoder;
    return decoder.decode(data);
}

float Elm327DataDecoder::GetTimingAdvance(const std::string &data)
{
    DecodeTimingAdvance decoder;
    return decoder.decode(data);
}

float Elm327DataDecoder::GetIntakeAirTemperature(const std::string &data)
{
    DecodeTemperature decoder;
    return decoder.decode(data);
}

float Elm327DataDecoder::GetMafAirFlowRate(const std::string &data)
{
    DecodeAirFlow decoder;
    return decoder.decode(data);
}

float Elm327DataDecoder::GetThrottlePosition(const std::string &data)
{
    DecodePercentage decoder;
    return decoder.decode(data);
}

std::bitset<32> Elm327DataDecoder::GetSecondaryAirStatus(const std::string &data)
{
    DecodeBitEncoded decoder;
    return decoder.decode(data);
}

std::bitset<32> Elm327DataDecoder::GetOxygenSensorsPresent1(const std::string &data)
{
    DecodeBitEncoded decoder;
    return decoder.decode(data);
}

std::pair<float, float >
Elm327DataDecoder::GetOxygenSensorFtV1(const std::string &data)
{
    DecodeOxygenSensorVoltage1 voltageDecoder;
    DecodeSignedPercentage fuelTrimDecoder;
    return std::make_pair(voltageDecoder.decode(data.substr(0,1)),
                          fuelTrimDecoder.decode(data.substr(2,3)));
}

std::pair<float, float >
Elm327DataDecoder::GetOxygenSensorFtV2(const std::string &data)
{
    DecodeOxygenSensorVoltage1 voltageDecoder;
    DecodeSignedPercentage fuelTrimDecoder;
    return std::make_pair(voltageDecoder.decode(data.substr(0,1)),
                          fuelTrimDecoder.decode(data.substr(2,3)));
}

std::pair<float, float >
Elm327DataDecoder::GetOxygenSensorFtV3(const std::string &data)
{
    DecodeOxygenSensorVoltage1 voltageDecoder;
    DecodeSignedPercentage fuelTrimDecoder;
    return std::make_pair(voltageDecoder.decode(data.substr(0,1)),
                          fuelTrimDecoder.decode(data.substr(2,3)));
}

std::pair<float, float >
Elm327DataDecoder::GetOxygenSensorFtV4(const std::string &data)
{
    DecodeOxygenSensorVoltage1 voltageDecoder;
    DecodeSignedPercentage fuelTrimDecoder;
    return std::make_pair(voltageDecoder.decode(data.substr(0,1)),
                          fuelTrimDecoder.decode(data.substr(2,3)));
}

std::pair<float, float >
Elm327DataDecoder::GetOxygenSensorFtV5(const std::string &data)
{
    DecodeOxygenSensorVoltage1 voltageDecoder;
    DecodeSignedPercentage fuelTrimDecoder;
    return std::make_pair(voltageDecoder.decode(data.substr(0,1)),
                          fuelTrimDecoder.decode(data.substr(2,3)));
}

std::pair<float, float >
Elm327DataDecoder::GetOxygenSensorFtV6(const std::string &data)
{
    DecodeOxygenSensorVoltage1 voltageDecoder;
    DecodeSignedPercentage fuelTrimDecoder;
    return std::make_pair(voltageDecoder.decode(data.substr(0,1)),
                          fuelTrimDecoder.decode(data.substr(2,3)));
}

std::pair<float, float >
Elm327DataDecoder::GetOxygenSensorFtV7(const std::string &data)
{
    DecodeOxygenSensorVoltage1 voltageDecoder;
    DecodeSignedPercentage fuelTrimDecoder;
    return std::make_pair(voltageDecoder.decode(data.substr(0,1)),
                          fuelTrimDecoder.decode(data.substr(2,3)));
}

std::pair<float, float >
Elm327DataDecoder::GetOxygenSensorFtV8(const std::string &data)
{
    DecodeOxygenSensorVoltage1 voltageDecoder;
    DecodeSignedPercentage fuelTrimDecoder;
    return std::make_pair(voltageDecoder.decode(data.substr(0,1)),
                          fuelTrimDecoder.decode(data.substr(2,3)));
}

std::bitset<32> Elm327DataDecoder::GetObdStandard(const std::string &data)
{
    DecodeBitEncoded decoder;
    return decoder.decode(data);
}


std::bitset<32> Elm327DataDecoder::GetOxygenSensorsPresent2(const std::string &data)
{
    DecodeBitEncoded decoder;
    return decoder.decode(data);
}

std::bitset<32> Elm327DataDecoder::GetAuxiliaryInputStatus(const std::string &data)
{
    DecodeBitEncoded decoder;
    return decoder.decode(data);
}

float Elm327DataDecoder::GetRunTime(const std::string &data)
{
    DecodeCountAB decoder;
    return decoder.decode(data);
}

std::bitset<32> Elm327DataDecoder::GetSupportedPIDs2(const std::string &data)
{
    DecodeBitEncoded decoder;
    return decoder.decode(data);
}


float Elm327DataDecoder::GetDistanceWithMilOn(const std::string &data)
{
    DecodeCountAB decoder;
    return decoder.decode(data);
}

float Elm327DataDecoder::GetFuelRailPressure(const std::string &data)
{
    DecodeFuelRailPressure decoder;
    return decoder.decode(data);
}

float Elm327DataDecoder::GetFuelRailGaugePressure(const std::string &data)
{
    DecodeFuelRailGaugePressure decoder;
    return decoder.decode(data);
}

std::pair<float, float> Elm327DataDecoder::GetOxygenSensorEqV1(const std::string &data)
{
    DecodeEquivalenceRatio eqRatioDecoder;
    DecodeOxygenSensorVoltage2 voltageDecoder;
    return std::make_pair(eqRatioDecoder.decode(data.substr(0,1)),
                          voltageDecoder.decode(data.substr(2,3)));
}

std::pair<float, float> Elm327DataDecoder::GetOxygenSensorEqV2(const std::string &data)
{
    DecodeEquivalenceRatio eqRatioDecoder;
    DecodeOxygenSensorVoltage2 voltageDecoder;
    return std::make_pair(eqRatioDecoder.decode(data.substr(0,1)),
                          voltageDecoder.decode(data.substr(2,3)));
}

std::pair<float, float> Elm327DataDecoder::GetOxygenSensorEqV3(const std::string &data)
{
    DecodeEquivalenceRatio eqRatioDecoder;
    DecodeOxygenSensorVoltage2 voltageDecoder;
    return std::make_pair(eqRatioDecoder.decode(data.substr(0,1)),
                          voltageDecoder.decode(data.substr(2,3)));
}

std::pair<float, float> Elm327DataDecoder::GetOxygenSensorEqV4(const std::string &data)
{
    DecodeEquivalenceRatio eqRatioDecoder;
    DecodeOxygenSensorVoltage2 voltageDecoder;
    return std::make_pair(eqRatioDecoder.decode(data.substr(0,1)),
                          voltageDecoder.decode(data.substr(2,3)));
}

std::pair<float, float> Elm327DataDecoder::GetOxygenSensorEqV5(const std::string &data)
{
    DecodeEquivalenceRatio eqRatioDecoder;
    DecodeOxygenSensorVoltage2 voltageDecoder;
    return std::make_pair(eqRatioDecoder.decode(data.substr(0,1)),
                          voltageDecoder.decode(data.substr(2,3)));
}

std::pair<float, float> Elm327DataDecoder::GetOxygenSensorEqV6(const std::string &data)
{
    DecodeEquivalenceRatio eqRatioDecoder;
    DecodeOxygenSensorVoltage2 voltageDecoder;
    return std::make_pair(eqRatioDecoder.decode(data.substr(0,1)),
                          voltageDecoder.decode(data.substr(2,3)));
}

std::pair<float, float> Elm327DataDecoder::GetOxygenSensorEqV7(const std::string &data)
{
    DecodeEquivalenceRatio eqRatioDecoder;
    DecodeOxygenSensorVoltage2 voltageDecoder;
    return std::make_pair(eqRatioDecoder.decode(data.substr(0,1)),
                          voltageDecoder.decode(data.substr(2,3)));
}

std::pair<float, float> Elm327DataDecoder::GetOxygenSensorEqV8(const std::string &data)
{
    DecodeEquivalenceRatio eqRatioDecoder;
    DecodeOxygenSensorVoltage2 voltageDecoder;
    return std::make_pair(eqRatioDecoder.decode(data.substr(0,1)),
                          voltageDecoder.decode(data.substr(2,3)));
}

float Elm327DataDecoder::GetCommandedEgr(const std::string &data)
{
    DecodePercentage decoder;
    return decoder.decode(data);
}

float Elm327DataDecoder::GetEgrError(const std::string &data)
{
    DecodeSignedPercentage decoder;
    return decoder.decode(data);
}

float Elm327DataDecoder::GetCommandedEvaporativePurge(const std::string &data)
{
    DecodePercentage decoder;
    return decoder.decode(data);
}

float Elm327DataDecoder::GetFuelTankLevelInput(const std::string &data)
{
    DecodePercentage decoder;
    return decoder.decode(data);
}

float Elm327DataDecoder::GetWarmupsSinceDtcCleared(const std::string &data)
{
    DecodeSimpleA decoder;
    return decoder.decode(data);
}

float Elm327DataDecoder::GetDistanceSinceDtcCleared(const std::string &data)
{
    DecodeCountAB decoder;
    return decoder.decode(data);
}

float Elm327DataDecoder::GetEvapVaporPressure(const std::string &data)
{
    DecodeEvapPressure decoder;
    return decoder.decode(data);
}

float Elm327DataDecoder::GetAbsoluteBarometricPressure(const std::string &data)
{
    DecodeSimpleA decoder;
    return decoder.decode(data);
}

std::pair<float, float >
Elm327DataDecoder::GetOxygenSensorEqC1(const std::string &data)
{
    DecodeEquivalenceRatio eqDecoder;
    DecodeOxygenSensorCurrent currentDecoder;
    return std::make_pair(eqDecoder.decode(data.substr(0,1)),
                          currentDecoder.decode(data.substr(2,3)));
}

std::pair<float, float >
Elm327DataDecoder::GetOxygenSensorEqC2(const std::string &data)
{
    DecodeEquivalenceRatio eqDecoder;
    DecodeOxygenSensorCurrent currentDecoder;
    return std::make_pair(eqDecoder.decode(data.substr(0,1)),
                          currentDecoder.decode(data.substr(2,3)));
}

std::pair<float, float >
Elm327DataDecoder::GetOxygenSensorEqC3(const std::string &data)
{
    DecodeEquivalenceRatio eqDecoder;
    DecodeOxygenSensorCurrent currentDecoder;
    return std::make_pair(eqDecoder.decode(data.substr(0,1)),
                          currentDecoder.decode(data.substr(2,3)));
}

std::pair<float, float >
Elm327DataDecoder::GetOxygenSensorEqC4(const std::string &data)
{
    DecodeEquivalenceRatio eqDecoder;
    DecodeOxygenSensorCurrent currentDecoder;
    return std::make_pair(eqDecoder.decode(data.substr(0,1)),
                          currentDecoder.decode(data.substr(2,3)));
}

std::pair<float, float >
Elm327DataDecoder::GetOxygenSensorEqC5(const std::string &data)
{
    DecodeEquivalenceRatio eqDecoder;
    DecodeOxygenSensorCurrent currentDecoder;
    return std::make_pair(eqDecoder.decode(data.substr(0,1)),
                          currentDecoder.decode(data.substr(2,3)));
}

std::pair<float, float >
Elm327DataDecoder::GetOxygenSensorEqC6(const std::string &data)
{
    DecodeEquivalenceRatio eqDecoder;
    DecodeOxygenSensorCurrent currentDecoder;
    return std::make_pair(eqDecoder.decode(data.substr(0,1)),
                          currentDecoder.decode(data.substr(2,3)));
}

std::pair<float, float >
Elm327DataDecoder::GetOxygenSensorEqC7(const std::string &data)
{
    DecodeEquivalenceRatio eqDecoder;
    DecodeOxygenSensorCurrent currentDecoder;
    return std::make_pair(eqDecoder.decode(data.substr(0,1)),
                          currentDecoder.decode(data.substr(2,3)));
}

std::pair<float, float >
Elm327DataDecoder::GetOxygenSensorEqC8(const std::string &data)
{
    DecodeEquivalenceRatio eqDecoder;
    DecodeOxygenSensorCurrent currentDecoder;
    return std::make_pair(eqDecoder.decode(data.substr(0,1)),
                          currentDecoder.decode(data.substr(2,3)));
}

float Elm327DataDecoder::GetCatalystTemperatureB1S1(const std::string &data)
{
    DecodeCatalystTemperature decoder;
    return decoder.decode(data);
}

float Elm327DataDecoder::GetCatalystTemperatureB2S1(const std::string &data)
{
    DecodeCatalystTemperature decoder;
    return decoder.decode(data);
}

float Elm327DataDecoder::GetCatalystTemperatureB1S2(const std::string &data)
{
    DecodeCatalystTemperature decoder;
    return decoder.decode(data);
}

float Elm327DataDecoder::GetCatalystTemperatureB2S2(const std::string &data)
{
    DecodeCatalystTemperature decoder;
    return decoder.decode(data);
}

std::bitset<32> Elm327DataDecoder::GetSupportedVIPIDs(const std::string &data)
{
    DecodeBitEncoded decoder;
    return decoder.decode(data);
}

float Elm327DataDecoder::GetVinMessageCount(const std::string &data)
{
    DecodeSimpleA decoder;
    return decoder.decode(data);
}

std::string Elm327DataDecoder::GetVin(const std::string &data)
{
    DecodeString decoder;
    return decoder.decode(data);
}

float Elm327DataDecoder::GetCalibrationIdMessageCount(const std::string &data)
{
    DecodeSimpleA decoder;
    return decoder.decode(data);
}

std::string Elm327DataDecoder::GetCalibrationId(const std::string &data)
{
    DecodeString decoder;
    return decoder.decode(data);
}

float Elm327DataDecoder::GetCalibrationVerificationNumbersMessageCount(const std::string &data)
{
    DecodeSimpleA decoder;
    return decoder.decode(data);
}

std::string Elm327DataDecoder::GetCalibrationVerificationNumbers(const std::string &data)
{
    DecodeString decoder;
    return decoder.decode(data);
}

float Elm327DataDecoder::GetPerformanceTrackingMessageCount(const std::string &data)
{
    DecodeSimpleA decoder;
    return decoder.decode(data);
}

std::string Elm327DataDecoder::GetPerformanceTracking1(const std::string &data)
{
    //TODO
    //Check if response string contains actual data
    return data;
}

float Elm327DataDecoder::GetEcuNameMessageCount(const std::string &data)
{
    DecodeSimpleA decoder;
    return decoder.decode(data);
}

std::string Elm327DataDecoder::GetEcuName(const std::string &data)
{
    DecodeString decoder;
    return decoder.decode(data);
}

std::string Elm327DataDecoder::GetPerformanceTracking2(const std::string &data)
{
    //TODO
    //Check if response string contains actual data
    return data;
}
