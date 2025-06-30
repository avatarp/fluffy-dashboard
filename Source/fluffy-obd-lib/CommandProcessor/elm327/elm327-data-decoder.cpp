#include "elm327-data-decoder.hpp"
#include "elm327-decoders.hpp"

std::unordered_map<ObdCommandPid, Elm327DataDecoder::decoderFunction> Elm327DataDecoder::getDecodingMap()
{
    using enum ObdCommandPid;

    std::unordered_map<ObdCommandPid, decoderFunction> decodingMap = {
        { S01P00, { &Elm327DataDecoder::GetSupportedPIDs1, DataType::bitset } },
        { S01P01, { &Elm327DataDecoder::GetMonitorStatus, DataType::bitset } },
        { S01P02, { &Elm327DataDecoder::GetFreezeDTCs, DataType::string } },
        { S01P03, { &Elm327DataDecoder::GetFuelSystemStatus, DataType::bitset } },
        { S01P04, { &Elm327DataDecoder::GetEngineLoad, DataType::number } },
        { S01P05, { &Elm327DataDecoder::GetEngineCoolantTemperature, DataType::number } },
        { S01P06, { &Elm327DataDecoder::GetShortTermFuelTrimBank1, DataType::number } },
        { S01P07, { &Elm327DataDecoder::GetLongTermFuelTrimBank1, DataType::number } },
        { S01P08, { &Elm327DataDecoder::GetShortTermFuelTrimBank2, DataType::number } },
        { S01P09, { &Elm327DataDecoder::GetLongTermFuelTrimBank2, DataType::number } },
        { S01P0A, { &Elm327DataDecoder::GetFuelPressure, DataType::number } },
        { S01P0B, { &Elm327DataDecoder::GetIntakeManifoldPressure, DataType::number } },
        { S01P0C, { &Elm327DataDecoder::GetEngineRpm, DataType::number } },
        { S01P0D, { &Elm327DataDecoder::GetSpeed, DataType::number } },
        { S01P0E, { &Elm327DataDecoder::GetTimingAdvance, DataType::number } },
        { S01P0F, { &Elm327DataDecoder::GetIntakeAirTemperature, DataType::number } },

        { S01P10, { &Elm327DataDecoder::GetMafAirFlowRate, DataType::number } },
        { S01P11, { &Elm327DataDecoder::GetThrottlePosition, DataType::number } },
        { S01P12, { &Elm327DataDecoder::GetSecondaryAirStatus, DataType::bitset } },
        { S01P13, { &Elm327DataDecoder::GetOxygenSensorsPresent1, DataType::bitset } },
        { S01P14, { &Elm327DataDecoder::GetOxygenSensorFtV1, DataType::numberPair } },
        { S01P15, { &Elm327DataDecoder::GetOxygenSensorFtV2, DataType::numberPair } },
        { S01P16, { &Elm327DataDecoder::GetOxygenSensorFtV3, DataType::numberPair } },
        { S01P17, { &Elm327DataDecoder::GetOxygenSensorFtV4, DataType::numberPair } },
        { S01P18, { &Elm327DataDecoder::GetOxygenSensorFtV5, DataType::numberPair } },
        { S01P19, { &Elm327DataDecoder::GetOxygenSensorFtV6, DataType::numberPair } },
        { S01P1A, { &Elm327DataDecoder::GetOxygenSensorFtV7, DataType::numberPair } },
        { S01P1B, { &Elm327DataDecoder::GetOxygenSensorFtV8, DataType::numberPair } },
        { S01P1C, { &Elm327DataDecoder::GetObdStandard, DataType::bitset } },
        { S01P1D, { &Elm327DataDecoder::GetOxygenSensorsPresent2, DataType::bitset } },
        { S01P1E, { &Elm327DataDecoder::GetAuxiliaryInputStatus, DataType::bitset } },
        { S01P1F, { &Elm327DataDecoder::GetRunTime, DataType::number } },

        { S01P20, { &Elm327DataDecoder::GetSupportedPIDs2, DataType::bitset } },
        { S01P21, { &Elm327DataDecoder::GetDistanceWithMilOn, DataType::number } },
        { S01P22, { &Elm327DataDecoder::GetFuelRailPressure, DataType::number } },
        { S01P23, { &Elm327DataDecoder::GetFuelRailGaugePressure, DataType::number } },
        { S01P24, { &Elm327DataDecoder::GetOxygenSensorEqV1, DataType::numberPair } },
        { S01P25, { &Elm327DataDecoder::GetOxygenSensorEqV2, DataType::numberPair } },
        { S01P26, { &Elm327DataDecoder::GetOxygenSensorEqV3, DataType::numberPair } },
        { S01P27, { &Elm327DataDecoder::GetOxygenSensorEqV4, DataType::numberPair } },
        { S01P28, { &Elm327DataDecoder::GetOxygenSensorEqV5, DataType::numberPair } },
        { S01P29, { &Elm327DataDecoder::GetOxygenSensorEqV6, DataType::numberPair } },
        { S01P2A, { &Elm327DataDecoder::GetOxygenSensorEqV7, DataType::numberPair } },
        { S01P2B, { &Elm327DataDecoder::GetOxygenSensorEqV8, DataType::numberPair } },
        { S01P2C, { &Elm327DataDecoder::GetCommandedEgr, DataType::number } },
        { S01P2D, { &Elm327DataDecoder::GetEgrError, DataType::number } },
        { S01P2E, { &Elm327DataDecoder::GetCommandedEvaporativePurge, DataType::number } },
        { S01P2F, { &Elm327DataDecoder::GetFuelTankLevelInput, DataType::number } },

        { S01P30, { &Elm327DataDecoder::GetWarmupsSinceDtcCleared, DataType::number } },
        { S01P31, { &Elm327DataDecoder::GetDistanceSinceDtcCleared, DataType::number } },
        { S01P32, { &Elm327DataDecoder::GetEvapVaporPressure, DataType::number } },
        { S01P33, { &Elm327DataDecoder::GetAbsoluteBarometricPressure, DataType::number } },
        { S01P34, { &Elm327DataDecoder::GetOxygenSensorEqC1, DataType::numberPair } },
        { S01P35, { &Elm327DataDecoder::GetOxygenSensorEqC2, DataType::numberPair } },
        { S01P36, { &Elm327DataDecoder::GetOxygenSensorEqC3, DataType::numberPair } },
        { S01P37, { &Elm327DataDecoder::GetOxygenSensorEqC4, DataType::numberPair } },
        { S01P38, { &Elm327DataDecoder::GetOxygenSensorEqC5, DataType::numberPair } },
        { S01P39, { &Elm327DataDecoder::GetOxygenSensorEqC6, DataType::numberPair } },
        { S01P3A, { &Elm327DataDecoder::GetOxygenSensorEqC7, DataType::numberPair } },
        { S01P3B, { &Elm327DataDecoder::GetOxygenSensorEqC8, DataType::numberPair } },
        { S01P3C, { &Elm327DataDecoder::GetCatalystTemperatureB1S1, DataType::number } },
        { S01P3D, { &Elm327DataDecoder::GetCatalystTemperatureB2S1, DataType::number } },
        { S01P3E, { &Elm327DataDecoder::GetCatalystTemperatureB1S2, DataType::number } },
        { S01P3F, { &Elm327DataDecoder::GetCatalystTemperatureB2S2, DataType::number } },

        { S09P00, { &Elm327DataDecoder::GetSupportedVIPIDs, DataType::string } },
        { S09P02, { &Elm327DataDecoder::GetVin, DataType::string } }
    };
    return decodingMap;
}

