#include "elm327-data-decoder.hpp"
#include "elm327-decoders.hpp"

void Elm327DataDecoder::decodeResponse(Response &response)
{
    using enum ObdCommandPid;

    switch (response.commandPid) {
    case S01P00:
        response.m_dataType = DataType::bitset;
        response.m_dataBitset = this->GetSupportedPIDs1(response.m_rawData);
        return;
    case S01P01:
        response.m_dataType = DataType::bitset;
        response.m_dataBitset = this->GetMonitorStatus(response.m_rawData);
        return;
    case S01P02:
        response.m_dataType = DataType::string;
        response.m_dataString = std::pair<std::string, std::string>(
            this->GetFreezeDTCs(response.m_rawData), "FreezeDTCs");
        return;
    case S01P03:
        response.m_dataType = DataType::bitset;
        response.m_dataBitset = this->GetFuelSystemStatus(response.m_rawData);
        return;
    case S01P04:
        response.m_dataType = DataType::number;
        response.m_dataFloat1 = { this->GetEngineLoad(response.m_rawData), "%" };
        return;
    case S01P05:
        response.m_dataType = DataType::number;
        response.m_dataFloat1 = { this->GetEngineCoolantTemperature(response.m_rawData), "°C" };
        return;
    case S01P06:
        response.m_dataType = DataType::number;
        response.m_dataFloat1 = { this->GetShortTermFuelTrimBank1(response.m_rawData), "%" };
        return;
    case S01P07:
        response.m_dataType = DataType::number;
        response.m_dataFloat1 = { this->GetLongTermFuelTrimBank1(response.m_rawData), "%" };
        return;
    case S01P08:
        response.m_dataType = DataType::number;
        response.m_dataFloat1 = { this->GetShortTermFuelTrimBank2(response.m_rawData), "%" };
        return;
    case S01P09:
        response.m_dataType = DataType::number;
        response.m_dataFloat1 = { this->GetLongTermFuelTrimBank2(response.m_rawData), "%" };
        return;
    case S01P0A:
        response.m_dataType = DataType::number;
        response.m_dataFloat1 = { this->GetFuelPressure(response.m_rawData), "kPa" };
        return;
    case S01P0B:
        response.m_dataType = DataType::number;
        response.m_dataFloat1 = { this->GetIntakeManifoldPressure(response.m_rawData), "kPa" };
        return;
    case S01P0C:
        response.m_dataType = DataType::number;
        response.m_dataFloat1 = { this->GetEngineRpm(response.m_rawData), "rpm" };
        return;
    case S01P0D:
        response.m_dataType = DataType::number;
        response.m_dataFloat1 = { this->GetSpeed(response.m_rawData), "km/h" };
        return;
    case S01P0E:
        response.m_dataType = DataType::number;
        response.m_dataFloat1 = { this->GetTimingAdvance(response.m_rawData), "° before TDC" };
        return;
    case S01P0F:
        response.m_dataType = DataType::number;
        response.m_dataFloat1 = { this->GetIntakeAirTemperature(response.m_rawData), "°C" };
        return;
    case S01P10:
        response.m_dataType = DataType::number;
        response.m_dataFloat1 = { this->GetMafAirFlowRate(response.m_rawData), "g/s" };
        return;
    case S01P11:
        response.m_dataType = DataType::number;
        response.m_dataFloat1 = { this->GetThrottlePosition(response.m_rawData), "%" };
        return;
    case S01P12:
        response.m_dataType = DataType::bitset;
        response.m_dataBitset = this->GetSecondaryAirStatus(response.m_rawData);
        return;
    case S01P13:
        response.m_dataType = DataType::bitset;
        response.m_dataBitset = this->GetOxygenSensorsPresent1(response.m_rawData);
        return;
    case S01P14: {
        response.m_dataType = DataType::numberPair;
        auto decodedPair = this->GetOxygenSensorFtV1(response.m_rawData);
        response.m_dataFloat1 = { decodedPair.first, "V" };
        response.m_dataFloat2 = { decodedPair.second, "%" };
        return;
    }
    case S01P15: {
        response.m_dataType = DataType::numberPair;
        auto decodedPair = this->GetOxygenSensorFtV2(response.m_rawData);
        response.m_dataFloat1 = { decodedPair.first, "V" };
        response.m_dataFloat2 = { decodedPair.second, "%" };
        return;
    }
    case S01P16: {
        response.m_dataType = DataType::numberPair;
        auto decodedPair = this->GetOxygenSensorFtV3(response.m_rawData);
        response.m_dataFloat1 = { decodedPair.first, "V" };
        response.m_dataFloat2 = { decodedPair.second, "%" };
        return;
    }
    case S01P17: {
        response.m_dataType = DataType::numberPair;
        auto decodedPair = this->GetOxygenSensorFtV4(response.m_rawData);
        response.m_dataFloat1 = { decodedPair.first, "V" };
        response.m_dataFloat2 = { decodedPair.second, "%" };
        return;
    }
    case S01P18: {
        response.m_dataType = DataType::numberPair;
        auto decodedPair = this->GetOxygenSensorFtV5(response.m_rawData);
        response.m_dataFloat1 = { decodedPair.first, "V" };
        response.m_dataFloat2 = { decodedPair.second, "%" };
        return;
    }
    case S01P19: {
        response.m_dataType = DataType::numberPair;
        auto decodedPair = this->GetOxygenSensorFtV6(response.m_rawData);
        response.m_dataFloat1 = { decodedPair.first, "V" };
        response.m_dataFloat2 = { decodedPair.second, "%" };
        return;
    }
    case S01P1A: {
        response.m_dataType = DataType::numberPair;
        auto decodedPair = this->GetOxygenSensorFtV7(response.m_rawData);
        response.m_dataFloat1 = { decodedPair.first, "V" };
        response.m_dataFloat2 = { decodedPair.second, "%" };
        return;
    }
    case S01P1B: {
        response.m_dataType = DataType::numberPair;
        auto decodedPair = this->GetOxygenSensorFtV8(response.m_rawData);
        response.m_dataFloat1 = { decodedPair.first, "V" };
        response.m_dataFloat2 = { decodedPair.second, "%" };
        return;
    }
    case S01P1C:
        response.m_dataType = DataType::bitset;
        response.m_dataBitset = this->GetObdStandard(response.m_rawData);
        return;
    case S01P1D:
        response.m_dataType = DataType::bitset;
        response.m_dataBitset = this->GetOxygenSensorsPresent2(response.m_rawData);
        return;
    case S01P1E:
        response.m_dataType = DataType::bitset;
        response.m_dataBitset = this->GetAuxiliaryInputStatus(response.m_rawData);
        return;
    case S01P1F:
        response.m_dataType = DataType::number;
        response.m_dataFloat1 = { this->GetRunTime(response.m_rawData), "s" };
        return;
    case S01P20:
        response.m_dataType = DataType::bitset;
        response.m_dataBitset = this->GetSupportedPIDs2(response.m_rawData);
        return;
    case S01P21:
        response.m_dataType = DataType::number;
        response.m_dataFloat1 = { this->GetDistanceWithMilOn(response.m_rawData), "km" };
        return;
    case S01P22:
        response.m_dataType = DataType::number;
        response.m_dataFloat1 = { this->GetFuelRailPressure(response.m_rawData), "kPa" };
        return;
    case S01P23:
        response.m_dataType = DataType::number;
        response.m_dataFloat1 = { this->GetFuelRailGaugePressure(response.m_rawData), "kPa" };
        return;
    case S01P24: {
        response.m_dataType = DataType::numberPair;
        auto decodedPair = this->GetOxygenSensorEqV1(response.m_rawData);
        response.m_dataFloat1 = { decodedPair.first, "ratio" };
        response.m_dataFloat2 = { decodedPair.second, "V" };
        return;
    }
    case S01P25: {
        response.m_dataType = DataType::numberPair;
        auto decodedPair = this->GetOxygenSensorEqV2(response.m_rawData);
        response.m_dataFloat1 = { decodedPair.first, "ratio" };
        response.m_dataFloat2 = { decodedPair.second, "V" };
        return;
    }
    case S01P26: {
        response.m_dataType = DataType::numberPair;
        auto decodedPair = this->GetOxygenSensorEqV3(response.m_rawData);
        response.m_dataFloat1 = { decodedPair.first, "ratio" };
        response.m_dataFloat2 = { decodedPair.second, "V" };
        return;
    }
    case S01P27: {
        response.m_dataType = DataType::numberPair;
        auto decodedPair = this->GetOxygenSensorEqV4(response.m_rawData);
        response.m_dataFloat1 = { decodedPair.first, "ratio" };
        response.m_dataFloat2 = { decodedPair.second, "V" };
        return;
    }
    case S01P28: {
        response.m_dataType = DataType::numberPair;
        auto decodedPair = this->GetOxygenSensorEqV5(response.m_rawData);
        response.m_dataFloat1 = { decodedPair.first, "ratio" };
        response.m_dataFloat2 = { decodedPair.second, "V" };
        return;
    }
    case S01P29: {
        response.m_dataType = DataType::numberPair;
        auto decodedPair = this->GetOxygenSensorEqV6(response.m_rawData);
        response.m_dataFloat1 = { decodedPair.first, "ratio" };
        response.m_dataFloat2 = { decodedPair.second, "V" };
        return;
    }
    case S01P2A: {
        response.m_dataType = DataType::numberPair;
        auto decodedPair = this->GetOxygenSensorEqV7(response.m_rawData);
        response.m_dataFloat1 = { decodedPair.first, "ratio" };
        response.m_dataFloat2 = { decodedPair.second, "V" };
        return;
    }
    case S01P2B: {
        response.m_dataType = DataType::numberPair;
        auto decodedPair = this->GetOxygenSensorEqV8(response.m_rawData);
        response.m_dataFloat1 = { decodedPair.first, "ratio" };
        response.m_dataFloat2 = { decodedPair.second, "V" };
        return;
    }
    case S01P2C:
        response.m_dataType = DataType::number;
        response.m_dataFloat1 = { this->GetCommandedEgr(response.m_rawData), "%" };
        return;
    case S01P2D:
        response.m_dataType = DataType::number;
        response.m_dataFloat1 = { this->GetEgrError(response.m_rawData), "%" };
        return;
    case S01P2E:
        response.m_dataType = DataType::number;
        response.m_dataFloat1 = { this->GetCommandedEvaporativePurge(response.m_rawData), "%" };
        return;
    case S01P2F:
        response.m_dataType = DataType::number;
        response.m_dataFloat1 = { this->GetFuelTankLevelInput(response.m_rawData), "%" };
        return;
    case S01P30:
        response.m_dataType = DataType::number;
        response.m_dataFloat1 = { this->GetWarmupsSinceDtcCleared(response.m_rawData), "count" };
        return;
    case S01P31:
        response.m_dataType = DataType::number;
        response.m_dataFloat1 = { this->GetDistanceSinceDtcCleared(response.m_rawData), "km" };
        return;
    case S01P32:
        response.m_dataType = DataType::number;
        response.m_dataFloat1 = { this->GetEvapVaporPressure(response.m_rawData), "Pa" };
        return;
    case S01P33:
        response.m_dataType = DataType::number;
        response.m_dataFloat1 = { this->GetAbsoluteBarometricPressure(response.m_rawData), "kPa" };
        return;
    case S01P34: {
        response.m_dataType = DataType::numberPair;
        auto decodedPair = this->GetOxygenSensorEqC1(response.m_rawData);
        response.m_dataFloat1 = { decodedPair.first, "ratio" };
        response.m_dataFloat2 = { decodedPair.second, "mA" };
        return;
    }
    case S01P35: {
        response.m_dataType = DataType::numberPair;
        auto decodedPair = this->GetOxygenSensorEqC2(response.m_rawData);
        response.m_dataFloat1 = { decodedPair.first, "ratio" };
        response.m_dataFloat2 = { decodedPair.second, "mA" };
        return;
    }
    case S01P36: {
        response.m_dataType = DataType::numberPair;
        auto decodedPair = this->GetOxygenSensorEqC3(response.m_rawData);
        response.m_dataFloat1 = { decodedPair.first, "ratio" };
        response.m_dataFloat2 = { decodedPair.second, "mA" };
        return;
    }
    case S01P37: {
        response.m_dataType = DataType::numberPair;
        auto decodedPair = this->GetOxygenSensorEqC4(response.m_rawData);
        response.m_dataFloat1 = { decodedPair.first, "ratio" };
        response.m_dataFloat2 = { decodedPair.second, "mA" };
        return;
    }
    case S01P38: {
        response.m_dataType = DataType::numberPair;
        auto decodedPair = this->GetOxygenSensorEqC5(response.m_rawData);
        response.m_dataFloat1 = { decodedPair.first, "ratio" };
        response.m_dataFloat2 = { decodedPair.second, "mA" };
        return;
    }
    case S01P39: {
        response.m_dataType = DataType::numberPair;
        auto decodedPair = this->GetOxygenSensorEqC6(response.m_rawData);
        response.m_dataFloat1 = { decodedPair.first, "ratio" };
        response.m_dataFloat2 = { decodedPair.second, "mA" };
        return;
    }
    case S01P3A: {
        response.m_dataType = DataType::numberPair;
        auto decodedPair = this->GetOxygenSensorEqC7(response.m_rawData);
        response.m_dataFloat1 = { decodedPair.first, "ratio" };
        response.m_dataFloat2 = { decodedPair.second, "mA" };
        return;
    }
    case S01P3B: {
        response.m_dataType = DataType::numberPair;
        auto decodedPair = this->GetOxygenSensorEqC8(response.m_rawData);
        response.m_dataFloat1 = { decodedPair.first, "ratio" };
        response.m_dataFloat2 = { decodedPair.second, "mA" };
        return;
    }
    case S01P3C: {
        response.m_dataType = DataType::numberPair;
        response.m_dataFloat1
            = { this->GetCatalystTemperatureB1S1(response.m_rawData), "°C" };
        return;
    }
    case S01P3D:
        response.m_dataType = DataType::number;
        response.m_dataFloat1
            = { this->GetCatalystTemperatureB2S1(response.m_rawData),
                  "°C" };
        return;
    case S01P3E:
        response.m_dataType = DataType::number;
        response.m_dataFloat1
            = { this->GetCatalystTemperatureB1S2(response.m_rawData),
                  "°C" };
        return;
    case S01P3F:
        response.m_dataType = DataType::number;
        response.m_dataFloat1
            = { this->GetCatalystTemperatureB2S2(response.m_rawData),
                  "°C" };
        return;

    case S09P00:
        response.m_dataType = DataType::bitset;
        response.m_dataBitset = this->GetSupportedVIPIDs(response.m_rawData);
    default:
        return;
    }
}

