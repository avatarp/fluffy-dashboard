#include "elm327-data-parser.hpp"

Elm327DataParser::Elm327DataParser()
{
    m_decoder = std::make_shared<Elm327DataDecoder>();
}

Response Elm327DataParser::ParseResponse(const std::string& command, std::string response, ObdCommandPid pid)
{
    spdlog::info("Parsing response: {}", response);

    constexpr uint8_t ecuIdGroupIndex { 2 };
    constexpr uint8_t responseSizeGroupIndex { 3 };
    constexpr uint8_t commandPidGroupIndex { 4 };
    constexpr uint8_t dataGroupIndex { 5 };

    std::smatch match;
    const std::regex responseRegexPattern { "(([0-9A-Z]{3})([0-9]{2}))?4("
        + command.substr(1, command.size() - 2)
        + ")([0-9A-F]+)" };

    response.erase(remove_if(response.begin(), response.end(), isspace), response.end());

    if (!std::regex_search(response, match, responseRegexPattern)) {
        throw(std::runtime_error { "Response to: "
            + command.substr(0, command.size() - 2)
            + ", not matched!\n" });
    }

    if (static_cast<size_t>(match[dataGroupIndex].length()) != getExpectedResponseSizeByPid(pid) * 2) {

        throw(std::runtime_error { "Response to: " + command + ", data length mismatching expected size!\n" });
    }

    Response parsedResponse;
    parsedResponse.m_rawCommandId = { command[0] + match[commandPidGroupIndex].str() };
    parsedResponse.m_rawData = match[dataGroupIndex];
    parsedResponse.m_rawEcuId = match[ecuIdGroupIndex];
    if (!match[responseSizeGroupIndex].str().empty()) {
        parsedResponse.m_rawLength = static_cast<uint8_t>(std::stoi(match[responseSizeGroupIndex].str()));
    }

    processResponse(parsedResponse, pid);

    return parsedResponse;
}