void Elm327DataDecoder::decodeResponse(Response& response)
{
    static std::unordered_map<ObdCommandPid, decoderFunction> decodingMap;

    if (decodingMap.empty()) {
        decodingMap = getDecodingMap();
    }

    auto decodingFunction = decodingMap.find(response.commandPid);

    if (decodingFunction == decodingMap.end()) {
        response.state = ResponseState::invalid;
        return;
    }

    response.dataType = decodingFunction->second.dataType;
    response.decodedData = (this->*decodingFunction->second.function)(response.raw.data);
    response.state = ResponseState::decoded;
}

DecodedData Elm327DataDecoder::GetSupportedPIDs1(const std::string& data)
{
    return Bitset_32 { elm327::decoders::DecodeBitEncoded(data) };
}

DecodedData Elm327DataDecoder::GetMonitorStatus(const std::string& data)
{
    return Bitset_32 { elm327::decoders::DecodeBitEncoded(data) };
}

DecodedData Elm327DataDecoder::GetFreezeDTCs(const std::string& data)
{
    return StringData { elm327::decoders::DecodeString(data), "FreezeDTCs" };
}

DecodedData Elm327DataDecoder::GetFuelSystemStatus(const std::string& data)
{
    return Bitset_32 { elm327::decoders::DecodeBitEncoded(data) };
}