bitset_32 Elm327DataDecoder::GetSupportedPIDs1(const std::string& data)
{
    return elm327::decoders::DecodeBitEncoded(data);
}

bitset_32 Elm327DataDecoder::GetMonitorStatus(const std::string& data)
{
    return elm327::decoders::DecodeBitEncoded(data);
}

std::string Elm327DataDecoder::GetFreezeDTCs(const std::string& data)
{
    return elm327::decoders::DecodeString(data);
}

bitset_32 Elm327DataDecoder::GetFuelSystemStatus(const std::string& data)
{
    return elm327::decoders::DecodeBitEncoded(data);
}

float Elm327DataDecoder::GetEngineLoad(const std::string& data)
{
    return elm327::decoders::DecodePercentage(data);
}

float Elm327DataDecoder::GetEngineCoolantTemperature(const std::string& data)
{
    return elm327::decoders::DecodeTemperature(data);
}

float Elm327DataDecoder::GetShortTermFuelTrimBank1(const std::string& data)
{
    return elm327::decoders::DecodeSignedPercentage(data);
}

float Elm327DataDecoder::GetLongTermFuelTrimBank1(const std::string& data)
{
    return elm327::decoders::DecodeSignedPercentage(data);
}

float Elm327DataDecoder::GetShortTermFuelTrimBank2(const std::string& data)
{
    return elm327::decoders::DecodeSignedPercentage(data);
}