void Elm327DataParser::processResponse(Response& parsedResponse, ObdCommandPid pid)
{
    using enum ObdCommandPid;

    switch (pid) {
    case S01P00:
        parsedResponse.m_dataType = DataType::bitset;
        parsedResponse.m_dataBitset = m_decoder->GetSupportedPIDs1(parsedResponse.m_rawData);
        return;

    case S01P01:
        parsedResponse.m_dataType = DataType::bitset;
        parsedResponse.m_dataBitset = m_decoder->GetMonitorStatus(parsedResponse.m_rawData);
        return;
    case S01P02:
        parsedResponse.m_dataType = DataType::string;
        parsedResponse.m_dataString = std::pair<std::string, std::string>(
            m_decoder->GetFreezeDTCs(parsedResponse.m_rawData), "FreezeDTCs");
        return;
    case S01P03:
        parsedResponse.m_dataType = DataType::bitset;
        parsedResponse.m_dataBitset = m_decoder->GetFuelSystemStatus(parsedResponse.m_rawData);
        return;
    case S01P04:
        parsedResponse.m_dataType = DataType::number;
        parsedResponse.m_dataFloat1 = { m_decoder->GetEngineLoad(parsedResponse.m_rawData), "%" };
        return;
    case S01P05:
        parsedResponse.m_dataType = DataType::number;
        parsedResponse.m_dataFloat1 = { m_decoder->GetEngineCoolantTemperature(parsedResponse.m_rawData), "°C" };
        return;
    case S01P06:
        parsedResponse.m_dataType = DataType::number;
        parsedResponse.m_dataFloat1 = { m_decoder->GetShortTermFuelTrimBank1(parsedResponse.m_rawData), "%" };
        return;
    case S01P07:
        parsedResponse.m_dataType = DataType::number;
        parsedResponse.m_dataFloat1 = { m_decoder->GetLongTermFuelTrimBank1(parsedResponse.m_rawData), "%" };
        return;
    case S01P08:
        parsedResponse.m_dataType = DataType::number;
        parsedResponse.m_dataFloat1 = { m_decoder->GetShortTermFuelTrimBank2(parsedResponse.m_rawData), "%" };
        return;
    case S01P09:
        parsedResponse.m_dataType = DataType::number;
        parsedResponse.m_dataFloat1 = { m_decoder->GetLongTermFuelTrimBank2(parsedResponse.m_rawData), "%" };
        return;
    case S01P0A:
        parsedResponse.m_dataType = DataType::number;
        parsedResponse.m_dataFloat1 = { m_decoder->GetFuelPressure(parsedResponse.m_rawData), "kPa" };
        return;
    case S01P0B:
        parsedResponse.m_dataType = DataType::number;
        parsedResponse.m_dataFloat1 = { m_decoder->GetIntakeManifoldPressure(parsedResponse.m_rawData), "kPa" };
        return;
    case S01P0C:
        parsedResponse.m_dataType = DataType::number;
        parsedResponse.m_dataFloat1 = { m_decoder->GetEngineRpm(parsedResponse.m_rawData), "rpm" };
        return;
    case S01P0D:
        parsedResponse.m_dataType = DataType::number;
        parsedResponse.m_dataFloat1 = { m_decoder->GetSpeed(parsedResponse.m_rawData), "km/h" };
        return;
    case S01P0E:
        parsedResponse.m_dataType = DataType::number;
        parsedResponse.m_dataFloat1 = { m_decoder->GetTimingAdvance(parsedResponse.m_rawData), "° before TDC" };
        return;
    case S01P0F:
        parsedResponse.m_dataType = DataType::number;
        parsedResponse.m_dataFloat1 = { m_decoder->GetIntakeAirTemperature(parsedResponse.m_rawData), "°C" };
        return;
    case S01P10:
        parsedResponse.m_dataType = DataType::number;
        parsedResponse.m_dataFloat1 = { m_decoder->GetMafAirFlowRate(parsedResponse.m_rawData), "g/s" };
        return;
    case S01P11:
        parsedResponse.m_dataType = DataType::number;
        parsedResponse.m_dataFloat1 = { m_decoder->GetThrottlePosition(parsedResponse.m_rawData), "%" };
        return;
    case S01P12:
        parsedResponse.m_dataType = DataType::bitset;
        parsedResponse.m_dataBitset = m_decoder->GetSecondaryAirStatus(parsedResponse.m_rawData);
        return;
    case S01P13:
        parsedResponse.m_dataType = DataType::bitset;
        parsedResponse.m_dataBitset = m_decoder->GetOxygenSensorsPresent1(parsedResponse.m_rawData);
        return;
    case S01P14: {
        parsedResponse.m_dataType = DataType::numberPair;
        auto decodedPair = m_decoder->GetOxygenSensorFtV1(parsedResponse.m_rawData);
        parsedResponse.m_dataFloat1 = { decodedPair.first, "V" };
        parsedResponse.m_dataFloat2 = { decodedPair.second, "%" };
        return;
    }
    case S01P15: {
        parsedResponse.m_dataType = DataType::numberPair;
        auto decodedPair = m_decoder->GetOxygenSensorFtV2(parsedResponse.m_rawData);
        parsedResponse.m_dataFloat1 = { decodedPair.first, "V" };
        parsedResponse.m_dataFloat2 = { decodedPair.second, "%" };
        return;
    }
    case S01P16: {
        parsedResponse.m_dataType = DataType::numberPair;
        auto decodedPair = m_decoder->GetOxygenSensorFtV3(parsedResponse.m_rawData);
        parsedResponse.m_dataFloat1 = { decodedPair.first, "V" };
        parsedResponse.m_dataFloat2 = { decodedPair.second, "%" };
        return;
    }
    case S01P17: {
        parsedResponse.m_dataType = DataType::numberPair;
        auto decodedPair = m_decoder->GetOxygenSensorFtV4(parsedResponse.m_rawData);
        parsedResponse.m_dataFloat1 = { decodedPair.first, "V" };
        parsedResponse.m_dataFloat2 = { decodedPair.second, "%" };
        return;
    }
    case S01P18: {
        parsedResponse.m_dataType = DataType::numberPair;
        auto decodedPair = m_decoder->GetOxygenSensorFtV5(parsedResponse.m_rawData);
        parsedResponse.m_dataFloat1 = { decodedPair.first, "V" };
        parsedResponse.m_dataFloat2 = { decodedPair.second, "%" };
        return;
    }
    case S01P19: {
        parsedResponse.m_dataType = DataType::numberPair;
        auto decodedPair = m_decoder->GetOxygenSensorFtV6(parsedResponse.m_rawData);
        parsedResponse.m_dataFloat1 = { decodedPair.first, "V" };
        parsedResponse.m_dataFloat2 = { decodedPair.second, "%" };
        return;
    }
    case S01P1A: {
        parsedResponse.m_dataType = DataType::numberPair;
        auto decodedPair = m_decoder->GetOxygenSensorFtV7(parsedResponse.m_rawData);
        parsedResponse.m_dataFloat1 = { decodedPair.first, "V" };
        parsedResponse.m_dataFloat2 = { decodedPair.second, "%" };
        return;
    }
    case S01P1B: {
        parsedResponse.m_dataType = DataType::numberPair;
        auto decodedPair = m_decoder->GetOxygenSensorFtV8(parsedResponse.m_rawData);
        parsedResponse.m_dataFloat1 = { decodedPair.first, "V" };
        parsedResponse.m_dataFloat2 = { decodedPair.second, "%" };
        return;
    }
    case S01P1C:
        parsedResponse.m_dataType = DataType::bitset;
        parsedResponse.m_dataBitset = m_decoder->GetObdStandard(parsedResponse.m_rawData);
        return;
    case S01P1D:
        parsedResponse.m_dataType = DataType::bitset;
        parsedResponse.m_dataBitset = m_decoder->GetOxygenSensorsPresent2(parsedResponse.m_rawData);
        return;
    case S01P1E:
        parsedResponse.m_dataType = DataType::bitset;
        parsedResponse.m_dataBitset = m_decoder->GetAuxiliaryInputStatus(parsedResponse.m_rawData);
        return;
    case S01P1F:
        parsedResponse.m_dataType = DataType::number;
        parsedResponse.m_dataFloat1 = { m_decoder->GetRunTime(parsedResponse.m_rawData), "s" };
        return;
    case S01P20:
        parsedResponse.m_dataType = DataType::bitset;
        parsedResponse.m_dataBitset = m_decoder->GetSupportedPIDs2(parsedResponse.m_rawData);
        return;
    case S01P21:
        parsedResponse.m_dataType = DataType::number;
        parsedResponse.m_dataFloat1 = { m_decoder->GetDistanceWithMilOn(parsedResponse.m_rawData), "km" };
        return;
    case S01P22:
        parsedResponse.m_dataType = DataType::number;
        parsedResponse.m_dataFloat1 = { m_decoder->GetFuelRailPressure(parsedResponse.m_rawData), "kPa" };
        return;
    case S01P23:
        parsedResponse.m_dataType = DataType::number;
        parsedResponse.m_dataFloat1 = { m_decoder->GetFuelRailGaugePressure(parsedResponse.m_rawData), "kPa" };
        return;
    case S01P24: {
        parsedResponse.m_dataType = DataType::numberPair;
        auto decodedPair = m_decoder->GetOxygenSensorEqV1(parsedResponse.m_rawData);
        parsedResponse.m_dataFloat1 = { decodedPair.first, "ratio" };
        parsedResponse.m_dataFloat2 = { decodedPair.second, "V" };
        return;
    }
    case S01P25: {
        parsedResponse.m_dataType = DataType::numberPair;
        auto decodedPair = m_decoder->GetOxygenSensorEqV2(parsedResponse.m_rawData);
        parsedResponse.m_dataFloat1 = { decodedPair.first, "ratio" };
        parsedResponse.m_dataFloat2 = { decodedPair.second, "V" };
        return;
    }
    case S01P26: {
        parsedResponse.m_dataType = DataType::numberPair;
        auto decodedPair = m_decoder->GetOxygenSensorEqV3(parsedResponse.m_rawData);
        parsedResponse.m_dataFloat1 = { decodedPair.first, "ratio" };
        parsedResponse.m_dataFloat2 = { decodedPair.second, "V" };
        return;
    }
    case S01P27: {
        parsedResponse.m_dataType = DataType::numberPair;
        auto decodedPair = m_decoder->GetOxygenSensorEqV4(parsedResponse.m_rawData);
        parsedResponse.m_dataFloat1 = { decodedPair.first, "ratio" };
        parsedResponse.m_dataFloat2 = { decodedPair.second, "V" };
        return;
    }
    case S01P28: {
        parsedResponse.m_dataType = DataType::numberPair;
        auto decodedPair = m_decoder->GetOxygenSensorEqV5(parsedResponse.m_rawData);
        parsedResponse.m_dataFloat1 = { decodedPair.first, "ratio" };
        parsedResponse.m_dataFloat2 = { decodedPair.second, "V" };
        return;
    }
    case S01P29: {
        parsedResponse.m_dataType = DataType::numberPair;
        auto decodedPair = m_decoder->GetOxygenSensorEqV6(parsedResponse.m_rawData);
        parsedResponse.m_dataFloat1 = { decodedPair.first, "ratio" };
        parsedResponse.m_dataFloat2 = { decodedPair.second, "V" };
        return;
    }
    case S01P2A: {
        parsedResponse.m_dataType = DataType::numberPair;
        auto decodedPair = m_decoder->GetOxygenSensorEqV7(parsedResponse.m_rawData);
        parsedResponse.m_dataFloat1 = { decodedPair.first, "ratio" };
        parsedResponse.m_dataFloat2 = { decodedPair.second, "V" };
        return;
    }
    case S01P2B: {
        parsedResponse.m_dataType = DataType::numberPair;
        auto decodedPair = m_decoder->GetOxygenSensorEqV8(parsedResponse.m_rawData);
        parsedResponse.m_dataFloat1 = { decodedPair.first, "ratio" };
        parsedResponse.m_dataFloat2 = { decodedPair.second, "V" };
        return;
    }
    case S01P2C:
        parsedResponse.m_dataType = DataType::number;
        parsedResponse.m_dataFloat1 = { m_decoder->GetCommandedEgr(parsedResponse.m_rawData), "%" };
        return;
    case S01P2D:
        parsedResponse.m_dataType = DataType::number;
        parsedResponse.m_dataFloat1 = { m_decoder->GetEgrError(parsedResponse.m_rawData), "%" };
        return;
    case S01P2E:
        parsedResponse.m_dataType = DataType::number;
        parsedResponse.m_dataFloat1 = { m_decoder->GetCommandedEvaporativePurge(parsedResponse.m_rawData), "%" };
        return;
    case S01P2F:
        parsedResponse.m_dataType = DataType::number;
        parsedResponse.m_dataFloat1 = { m_decoder->GetFuelTankLevelInput(parsedResponse.m_rawData), "%" };
        return;
    case S01P30:
        parsedResponse.m_dataType = DataType::number;
        parsedResponse.m_dataFloat1 = { m_decoder->GetWarmupsSinceDtcCleared(parsedResponse.m_rawData), "count" };
        return;
    case S01P31:
        parsedResponse.m_dataType = DataType::number;
        parsedResponse.m_dataFloat1 = { m_decoder->GetDistanceSinceDtcCleared(parsedResponse.m_rawData), "km" };
        return;
    case S01P32:
        parsedResponse.m_dataType = DataType::number;
        parsedResponse.m_dataFloat1 = { m_decoder->GetEvapVaporPressure(parsedResponse.m_rawData), "Pa" };
        return;
    case S01P33:
        parsedResponse.m_dataType = DataType::number;
        parsedResponse.m_dataFloat1 = { m_decoder->GetAbsoluteBarometricPressure(parsedResponse.m_rawData), "kPa" };
        return;
    case S01P34: {
        parsedResponse.m_dataType = DataType::numberPair;
        auto decodedPair = m_decoder->GetOxygenSensorEqC1(parsedResponse.m_rawData);
        parsedResponse.m_dataFloat1 = { decodedPair.first, "ratio" };
        parsedResponse.m_dataFloat2 = { decodedPair.second, "mA" };
        return;
    }
    case S01P35: {
        parsedResponse.m_dataType = DataType::numberPair;
        auto decodedPair = m_decoder->GetOxygenSensorEqC2(parsedResponse.m_rawData);
        parsedResponse.m_dataFloat1 = { decodedPair.first, "ratio" };
        parsedResponse.m_dataFloat2 = { decodedPair.second, "mA" };
        return;
    }
    case S01P36: {
        parsedResponse.m_dataType = DataType::numberPair;
        auto decodedPair = m_decoder->GetOxygenSensorEqC3(parsedResponse.m_rawData);
        parsedResponse.m_dataFloat1 = { decodedPair.first, "ratio" };
        parsedResponse.m_dataFloat2 = { decodedPair.second, "mA" };
        return;
    }
    case S01P37: {
        parsedResponse.m_dataType = DataType::numberPair;
        auto decodedPair = m_decoder->GetOxygenSensorEqC4(parsedResponse.m_rawData);
        parsedResponse.m_dataFloat1 = { decodedPair.first, "ratio" };
        parsedResponse.m_dataFloat2 = { decodedPair.second, "mA" };
        return;
    }
    case S01P38: {
        parsedResponse.m_dataType = DataType::numberPair;
        auto decodedPair = m_decoder->GetOxygenSensorEqC5(parsedResponse.m_rawData);
        parsedResponse.m_dataFloat1 = { decodedPair.first, "ratio" };
        parsedResponse.m_dataFloat2 = { decodedPair.second, "mA" };
        return;
    }
    case S01P39: {
        parsedResponse.m_dataType = DataType::numberPair;
        auto decodedPair = m_decoder->GetOxygenSensorEqC6(parsedResponse.m_rawData);
        parsedResponse.m_dataFloat1 = { decodedPair.first, "ratio" };
        parsedResponse.m_dataFloat2 = { decodedPair.second, "mA" };
        return;
    }
    case S01P3A: {
        parsedResponse.m_dataType = DataType::numberPair;
        auto decodedPair = m_decoder->GetOxygenSensorEqC7(parsedResponse.m_rawData);
        parsedResponse.m_dataFloat1 = { decodedPair.first, "ratio" };
        parsedResponse.m_dataFloat2 = { decodedPair.second, "mA" };
        return;
    }
    case S01P3B: {
        parsedResponse.m_dataType = DataType::numberPair;
        auto decodedPair = m_decoder->GetOxygenSensorEqC8(parsedResponse.m_rawData);
        parsedResponse.m_dataFloat1 = { decodedPair.first, "ratio" };
        parsedResponse.m_dataFloat2 = { decodedPair.second, "mA" };
        return;
    }
    case S01P3C: {
        parsedResponse.m_dataType = DataType::numberPair;
        parsedResponse.m_dataFloat1
            = { m_decoder->GetCatalystTemperatureB1S1(parsedResponse.m_rawData), "°C" };
        return;
    }
    case S01P3D:
        parsedResponse.m_dataType = DataType::number;
        parsedResponse.m_dataFloat1
            = { m_decoder->GetCatalystTemperatureB2S1(parsedResponse.m_rawData),
                  "°C" };
        return;
    case S01P3E:
        parsedResponse.m_dataType = DataType::number;
        parsedResponse.m_dataFloat1
            = { m_decoder->GetCatalystTemperatureB1S2(parsedResponse.m_rawData),
                  "°C" };
        return;
    case S01P3F:
        parsedResponse.m_dataType = DataType::number;
        parsedResponse.m_dataFloat1
            = { m_decoder->GetCatalystTemperatureB2S2(parsedResponse.m_rawData),
                  "°C" };
        return;

    case S09P00:
        parsedResponse.m_dataType = DataType::bitset;
        parsedResponse.m_dataBitset = m_decoder->GetSupportedVIPIDs(parsedResponse.m_rawData);
    default:
        return;
    }
}