DecodedData Elm327DataDecoder::GetEngineLoad(const std::string& data)
{
    return FloatData { elm327::decoders::DecodePercentage(data), "%" };
}

DecodedData Elm327DataDecoder::GetEngineCoolantTemperature(const std::string& data)
{
    return FloatData { elm327::decoders::DecodeTemperature(data), "°C" };
}

DecodedData Elm327DataDecoder::GetShortTermFuelTrimBank1(const std::string& data)
{
    return FloatData { elm327::decoders::DecodeSignedPercentage(data), "%" };
}

DecodedData Elm327DataDecoder::GetLongTermFuelTrimBank1(const std::string& data)
{
    return FloatData { elm327::decoders::DecodeSignedPercentage(data), "%" };
}

DecodedData Elm327DataDecoder::GetShortTermFuelTrimBank2(const std::string& data)
{
    return FloatData { elm327::decoders::DecodeSignedPercentage(data), "%" };
}

DecodedData Elm327DataDecoder::GetLongTermFuelTrimBank2(const std::string& data)
{
    return FloatData { elm327::decoders::DecodeSignedPercentage(data), "%" };
}

DecodedData Elm327DataDecoder::GetFuelPressure(const std::string& data)
{
    return FloatData { elm327::decoders::DecodeFuelPressure(data), "kPa" };
}

DecodedData Elm327DataDecoder::GetIntakeManifoldPressure(const std::string& data)
{
    return FloatData { elm327::decoders::DecodeCountA(data), "kPa" };
}

DecodedData Elm327DataDecoder::GetEngineRpm(const std::string& data)
{
    return FloatData { elm327::decoders::DecodeRPM(data), "rpm" };
}

DecodedData Elm327DataDecoder::GetSpeed(const std::string& data)
{
    return FloatData { elm327::decoders::DecodeCountA(data), "km/h" };
}

DecodedData Elm327DataDecoder::GetTimingAdvance(const std::string& data)
{
    return FloatData { elm327::decoders::DecodeTimingAdvance(data), "° before TDC" };
}

DecodedData Elm327DataDecoder::GetIntakeAirTemperature(const std::string& data)
{
    return FloatData { elm327::decoders::DecodeTemperature(data), "°C" };
}

DecodedData Elm327DataDecoder::GetMafAirFlowRate(const std::string& data)
{
    return FloatData { elm327::decoders::DecodeAirFlow(data), "g/s" };
}

DecodedData Elm327DataDecoder::GetThrottlePosition(const std::string& data)
{
    return FloatData { elm327::decoders::DecodePercentage(data), "%" };
}

DecodedData Elm327DataDecoder::GetSecondaryAirStatus(const std::string& data)
{
    return Bitset_32 { elm327::decoders::DecodeBitEncoded(data) };
}