float Elm327DataDecoder::GetLongTermFuelTrimBank2(const std::string& data)
{
    return elm327::decoders::DecodeSignedPercentage(data);
}

float Elm327DataDecoder::GetFuelPressure(const std::string& data)
{
    return elm327::decoders::DecodeFuelPressure(data);
}

float Elm327DataDecoder::GetIntakeManifoldPressure(const std::string& data)
{
    return elm327::decoders::DecodeCountA(data);
}

float Elm327DataDecoder::GetEngineRpm(const std::string& data)
{
    return elm327::decoders::DecodeRPM(data);
}

float Elm327DataDecoder::GetSpeed(const std::string& data)
{
    return elm327::decoders::DecodeCountA(data);
}

float Elm327DataDecoder::GetTimingAdvance(const std::string& data)
{
    return elm327::decoders::DecodeTimingAdvance(data);
}

float Elm327DataDecoder::GetIntakeAirTemperature(const std::string& data)
{
    return elm327::decoders::DecodeTemperature(data);
}

float Elm327DataDecoder::GetMafAirFlowRate(const std::string& data)
{
    return elm327::decoders::DecodeAirFlow(data);
}

float Elm327DataDecoder::GetThrottlePosition(const std::string& data)
{
    return elm327::decoders::DecodePercentage(data);
}