std::size_t Elm327DataParser::getExpectedResponseSizeByPid(ObdCommandPid pid)
{
    using enum ObdCommandPid;
    switch (pid) {
    case S01P04:
    case S01P05:
    case S01P06:
    case S01P07:
    case S01P08:
    case S01P09:
    case S01P0A:
    case S01P0B:
    case S01P0D:
    case S01P0E:
    case S01P0F:
    case S01P11:
    case S01P12:
    case S01P13:
    case S01P1C:
    case S01P1D:
    case S01P1E:
    case S01P2C:
    case S01P2D:
    case S01P2E:
    case S01P2F:
    case S01P30:
    case S01P33:
        return 1;

    case S01P02:
    case S01P03:
    case S01P0C:
    case S01P10:
    case S01P14:
    case S01P15:
    case S01P16:
    case S01P17:
    case S01P18:
    case S01P19:
    case S01P1A:
    case S01P1B:
    case S01P1F:
    case S01P21:
    case S01P22:
    case S01P23:
    case S01P31:
    case S01P32:
    case S01P3C:
    case S01P3D:
    case S01P3E:
    case S01P3F:
        return 2;

    case S01P00:
    case S01P01:
    case S01P20:
    case S01P24:
    case S01P25:
    case S01P26:
    case S01P27:
    case S01P28:
    case S01P29:
    case S01P2A:
    case S01P2B:
    case S01P34:
    case S01P35:
    case S01P36:
    case S01P37:
    case S01P38:
    case S01P39:
    case S01P3B:
        // Other Pids currently not supported

    case S09P00:
        return 4;
    // GCOVR_EXCL_START
    default:
        return 0;
        // GCOVR_EXCL_STOP
    }
}