DecodedData Elm327DataDecoder::GetOxygenSensorsPresent1(const std::string& data)
{
    return Bitset_32 { elm327::decoders::DecodeBitEncoded(data) };
}

DecodedData Elm327DataDecoder::GetOxygenSensorFtV1(const std::string& data)
{
    return FloatDataPair { std::make_pair(
        std::make_pair(elm327::decoders::DecodeOxygenSensorVoltage1(data.substr(0, 2)), "V"),
        std::make_pair(elm327::decoders::DecodeSignedPercentage(data.substr(2, 2)), "%")) };
}

DecodedData Elm327DataDecoder::GetOxygenSensorFtV2(const std::string& data)
{
    return FloatDataPair { std::make_pair(
        std::make_pair(elm327::decoders::DecodeOxygenSensorVoltage1(data.substr(0, 2)), "V"),
        std::make_pair(elm327::decoders::DecodeSignedPercentage(data.substr(2, 2)), "%")) };
}

DecodedData Elm327DataDecoder::GetOxygenSensorFtV3(const std::string& data)
{
    return FloatDataPair { std::make_pair(
        std::make_pair(elm327::decoders::DecodeOxygenSensorVoltage1(data.substr(0, 2)), "V"),
        std::make_pair(elm327::decoders::DecodeSignedPercentage(data.substr(2, 2)), "%")) };
}

DecodedData Elm327DataDecoder::GetOxygenSensorFtV4(const std::string& data)
{
    return FloatDataPair { std::make_pair(
        std::make_pair(elm327::decoders::DecodeOxygenSensorVoltage1(data.substr(0, 2)), "V"),
        std::make_pair(elm327::decoders::DecodeSignedPercentage(data.substr(2, 2)), "%")) };
}

DecodedData Elm327DataDecoder::GetOxygenSensorFtV5(const std::string& data)
{
    return FloatDataPair { std::make_pair(
        std::make_pair(elm327::decoders::DecodeOxygenSensorVoltage1(data.substr(0, 2)), "V"),
        std::make_pair(elm327::decoders::DecodeSignedPercentage(data.substr(2, 2)), "%")) };
}

DecodedData Elm327DataDecoder::GetOxygenSensorFtV6(const std::string& data)
{
    return FloatDataPair { std::make_pair(
        std::make_pair(elm327::decoders::DecodeOxygenSensorVoltage1(data.substr(0, 2)), "V"),
        std::make_pair(elm327::decoders::DecodeSignedPercentage(data.substr(2, 2)), "%")) };
}

DecodedData Elm327DataDecoder::GetOxygenSensorFtV7(const std::string& data)
{
    return FloatDataPair { std::make_pair(
        std::make_pair(elm327::decoders::DecodeOxygenSensorVoltage1(data.substr(0, 2)), "V"),
        std::make_pair(elm327::decoders::DecodeSignedPercentage(data.substr(2, 2)), "%")) };
}

DecodedData Elm327DataDecoder::GetOxygenSensorFtV8(const std::string& data)
{
    return FloatDataPair { std::make_pair(
        std::make_pair(elm327::decoders::DecodeOxygenSensorVoltage1(data.substr(0, 2)), "V"),
        std::make_pair(elm327::decoders::DecodeSignedPercentage(data.substr(2, 2)), "%")) };
}

DecodedData Elm327DataDecoder::GetObdStandard(const std::string& data)
{
    return Bitset_32 { elm327::decoders::DecodeBitEncoded(data) };
}

DecodedData Elm327DataDecoder::GetOxygenSensorsPresent2(const std::string& data)
{
    return Bitset_32 { elm327::decoders::DecodeBitEncoded(data) };
}

DecodedData Elm327DataDecoder::GetAuxiliaryInputStatus(const std::string& data)
{
    return Bitset_32 { elm327::decoders::DecodeBitEncoded(data) };
}

DecodedData Elm327DataDecoder::GetRunTime(const std::string& data)
{
    return FloatData { elm327::decoders::DecodeCountAB(data), "s" };
}