bitset_32 Elm327DataDecoder::GetSecondaryAirStatus(const std::string& data)
{
    return elm327::decoders::DecodeBitEncoded(data);
}

bitset_32 Elm327DataDecoder::GetOxygenSensorsPresent1(const std::string& data)
{
    return elm327::decoders::DecodeBitEncoded(data);
}

std::pair<float, float>
Elm327DataDecoder::GetOxygenSensorFtV1(const std::string& data)
{
    return std::make_pair(elm327::decoders::DecodeOxygenSensorVoltage1(data.substr(0, 2)),
        elm327::decoders::DecodeSignedPercentage(data.substr(2, 2)));
}

std::pair<float, float>
Elm327DataDecoder::GetOxygenSensorFtV2(const std::string& data)
{
    return std::make_pair(elm327::decoders::DecodeOxygenSensorVoltage1(data.substr(0, 2)),
        elm327::decoders::DecodeSignedPercentage(data.substr(2, 2)));
}

std::pair<float, float>
Elm327DataDecoder::GetOxygenSensorFtV3(const std::string& data)
{
    return std::make_pair(elm327::decoders::DecodeOxygenSensorVoltage1(data.substr(0, 2)),
        elm327::decoders::DecodeSignedPercentage(data.substr(2, 2)));
}

