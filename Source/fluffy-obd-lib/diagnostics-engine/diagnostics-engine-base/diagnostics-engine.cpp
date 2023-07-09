#include "diagnostics-engine.hpp"

bool ParametersEngine::SendCommand(const std::string& command)
{
    std::clog << "Sending command: " << command << '\n';
    ssize_t bytesWritten = write(m_ConnectionHandle, command.c_str(), command.length());

    if (!command.ends_with('\r')) {
        write(m_ConnectionHandle, "\r", 1);
    }

    if (bytesWritten == -1) {
        throw(std::runtime_error(
            std::string("Exception on sending command ") + command + " : " + getStrerror(errno)));
    }
    return true;
}

std::string ParametersEngine::ReadResponse()
{
    usleep(m_readSleepTime);
    std::array<char, BUFFER_SIZE> readBuffer { '\0' };

    ssize_t dataReadCount = read(m_ConnectionHandle, &readBuffer, BUFFER_SIZE);

    if (dataReadCount < 0) {
        throw(std::runtime_error(
            std::string("Exception on reading response : ") + getStrerror(errno)));
    }
    std::string response { std::begin(readBuffer), std::end(readBuffer) };

    std::clog << "Recived response: " << response << '\n';
    return response;
}

void ParametersEngine::SetSerialDevice(Obd::Device device) { m_SerialDevice = std::move(device); }