DecodedData Elm327DataDecoder::GetSupportedPIDs2(const std::string& data)
{
    return Bitset_32 { elm327::decoders::DecodeBitEncoded(data) };
}

DecodedData Elm327DataDecoder::GetDistanceWithMilOn(const std::string& data)
{
    return FloatData { elm327::decoders::DecodeCountAB(data), "km" };
}

DecodedData Elm327DataDecoder::GetFuelRailPressure(const std::string& data)
{
    return FloatData { elm327::decoders::DecodeFuelRailPressure(data), "kPa" };
}

DecodedData Elm327DataDecoder::GetFuelRailGaugePressure(const std::string& data)
{
    return FloatData { elm327::decoders::DecodeFuelRailGaugePressure(data), "kPa" };
}

DecodedData Elm327DataDecoder::GetOxygenSensorEqV1(const std::string& data)
{
    return FloatDataPair { std::make_pair(
        std::make_pair(elm327::decoders::DecodeEquivalenceRatio(data.substr(0, 4)), "ratio"),
        std::make_pair(elm327::decoders::DecodeOxygenSensorVoltage2(data.substr(4, 4)), "V")) };
}

DecodedData Elm327DataDecoder::GetOxygenSensorEqV2(const std::string& data)
{
    return FloatDataPair { std::make_pair(
        std::make_pair(elm327::decoders::DecodeEquivalenceRatio(data.substr(0, 4)), "ratio"),
        std::make_pair(elm327::decoders::DecodeOxygenSensorVoltage2(data.substr(4, 4)), "V")) };
}

DecodedData Elm327DataDecoder::GetOxygenSensorEqV3(const std::string& data)
{
    return FloatDataPair { std::make_pair(
        std::make_pair(elm327::decoders::DecodeEquivalenceRatio(data.substr(0, 4)), "ratio"),
        std::make_pair(elm327::decoders::DecodeOxygenSensorVoltage2(data.substr(4, 4)), "V")) };
}

DecodedData Elm327DataDecoder::GetOxygenSensorEqV4(const std::string& data)
{
    return FloatDataPair { std::make_pair(
        std::make_pair(elm327::decoders::DecodeEquivalenceRatio(data.substr(0, 4)), "ratio"),
        std::make_pair(elm327::decoders::DecodeOxygenSensorVoltage2(data.substr(4, 4)), "V")) };
}

DecodedData Elm327DataDecoder::GetOxygenSensorEqV5(const std::string& data)
{
    return FloatDataPair { std::make_pair(
        std::make_pair(elm327::decoders::DecodeEquivalenceRatio(data.substr(0, 4)), "ratio"),
        std::make_pair(elm327::decoders::DecodeOxygenSensorVoltage2(data.substr(4, 4)), "V")) };
}

DecodedData Elm327DataDecoder::GetOxygenSensorEqV6(const std::string& data)
{
    return FloatDataPair { std::make_pair(
        std::make_pair(elm327::decoders::DecodeEquivalenceRatio(data.substr(0, 4)), "ratio"),
        std::make_pair(elm327::decoders::DecodeOxygenSensorVoltage2(data.substr(4, 4)), "V")) };
}

DecodedData Elm327DataDecoder::GetOxygenSensorEqV7(const std::string& data)
{
    return FloatDataPair { std::make_pair(
        std::make_pair(elm327::decoders::DecodeEquivalenceRatio(data.substr(0, 4)), "ratio"),
        std::make_pair(elm327::decoders::DecodeOxygenSensorVoltage2(data.substr(4, 4)), "V")) };
}

DecodedData Elm327DataDecoder::GetOxygenSensorEqV8(const std::string& data)
{
    return FloatDataPair { std::make_pair(
        std::make_pair(elm327::decoders::DecodeEquivalenceRatio(data.substr(0, 4)), "ratio"),
        std::make_pair(elm327::decoders::DecodeOxygenSensorVoltage2(data.substr(4, 4)), "V")) };
}