std::pair<float, float>
Elm327DataDecoder::GetOxygenSensorFtV4(const std::string& data)
{
    return std::make_pair(elm327::decoders::DecodeOxygenSensorVoltage1(data.substr(0, 2)),
        elm327::decoders::DecodeSignedPercentage(data.substr(2, 2)));
}

std::pair<float, float>
Elm327DataDecoder::GetOxygenSensorFtV5(const std::string& data)
{
    return std::make_pair(elm327::decoders::DecodeOxygenSensorVoltage1(data.substr(0, 2)),
        elm327::decoders::DecodeSignedPercentage(data.substr(2, 2)));
}

std::pair<float, float>
Elm327DataDecoder::GetOxygenSensorFtV6(const std::string& data)
{
    return std::make_pair(elm327::decoders::DecodeOxygenSensorVoltage1(data.substr(0, 2)),
        elm327::decoders::DecodeSignedPercentage(data.substr(2, 2)));
}

std::pair<float, float>
Elm327DataDecoder::GetOxygenSensorFtV7(const std::string& data)
{
    return std::make_pair(elm327::decoders::DecodeOxygenSensorVoltage1(data.substr(0, 2)),
        elm327::decoders::DecodeSignedPercentage(data.substr(2, 2)));
}

std::pair<float, float>
Elm327DataDecoder::GetOxygenSensorFtV8(const std::string& data)
{
    return std::make_pair(elm327::decoders::DecodeOxygenSensorVoltage1(data.substr(0, 2)),
        elm327::decoders::DecodeSignedPercentage(data.substr(2, 2)));
}

bitset_32 Elm327DataDecoder::GetObdStandard(const std::string& data)
{
    return elm327::decoders::DecodeBitEncoded(data);
}

bitset_32 Elm327DataDecoder::GetOxygenSensorsPresent2(const std::string& data)
{
    return elm327::decoders::DecodeBitEncoded(data);
}

bitset_32 Elm327DataDecoder::GetAuxiliaryInputStatus(const std::string& data)
{
    return elm327::decoders::DecodeBitEncoded(data);
}

float Elm327DataDecoder::GetRunTime(const std::string& data)
{
    return elm327::decoders::DecodeCountAB(data);
}

bitset_32 Elm327DataDecoder::GetSupportedPIDs2(const std::string& data)
{
    return elm327::decoders::DecodeBitEncoded(data);
}

float Elm327DataDecoder::GetDistanceWithMilOn(const std::string& data)
{
    return elm327::decoders::DecodeCountAB(data);
}

float Elm327DataDecoder::GetFuelRailPressure(const std::string& data)
{
    return elm327::decoders::DecodeFuelRailPressure(data);
}

float Elm327DataDecoder::GetFuelRailGaugePressure(const std::string& data)
{
    return elm327::decoders::DecodeFuelRailGaugePressure(data);
}