Response ParametersEngine::GetCommandResponse(ObdCommandPid pid)
{
    using enum ObdCommandPid;

    switch (pid) {
    case S01P00: {
        std::string command = m_CommandRepository->GetSupportedPIDs1();
        SendCommand(command);
        RawResponse parsedResponse = m_dataFilter->ParseResponse(ReadResponse(), 4, command);
        return Response { parsedResponse, m_dataDecoder->GetSupportedPIDs1(parsedResponse.m_data) };
        break;
    }
    case S01P01: {
        std::string command = m_CommandRepository->GetMonitorStatus();
        SendCommand(command);
        RawResponse parsedResponse = m_dataFilter->ParseResponse(ReadResponse(), 4, command);
        return Response { parsedResponse, m_dataDecoder->GetMonitorStatus(parsedResponse.m_data) };
        break;
    }
    case S01P02: {
        std::string command = m_CommandRepository->GetFreezeDTCs();
        SendCommand(command);
        RawResponse parsedResponse = m_dataFilter->ParseResponse(ReadResponse(), 2, command);
        return Response { parsedResponse, m_dataDecoder->GetFreezeDTCs(parsedResponse.m_data),
            "FreezeDTCs" };
        break;
    }
    case S01P03: {
        std::string command = m_CommandRepository->GetFuelSystemStatus();
        SendCommand(command);
        RawResponse parsedResponse = m_dataFilter->ParseResponse(ReadResponse(), 2, command);
        return Response { parsedResponse,
            m_dataDecoder->GetFuelSystemStatus(parsedResponse.m_data) };
        break;
    }
    case S01P04: {
        std::string command = m_CommandRepository->GetEngineLoad();
        SendCommand(command);
        RawResponse parsedResponse = m_dataFilter->ParseResponse(ReadResponse(), 1, command);
        return Response { parsedResponse, m_dataDecoder->GetEngineLoad(parsedResponse.m_data),
            "%" };
        break;
    }
    case S01P05: {
        std::string command = m_CommandRepository->GetEngineCoolantTemperature();
        SendCommand(command);
        RawResponse parsedResponse = m_dataFilter->ParseResponse(ReadResponse(), 1, command);
        return Response { parsedResponse,
            m_dataDecoder->GetEngineCoolantTemperature(parsedResponse.m_data), "°C" };
        break;
    }
    case S01P06: {
        std::string command = m_CommandRepository->GetShortTermFuelTrimBank1();
        SendCommand(command);
        RawResponse parsedResponse = m_dataFilter->ParseResponse(ReadResponse(), 1, command);
        return Response { parsedResponse,
            m_dataDecoder->GetShortTermFuelTrimBank1(parsedResponse.m_data), "%" };
        break;
    }
    case S01P07: {
        std::string command = m_CommandRepository->GetLongTermFuelTrimBank1();
        SendCommand(command);
        RawResponse parsedResponse = m_dataFilter->ParseResponse(ReadResponse(), 1, command);
        return Response { parsedResponse,
            m_dataDecoder->GetLongTermFuelTrimBank1(parsedResponse.m_data), "%" };
        break;
    }
    case S01P08: {
        std::string command = m_CommandRepository->GetShortTermFuelTrimBank2();
        SendCommand(command);
        RawResponse parsedResponse = m_dataFilter->ParseResponse(ReadResponse(), 1, command);
        return Response { parsedResponse,
            m_dataDecoder->GetShortTermFuelTrimBank2(parsedResponse.m_data), "%" };
        break;
    }
    case S01P09: {
        std::string command = m_CommandRepository->GetLongTermFuelTrimBank2();
        SendCommand(command);
        RawResponse parsedResponse = m_dataFilter->ParseResponse(ReadResponse(), 1, command);
        return Response { parsedResponse,
            m_dataDecoder->GetLongTermFuelTrimBank2(parsedResponse.m_data), "%" };
        break;
    }
    case S01P0A: {
        std::string command = m_CommandRepository->GetFuelPressure();
        SendCommand(command);
        RawResponse parsedResponse = m_dataFilter->ParseResponse(ReadResponse(), 1, command);
        return Response { parsedResponse, m_dataDecoder->GetFuelPressure(parsedResponse.m_data),
            "kPa" };
        break;
    }
    case S01P0B: {
        std::string command = m_CommandRepository->GetIntakeManifoldPressure();
        SendCommand(command);
        RawResponse parsedResponse = m_dataFilter->ParseResponse(ReadResponse(), 1, command);
        return Response { parsedResponse,
            m_dataDecoder->GetIntakeManifoldPressure(parsedResponse.m_data), "kPa" };
        break;
    }
    case S01P0C: {
        std::string command = m_CommandRepository->GetEngineRpm();
        SendCommand(command);
        RawResponse parsedResponse = m_dataFilter->ParseResponse(ReadResponse(), 2, command);
        return Response { parsedResponse, m_dataDecoder->GetEngineRpm(parsedResponse.m_data),
            "rpm" };
        break;
    }
    case S01P0D: {
        std::string command = m_CommandRepository->GetSpeed();
        SendCommand(command);
        RawResponse parsedResponse = m_dataFilter->ParseResponse(ReadResponse(), 1, command);
        return Response { parsedResponse, m_dataDecoder->GetSpeed(parsedResponse.m_data), "km/h" };
        break;
    }
    case S01P0E: {
        std::string command = m_CommandRepository->GetTimingAdvance();
        SendCommand(command);
        RawResponse parsedResponse = m_dataFilter->ParseResponse(ReadResponse(), 1, command);
        return Response { parsedResponse, m_dataDecoder->GetTimingAdvance(parsedResponse.m_data),
            "° before TDC" };
        break;
    }
    case S01P0F: {
        std::string command = m_CommandRepository->GetIntakeAirTemperature();
        SendCommand(command);
        RawResponse parsedResponse = m_dataFilter->ParseResponse(ReadResponse(), 1, command);
        return Response { parsedResponse,
            m_dataDecoder->GetIntakeAirTemperature(parsedResponse.m_data), "°C" };
        break;
    }
    case S01P10: {
        std::string command = m_CommandRepository->GetMafAirFlowRate();
        SendCommand(command);
        RawResponse parsedResponse = m_dataFilter->ParseResponse(ReadResponse(), 2, command);
        return Response { parsedResponse, m_dataDecoder->GetMafAirFlowRate(parsedResponse.m_data),
            "g/s" };
        break;
    }
    case S01P11: {
        std::string command = m_CommandRepository->GetThrottlePosition();
        SendCommand(command);
        RawResponse parsedResponse = m_dataFilter->ParseResponse(ReadResponse(), 1, command);
        return Response { parsedResponse, m_dataDecoder->GetThrottlePosition(parsedResponse.m_data),
            "%" };
        break;
    }
    case S01P12: {
        std::string command = m_CommandRepository->GetSecondaryAirStatus();
        SendCommand(command);
        RawResponse parsedResponse = m_dataFilter->ParseResponse(ReadResponse(), 1, command);
        return Response { parsedResponse,
            m_dataDecoder->GetSecondaryAirStatus(parsedResponse.m_data) };
        break;
    }
    case S01P13: {
        std::string command = m_CommandRepository->GetOxygenSensorsPresent1();
        SendCommand(command);
        RawResponse parsedResponse = m_dataFilter->ParseResponse(ReadResponse(), 1, command);
        return Response { parsedResponse,
            m_dataDecoder->GetOxygenSensorsPresent1(parsedResponse.m_data) };
        break;
    }
    case S01P14: {
        std::string command = m_CommandRepository->GetOxygenSensorFtV1();
        SendCommand(command);
        RawResponse parsedResponse = m_dataFilter->ParseResponse(ReadResponse(), 2, command);
        std::pair<float, float> decodedPair
            = m_dataDecoder->GetOxygenSensorFtV1(parsedResponse.m_data);
        return Response { parsedResponse, decodedPair.first, "V", decodedPair.second, "%" };
        break;
    }
    case S01P15: {
        std::string command = m_CommandRepository->GetOxygenSensorFtV2();
        SendCommand(command);
        RawResponse parsedResponse = m_dataFilter->ParseResponse(ReadResponse(), 2, command);
        std::pair<float, float> decodedPair
            = m_dataDecoder->GetOxygenSensorFtV2(parsedResponse.m_data);
        return Response { parsedResponse, decodedPair.first, "V", decodedPair.second, "%" };
        break;
    }
    case S01P16: {
        std::string command = m_CommandRepository->GetOxygenSensorFtV3();
        SendCommand(command);
        RawResponse parsedResponse = m_dataFilter->ParseResponse(ReadResponse(), 2, command);
        std::pair<float, float> decodedPair
            = m_dataDecoder->GetOxygenSensorFtV3(parsedResponse.m_data);
        return Response { parsedResponse, decodedPair.first, "V", decodedPair.second, "%" };
        break;
    }
    case S01P17: {
        std::string command = m_CommandRepository->GetOxygenSensorFtV4();
        SendCommand(command);
        RawResponse parsedResponse = m_dataFilter->ParseResponse(ReadResponse(), 2, command);
        std::pair<float, float> decodedPair
            = m_dataDecoder->GetOxygenSensorFtV4(parsedResponse.m_data);
        return Response { parsedResponse, decodedPair.first, "V", decodedPair.second, "%" };
        break;
    }
    case S01P18: {
        std::string command = m_CommandRepository->GetOxygenSensorFtV5();
        SendCommand(command);
        RawResponse parsedResponse = m_dataFilter->ParseResponse(ReadResponse(), 2, command);
        std::pair<float, float> decodedPair
            = m_dataDecoder->GetOxygenSensorFtV5(parsedResponse.m_data);
        return Response { parsedResponse, decodedPair.first, "V", decodedPair.second, "%" };
        break;
    }
    case S01P19: {
        std::string command = m_CommandRepository->GetOxygenSensorFtV6();
        SendCommand(command);
        RawResponse parsedResponse = m_dataFilter->ParseResponse(ReadResponse(), 2, command);
        std::pair<float, float> decodedPair
            = m_dataDecoder->GetOxygenSensorFtV6(parsedResponse.m_data);
        return Response { parsedResponse, decodedPair.first, "V", decodedPair.second, "%" };
        break;
    }
    case S01P1A: {
        std::string command = m_CommandRepository->GetOxygenSensorFtV7();
        SendCommand(command);
        RawResponse parsedResponse = m_dataFilter->ParseResponse(ReadResponse(), 2, command);
        std::pair<float, float> decodedPair
            = m_dataDecoder->GetOxygenSensorFtV7(parsedResponse.m_data);
        return Response { parsedResponse, decodedPair.first, "V", decodedPair.second, "%" };
        break;
    }
    case S01P1B: {
        std::string command = m_CommandRepository->GetOxygenSensorFtV8();
        SendCommand(command);
        RawResponse parsedResponse = m_dataFilter->ParseResponse(ReadResponse(), 2, command);
        std::pair<float, float> decodedPair
            = m_dataDecoder->GetOxygenSensorFtV8(parsedResponse.m_data);
        return Response { parsedResponse, decodedPair.first, "V", decodedPair.second, "%" };
        break;
    }
    case S01P1C: {
        std::string command = m_CommandRepository->GetObdStandard();
        SendCommand(command);
        RawResponse parsedResponse = m_dataFilter->ParseResponse(ReadResponse(), 1, command);
        return Response { parsedResponse, m_dataDecoder->GetObdStandard(parsedResponse.m_data) };
        break;
    }
    case S01P1D: {
        std::string command = m_CommandRepository->GetOxygenSensorsPresent2();
        SendCommand(command);
        RawResponse parsedResponse = m_dataFilter->ParseResponse(ReadResponse(), 1, command);
        return Response { parsedResponse,
            m_dataDecoder->GetOxygenSensorsPresent2(parsedResponse.m_data) };
        break;
    }
    case S01P1E: {
        std::string command = m_CommandRepository->GetAuxiliaryInputStatus();
        SendCommand(command);
        RawResponse parsedResponse = m_dataFilter->ParseResponse(ReadResponse(), 1, command);
        return Response { parsedResponse,
            m_dataDecoder->GetAuxiliaryInputStatus(parsedResponse.m_data) };
        break;
    }
    case S01P1F: {
        std::string command = m_CommandRepository->GetRunTime();
        SendCommand(command);
        RawResponse parsedResponse = m_dataFilter->ParseResponse(ReadResponse(), 2, command);
        return Response { parsedResponse, m_dataDecoder->GetRunTime(parsedResponse.m_data), "s" };
        break;
    }
    case S01P20: {
        std::string command = m_CommandRepository->GetSupportedPIDs2();
        SendCommand(command);
        RawResponse parsedResponse = m_dataFilter->ParseResponse(ReadResponse(), 4, command);
        return Response { parsedResponse, m_dataDecoder->GetSupportedPIDs2(parsedResponse.m_data) };
        break;
    }
    case S01P21: {
        std::string command = m_CommandRepository->GetDistanceWithMilOn();
        SendCommand(command);
        RawResponse parsedResponse = m_dataFilter->ParseResponse(ReadResponse(), 2, command);
        return Response { parsedResponse,
            m_dataDecoder->GetDistanceWithMilOn(parsedResponse.m_data), "km" };
        break;
    }
    case S01P22: {
        std::string command = m_CommandRepository->GetFuelRailPressure();
        SendCommand(command);
        RawResponse parsedResponse = m_dataFilter->ParseResponse(ReadResponse(), 2, command);
        return Response { parsedResponse, m_dataDecoder->GetFuelRailPressure(parsedResponse.m_data),
            "kPa" };
        break;
    }
    case S01P23: {
        std::string command = m_CommandRepository->GetFuelRailGaugePressure();
        SendCommand(command);
        RawResponse parsedResponse = m_dataFilter->ParseResponse(ReadResponse(), 2, command);
        return Response { parsedResponse,
            m_dataDecoder->GetFuelRailGaugePressure(parsedResponse.m_data), "kPa" };
        break;
    }
    case S01P24: {
        std::string command = m_CommandRepository->GetOxygenSensorEqV1();
        SendCommand(command);
        RawResponse parsedResponse = m_dataFilter->ParseResponse(ReadResponse(), 2, command);
        std::pair<float, float> decodedPair
            = m_dataDecoder->GetOxygenSensorEqV1(parsedResponse.m_data);
        return Response { parsedResponse, decodedPair.first, "ratio", decodedPair.second, "V" };
        break;
    }
    case S01P25: {
        std::string command = m_CommandRepository->GetOxygenSensorEqV2();
        SendCommand(command);
        RawResponse parsedResponse = m_dataFilter->ParseResponse(ReadResponse(), 2, command);
        std::pair<float, float> decodedPair
            = m_dataDecoder->GetOxygenSensorEqV2(parsedResponse.m_data);
        return Response { parsedResponse, decodedPair.first, "ratio", decodedPair.second, "V" };
        break;
    }
    case S01P26: {
        std::string command = m_CommandRepository->GetOxygenSensorEqV3();
        SendCommand(command);
        RawResponse parsedResponse = m_dataFilter->ParseResponse(ReadResponse(), 2, command);
        std::pair<float, float> decodedPair
            = m_dataDecoder->GetOxygenSensorEqV3(parsedResponse.m_data);
        return Response { parsedResponse, decodedPair.first, "ratio", decodedPair.second, "V" };
        break;
    }
    case S01P27: {
        std::string command = m_CommandRepository->GetOxygenSensorEqV4();
        SendCommand(command);
        RawResponse parsedResponse = m_dataFilter->ParseResponse(ReadResponse(), 2, command);
        std::pair<float, float> decodedPair
            = m_dataDecoder->GetOxygenSensorEqV4(parsedResponse.m_data);
        return Response { parsedResponse, decodedPair.first, "ratio", decodedPair.second, "V" };
        break;
    }
    case S01P28: {
        std::string command = m_CommandRepository->GetOxygenSensorEqV5();
        SendCommand(command);
        RawResponse parsedResponse = m_dataFilter->ParseResponse(ReadResponse(), 2, command);
        std::pair<float, float> decodedPair
            = m_dataDecoder->GetOxygenSensorEqV5(parsedResponse.m_data);
        return Response { parsedResponse, decodedPair.first, "ratio", decodedPair.second, "V" };
        break;
    }
    case S01P29: {
        std::string command = m_CommandRepository->GetOxygenSensorEqV6();
        SendCommand(command);
        RawResponse parsedResponse = m_dataFilter->ParseResponse(ReadResponse(), 2, command);
        std::pair<float, float> decodedPair
            = m_dataDecoder->GetOxygenSensorEqV6(parsedResponse.m_data);
        return Response { parsedResponse, decodedPair.first, "ratio", decodedPair.second, "V" };
        break;
    }
    case S01P2A: {
        std::string command = m_CommandRepository->GetOxygenSensorEqV7();
        SendCommand(command);
        RawResponse parsedResponse = m_dataFilter->ParseResponse(ReadResponse(), 2, command);
        std::pair<float, float> decodedPair
            = m_dataDecoder->GetOxygenSensorEqV7(parsedResponse.m_data);
        return Response { parsedResponse, decodedPair.first, "ratio", decodedPair.second, "V" };
        break;
    }
    case S01P2B: {
        std::string command = m_CommandRepository->GetOxygenSensorEqV8();
        SendCommand(command);
        RawResponse parsedResponse = m_dataFilter->ParseResponse(ReadResponse(), 2, command);
        std::pair<float, float> decodedPair
            = m_dataDecoder->GetOxygenSensorEqV8(parsedResponse.m_data);
        return Response { parsedResponse, decodedPair.first, "ratio", decodedPair.second, "V" };
        break;
    }
    case S01P2C: {
        std::string command = m_CommandRepository->GetCommandedEgr();
        SendCommand(command);
        RawResponse parsedResponse = m_dataFilter->ParseResponse(ReadResponse(), 1, command);
        return Response { parsedResponse, m_dataDecoder->GetCommandedEgr(parsedResponse.m_data),
            "%" };
        break;
    }
    case S01P2D: {
        std::string command = m_CommandRepository->GetEgrError();
        SendCommand(command);
        RawResponse parsedResponse = m_dataFilter->ParseResponse(ReadResponse(), 1, command);
        return Response { parsedResponse, m_dataDecoder->GetEgrError(parsedResponse.m_data), "%" };
        break;
    }
    case S01P2E: {
        std::string command = m_CommandRepository->GetCommandedEvaporativePurge();
        SendCommand(command);
        RawResponse parsedResponse = m_dataFilter->ParseResponse(ReadResponse(), 1, command);
        return Response { parsedResponse,
            m_dataDecoder->GetCommandedEvaporativePurge(parsedResponse.m_data), "%" };
        break;
    }
    case S01P2F: {
        std::string command = m_CommandRepository->GetFuelTankLevelInput();
        SendCommand(command);
        RawResponse parsedResponse = m_dataFilter->ParseResponse(ReadResponse(), 1, command);
        return Response { parsedResponse,
            m_dataDecoder->GetFuelTankLevelInput(parsedResponse.m_data), "%" };
        break;
    }
    case S01P30: {
        std::string command = m_CommandRepository->GetWarmupsSinceDtcCleared();
        SendCommand(command);
        RawResponse parsedResponse = m_dataFilter->ParseResponse(ReadResponse(), 1, command);
        return Response { parsedResponse,
            m_dataDecoder->GetWarmupsSinceDtcCleared(parsedResponse.m_data), "" };
        break;
    }
    case S01P31: {
        std::string command = m_CommandRepository->GetDistanceSinceDtcCleared();
        SendCommand(command);
        RawResponse parsedResponse = m_dataFilter->ParseResponse(ReadResponse(), 2, command);
        return Response { parsedResponse,
            m_dataDecoder->GetDistanceSinceDtcCleared(parsedResponse.m_data), "km" };
        break;
    }
    case S01P32: {
        std::string command = m_CommandRepository->GetEvapVaporPressure();
        SendCommand(command);
        RawResponse parsedResponse = m_dataFilter->ParseResponse(ReadResponse(), 2, command);
        return Response { parsedResponse,
            m_dataDecoder->GetEvapVaporPressure(parsedResponse.m_data), "Pa" };
        break;
    }
    case S01P33: {
        std::string command = m_CommandRepository->GetAbsoluteBarometricPressure();
        SendCommand(command);
        RawResponse parsedResponse = m_dataFilter->ParseResponse(ReadResponse(), 1, command);
        return Response { parsedResponse,
            m_dataDecoder->GetAbsoluteBarometricPressure(parsedResponse.m_data), "kPa" };
        break;
    }
    case S01P34: {
        std::string command = m_CommandRepository->GetOxygenSensorEqC1();
        SendCommand(command);
        RawResponse parsedResponse = m_dataFilter->ParseResponse(ReadResponse(), 4, command);
        std::pair<float, float> decodedPair
            = m_dataDecoder->GetOxygenSensorEqC1(parsedResponse.m_data);
        return Response { parsedResponse, decodedPair.first, "ratio", decodedPair.second, "mA" };
        break;
    }
    case S01P35: {
        std::string command = m_CommandRepository->GetOxygenSensorEqC2();
        SendCommand(command);
        RawResponse parsedResponse = m_dataFilter->ParseResponse(ReadResponse(), 4, command);
        std::pair<float, float> decodedPair
            = m_dataDecoder->GetOxygenSensorEqC2(parsedResponse.m_data);
        return Response { parsedResponse, decodedPair.first, "ratio", decodedPair.second, "mA" };
        break;
    }
    case S01P36: {
        std::string command = m_CommandRepository->GetOxygenSensorEqC3();
        SendCommand(command);
        RawResponse parsedResponse = m_dataFilter->ParseResponse(ReadResponse(), 4, command);
        std::pair<float, float> decodedPair
            = m_dataDecoder->GetOxygenSensorEqC3(parsedResponse.m_data);
        return Response { parsedResponse, decodedPair.first, "ratio", decodedPair.second, "mA" };
        break;
    }
    case S01P37: {
        std::string command = m_CommandRepository->GetOxygenSensorEqC4();
        SendCommand(command);
        RawResponse parsedResponse = m_dataFilter->ParseResponse(ReadResponse(), 4, command);
        std::pair<float, float> decodedPair
            = m_dataDecoder->GetOxygenSensorEqC4(parsedResponse.m_data);
        return Response { parsedResponse, decodedPair.first, "ratio", decodedPair.second, "mA" };
        break;
    }
    case S01P38: {
        std::string command = m_CommandRepository->GetOxygenSensorEqC5();
        SendCommand(command);
        RawResponse parsedResponse = m_dataFilter->ParseResponse(ReadResponse(), 4, command);
        std::pair<float, float> decodedPair
            = m_dataDecoder->GetOxygenSensorEqC5(parsedResponse.m_data);
        return Response { parsedResponse, decodedPair.first, "ratio", decodedPair.second, "mA" };
        break;
    }
    case S01P39: {
        std::string command = m_CommandRepository->GetOxygenSensorEqC6();
        SendCommand(command);
        RawResponse parsedResponse = m_dataFilter->ParseResponse(ReadResponse(), 4, command);
        std::pair<float, float> decodedPair
            = m_dataDecoder->GetOxygenSensorEqC6(parsedResponse.m_data);
        return Response { parsedResponse, decodedPair.first, "ratio", decodedPair.second, "mA" };
        break;
    }
    case S01P3A: {
        std::string command = m_CommandRepository->GetOxygenSensorEqC7();
        SendCommand(command);
        RawResponse parsedResponse = m_dataFilter->ParseResponse(ReadResponse(), 4, command);
        std::pair<float, float> decodedPair
            = m_dataDecoder->GetOxygenSensorEqC7(parsedResponse.m_data);
        return Response { parsedResponse, decodedPair.first, "ratio", decodedPair.second, "mA" };
        break;
    }
    case S01P3B: {
        std::string command = m_CommandRepository->GetOxygenSensorEqC8();
        SendCommand(command);
        RawResponse parsedResponse = m_dataFilter->ParseResponse(ReadResponse(), 4, command);
        std::pair<float, float> decodedPair
            = m_dataDecoder->GetOxygenSensorEqC8(parsedResponse.m_data);
        return Response { parsedResponse, decodedPair.first, "ratio", decodedPair.second, "mA" };
        break;
    }
    case S01P3C: {
        std::string command = m_CommandRepository->GetCatalystTemperatureB1S1();
        SendCommand(command);
        RawResponse parsedResponse = m_dataFilter->ParseResponse(ReadResponse(), 2, command);
        return Response { parsedResponse,
            m_dataDecoder->GetCatalystTemperatureB1S1(parsedResponse.m_data), "°C" };
        break;
    }
    case S01P3D: {
        std::string command = m_CommandRepository->GetCatalystTemperatureB2S1();
        SendCommand(command);
        RawResponse parsedResponse = m_dataFilter->ParseResponse(ReadResponse(), 2, command);
        return Response { parsedResponse,
            m_dataDecoder->GetCatalystTemperatureB2S1(parsedResponse.m_data), "°C" };
        break;
    }
    case S01P3E: {
        std::string command = m_CommandRepository->GetCatalystTemperatureB1S2();
        SendCommand(command);
        RawResponse parsedResponse = m_dataFilter->ParseResponse(ReadResponse(), 2, command);
        return Response { parsedResponse,
            m_dataDecoder->GetCatalystTemperatureB1S2(parsedResponse.m_data), "°C" };
        break;
    }
    case S01P3F: {
        std::string command = m_CommandRepository->GetCatalystTemperatureB2S2();
        SendCommand(command);
        RawResponse parsedResponse = m_dataFilter->ParseResponse(ReadResponse(), 2, command);
        return Response { parsedResponse,
            m_dataDecoder->GetCatalystTemperatureB2S2(parsedResponse.m_data), "°C" };
        break;
    }
    default:
        return Response {};
    }
}