DecodedData Elm327DataDecoder::GetCommandedEgr(const std::string& data)
{
    return FloatData { elm327::decoders::DecodePercentage(data), "%" };
}

DecodedData Elm327DataDecoder::GetEgrError(const std::string& data)
{
    return FloatData { elm327::decoders::DecodeSignedPercentage(data), "%" };
}

DecodedData Elm327DataDecoder::GetCommandedEvaporativePurge(const std::string& data)
{
    return FloatData { elm327::decoders::DecodePercentage(data), "%" };
}

DecodedData Elm327DataDecoder::GetFuelTankLevelInput(const std::string& data)
{
    return FloatData { elm327::decoders::DecodePercentage(data), "%" };
}

DecodedData Elm327DataDecoder::GetWarmupsSinceDtcCleared(const std::string& data)
{
    return FloatData { elm327::decoders::DecodeCountA(data), "count" };
}

DecodedData Elm327DataDecoder::GetDistanceSinceDtcCleared(const std::string& data)
{
    return FloatData { elm327::decoders::DecodeCountAB(data), "km" };
}

DecodedData Elm327DataDecoder::GetEvapVaporPressure(const std::string& data)
{
    return FloatData { elm327::decoders::DecodeEvapPressure(data), "Pa" };
}

DecodedData Elm327DataDecoder::GetAbsoluteBarometricPressure(const std::string& data)
{
    return FloatData { elm327::decoders::DecodeCountA(data), "kPa" };
}

DecodedData Elm327DataDecoder::GetOxygenSensorEqC1(const std::string& data)
{
    return FloatDataPair { std::make_pair(
        std::make_pair(elm327::decoders::DecodeEquivalenceRatio(data.substr(0, 4)), "ratio"),
        std::make_pair(elm327::decoders::DecodeOxygenSensorCurrent(data.substr(4, 4)), "mA")) };
}

DecodedData Elm327DataDecoder::GetOxygenSensorEqC2(const std::string& data)
{
    return FloatDataPair { std::make_pair(
        std::make_pair(elm327::decoders::DecodeEquivalenceRatio(data.substr(0, 4)), "ratio"),
        std::make_pair(elm327::decoders::DecodeOxygenSensorCurrent(data.substr(4, 4)), "mA")) };
}

DecodedData Elm327DataDecoder::GetOxygenSensorEqC3(const std::string& data)
{
    return FloatDataPair { std::make_pair(
        std::make_pair(elm327::decoders::DecodeEquivalenceRatio(data.substr(0, 4)), "ratio"),
        std::make_pair(elm327::decoders::DecodeOxygenSensorCurrent(data.substr(4, 4)), "mA")) };
}

DecodedData Elm327DataDecoder::GetOxygenSensorEqC4(const std::string& data)
{
    return FloatDataPair { std::make_pair(
        std::make_pair(elm327::decoders::DecodeEquivalenceRatio(data.substr(0, 4)), "ratio"),
        std::make_pair(elm327::decoders::DecodeOxygenSensorCurrent(data.substr(4, 4)), "mA")) };
}

DecodedData Elm327DataDecoder::GetOxygenSensorEqC5(const std::string& data)
{
    return FloatDataPair { std::make_pair(
        std::make_pair(elm327::decoders::DecodeEquivalenceRatio(data.substr(0, 4)), "ratio"),
        std::make_pair(elm327::decoders::DecodeOxygenSensorCurrent(data.substr(4, 4)), "mA")) };
}

DecodedData Elm327DataDecoder::GetOxygenSensorEqC6(const std::string& data)
{
    return FloatDataPair { std::make_pair(
        std::make_pair(elm327::decoders::DecodeEquivalenceRatio(data.substr(0, 4)), "ratio"),
        std::make_pair(elm327::decoders::DecodeOxygenSensorCurrent(data.substr(4, 4)), "mA")) };
}