std::pair<float, float> Elm327DataDecoder::GetOxygenSensorEqV1(const std::string& data)
{
    return std::make_pair(elm327::decoders::DecodeEquivalenceRatio(data.substr(0, 4)),
        elm327::decoders::DecodeOxygenSensorVoltage2(data.substr(4, 4)));
}

std::pair<float, float> Elm327DataDecoder::GetOxygenSensorEqV2(const std::string& data)
{
    return std::make_pair(elm327::decoders::DecodeEquivalenceRatio(data.substr(0, 4)),
        elm327::decoders::DecodeOxygenSensorVoltage2(data.substr(4, 4)));
}

std::pair<float, float> Elm327DataDecoder::GetOxygenSensorEqV3(const std::string& data)
{
    return std::make_pair(elm327::decoders::DecodeEquivalenceRatio(data.substr(0, 4)),
        elm327::decoders::DecodeOxygenSensorVoltage2(data.substr(4, 4)));
}

std::pair<float, float> Elm327DataDecoder::GetOxygenSensorEqV4(const std::string& data)
{
    return std::make_pair(elm327::decoders::DecodeEquivalenceRatio(data.substr(0, 4)),
        elm327::decoders::DecodeOxygenSensorVoltage2(data.substr(4, 4)));
}

std::pair<float, float> Elm327DataDecoder::GetOxygenSensorEqV5(const std::string& data)
{
    return std::make_pair(elm327::decoders::DecodeEquivalenceRatio(data.substr(0, 4)),
        elm327::decoders::DecodeOxygenSensorVoltage2(data.substr(4, 4)));
}

std::pair<float, float> Elm327DataDecoder::GetOxygenSensorEqV6(const std::string& data)
{
    return std::make_pair(elm327::decoders::DecodeEquivalenceRatio(data.substr(0, 4)),
        elm327::decoders::DecodeOxygenSensorVoltage2(data.substr(4, 4)));
}

std::pair<float, float> Elm327DataDecoder::GetOxygenSensorEqV7(const std::string& data)
{
    return std::make_pair(elm327::decoders::DecodeEquivalenceRatio(data.substr(0, 4)),
        elm327::decoders::DecodeOxygenSensorVoltage2(data.substr(4, 4)));
}

std::pair<float, float> Elm327DataDecoder::GetOxygenSensorEqV8(const std::string& data)
{
    return std::make_pair(elm327::decoders::DecodeEquivalenceRatio(data.substr(0, 4)),
        elm327::decoders::DecodeOxygenSensorVoltage2(data.substr(4, 4)));
}

float Elm327DataDecoder::GetCommandedEgr(const std::string& data)
{
    return elm327::decoders::DecodePercentage(data);
}

float Elm327DataDecoder::GetEgrError(const std::string& data)
{
    return elm327::decoders::DecodeSignedPercentage(data);
}

float Elm327DataDecoder::GetCommandedEvaporativePurge(const std::string& data)
{
    return elm327::decoders::DecodePercentage(data);
}

float Elm327DataDecoder::GetFuelTankLevelInput(const std::string& data)
{
    return elm327::decoders::DecodePercentage(data);
}

float Elm327DataDecoder::GetWarmupsSinceDtcCleared(const std::string& data)
{
    return elm327::decoders::DecodeCountA(data);
}

float Elm327DataDecoder::GetDistanceSinceDtcCleared(const std::string& data)
{
    return elm327::decoders::DecodeCountAB(data);
}

float Elm327DataDecoder::GetEvapVaporPressure(const std::string& data)
{
    return elm327::decoders::DecodeEvapPressure(data);
}

float Elm327DataDecoder::GetAbsoluteBarometricPressure(const std::string& data)
{
    return elm327::decoders::DecodeCountA(data);
}

std::pair<float, float>
Elm327DataDecoder::GetOxygenSensorEqC1(const std::string& data)
{
    return std::make_pair(elm327::decoders::DecodeEquivalenceRatio(data.substr(0, 2)),
        elm327::decoders::DecodeOxygenSensorCurrent(data.substr(2, 2)));
}

std::pair<float, float>
Elm327DataDecoder::GetOxygenSensorEqC2(const std::string& data)
{
    return std::make_pair(elm327::decoders::DecodeEquivalenceRatio(data.substr(0, 2)),
        elm327::decoders::DecodeOxygenSensorCurrent(data.substr(2, 2)));
}

std::pair<float, float>
Elm327DataDecoder::GetOxygenSensorEqC3(const std::string& data)
{
    return std::make_pair(elm327::decoders::DecodeEquivalenceRatio(data.substr(0, 2)),
        elm327::decoders::DecodeOxygenSensorCurrent(data.substr(2, 2)));
}

std::pair<float, float>
Elm327DataDecoder::GetOxygenSensorEqC4(const std::string& data)
{
    return std::make_pair(elm327::decoders::DecodeEquivalenceRatio(data.substr(0, 2)),
        elm327::decoders::DecodeOxygenSensorCurrent(data.substr(2, 2)));
}

std::pair<float, float>
Elm327DataDecoder::GetOxygenSensorEqC5(const std::string& data)
{
    return std::make_pair(elm327::decoders::DecodeEquivalenceRatio(data.substr(0, 2)),
        elm327::decoders::DecodeOxygenSensorCurrent(data.substr(2, 2)));
}

std::pair<float, float>
Elm327DataDecoder::GetOxygenSensorEqC6(const std::string& data)
{
    return std::make_pair(elm327::decoders::DecodeEquivalenceRatio(data.substr(0, 2)),
        elm327::decoders::DecodeOxygenSensorCurrent(data.substr(2, 2)));
}

std::pair<float, float>
Elm327DataDecoder::GetOxygenSensorEqC7(const std::string& data)
{
    return std::make_pair(elm327::decoders::DecodeEquivalenceRatio(data.substr(0, 2)),
        elm327::decoders::DecodeOxygenSensorCurrent(data.substr(2, 2)));
}

std::pair<float, float>
Elm327DataDecoder::GetOxygenSensorEqC8(const std::string& data)
{
    return std::make_pair(elm327::decoders::DecodeEquivalenceRatio(data.substr(0, 2)),
        elm327::decoders::DecodeOxygenSensorCurrent(data.substr(2, 2)));
}

float Elm327DataDecoder::GetCatalystTemperatureB1S1(const std::string& data)
{
    return elm327::decoders::DecodeCatalystTemperature(data);
}

float Elm327DataDecoder::GetCatalystTemperatureB2S1(const std::string& data)
{
    return elm327::decoders::DecodeCatalystTemperature(data);
}

float Elm327DataDecoder::GetCatalystTemperatureB1S2(const std::string& data)
{
    return elm327::decoders::DecodeCatalystTemperature(data);
}

float Elm327DataDecoder::GetCatalystTemperatureB2S2(const std::string& data)
{
    return elm327::decoders::DecodeCatalystTemperature(data);
}

bitset_32 Elm327DataDecoder::GetSupportedVIPIDs(const std::string& data)
{
    return elm327::decoders::DecodeBitEncoded(data);
}

float Elm327DataDecoder::GetVinMessageCount(const std::string& data)
{
    return elm327::decoders::DecodeCountA(data);
}

std::string Elm327DataDecoder::GetVin(const std::string& data)
{
    return elm327::decoders::DecodeString(data);
}

float Elm327DataDecoder::GetCalibrationIdMessageCount(const std::string& data)
{
    return elm327::decoders::DecodeCountA(data);
}

std::string Elm327DataDecoder::GetCalibrationId(const std::string& data)
{
    return elm327::decoders::DecodeString(data);
}

float Elm327DataDecoder::GetCalibrationVerificationNumbersMessageCount(const std::string& data)
{
    return elm327::decoders::DecodeCountA(data);
}

std::string Elm327DataDecoder::GetCalibrationVerificationNumbers(const std::string& data)
{
    return elm327::decoders::DecodeString(data);
}

float Elm327DataDecoder::GetPerformanceTrackingMessageCount(const std::string& data)
{
    return elm327::decoders::DecodeCountA(data);
}

std::string Elm327DataDecoder::GetPerformanceTracking1(const std::string& data)
{
    // TODO
    // Check if response string contains actual data
    return data;
}

float Elm327DataDecoder::GetEcuNameMessageCount(const std::string& data)
{
    return elm327::decoders::DecodeCountA(data);
}

std::string Elm327DataDecoder::GetEcuName(const std::string& data)
{
    return elm327::decoders::DecodeString(data);
}

std::string Elm327DataDecoder::GetPerformanceTracking2(const std::string& data)
{
    // TODO
    // Check if response string contains actual data
    return data;
}