DecodedData Elm327DataDecoder::GetOxygenSensorEqC7(const std::string& data)
{
    return FloatDataPair { std::make_pair(
        std::make_pair(elm327::decoders::DecodeEquivalenceRatio(data.substr(0, 4)), "ratio"),
        std::make_pair(elm327::decoders::DecodeOxygenSensorCurrent(data.substr(4, 4)), "mA")) };
}

DecodedData Elm327DataDecoder::GetOxygenSensorEqC8(const std::string& data)
{
    return FloatDataPair { std::make_pair(
        std::make_pair(elm327::decoders::DecodeEquivalenceRatio(data.substr(0, 4)), "ratio"),
        std::make_pair(elm327::decoders::DecodeOxygenSensorCurrent(data.substr(4, 4)), "mA")) };
}

DecodedData Elm327DataDecoder::GetCatalystTemperatureB1S1(const std::string& data)
{
    return FloatData { elm327::decoders::DecodeCatalystTemperature(data), "°C" };
}

DecodedData Elm327DataDecoder::GetCatalystTemperatureB2S1(const std::string& data)
{
    return FloatData { elm327::decoders::DecodeCatalystTemperature(data), "°C" };
}

DecodedData Elm327DataDecoder::GetCatalystTemperatureB1S2(const std::string& data)
{
    return FloatData { elm327::decoders::DecodeCatalystTemperature(data), "°C" };
}

DecodedData Elm327DataDecoder::GetCatalystTemperatureB2S2(const std::string& data)
{
    return FloatData { elm327::decoders::DecodeCatalystTemperature(data), "°C" };
}

DecodedData Elm327DataDecoder::GetSupportedVIPIDs(const std::string& data)
{
    return Bitset_32 { elm327::decoders::DecodeBitEncoded(data) };
}

DecodedData Elm327DataDecoder::GetVinMessageCount(const std::string& data)
{
    return elm327::decoders::DecodeCountA(data);
}

DecodedData Elm327DataDecoder::GetVin(const std::string& data)
{
    constexpr size_t dataItemCountLength { 2 };
    return StringData { elm327::decoders::DecodeString(data.substr(dataItemCountLength, data.length() - dataItemCountLength)), "VIN" };
}

DecodedData Elm327DataDecoder::GetCalibrationIdMessageCount(const std::string& data)
{
    return FloatData { elm327::decoders::DecodeCountA(data), "Calibration ID message count" };
}

DecodedData Elm327DataDecoder::GetCalibrationId(const std::string& data)
{
    return StringData { elm327::decoders::DecodeString(data), "Calibration ID" };
}

DecodedData Elm327DataDecoder::GetCalibrationVerificationNumbersMessageCount(const std::string& data)
{
    return FloatData { elm327::decoders::DecodeCountA(data), "Calibration verification numbers message count" };
}

DecodedData Elm327DataDecoder::GetCalibrationVerificationNumbers(const std::string& data)
{
    return StringData { elm327::decoders::DecodeString(data), "Calibration verification numbers" };
}

DecodedData Elm327DataDecoder::GetPerformanceTrackingMessageCount(const std::string& data)
{
    return FloatData { elm327::decoders::DecodeCountA(data), "Performance tracking message count" };
}

DecodedData Elm327DataDecoder::GetPerformanceTracking1(const std::string& data)
{
    // TODO #16
    // Check if response string contains actual data
    return StringData { elm327::decoders::DecodeString(data), "Performance tracking 1" };
}

DecodedData Elm327DataDecoder::GetEcuNameMessageCount(const std::string& data)
{
    return FloatData { elm327::decoders::DecodeCountA(data), " Ecu name message count" };
}

DecodedData Elm327DataDecoder::GetEcuName(const std::string& data)
{
    return StringData { elm327::decoders::DecodeString(data), "ECU Name" };
}

DecodedData Elm327DataDecoder::GetPerformanceTracking2(const std::string& data)
{
    // TODO #16
    // Check if response string contains actual data
    return StringData { elm327::decoders::DecodeString(data), "Performance tracking 2" };
}
