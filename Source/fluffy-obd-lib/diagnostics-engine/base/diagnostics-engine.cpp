#include "diagnostics-engine.hpp"

bool ParametersEngine::SendCommand(const std::string& command)
{
    return m_obdAccess->Write(command);
}

std::string ParametersEngine::ReadResponse()
{
    return m_obdAccess->Read();
}

void ParametersEngine::SetSerialDevice(Obd::Device device)
{
    m_obdAccess->SetDevice(std::move(device));
}

void ParametersEngine::SetObdAccess(std::unique_ptr<Obd::ObdAccess> obdAccess)
{
    m_obdAccess = std::move(obdAccess);
}

Response ParametersEngine::GetCommandResponse(ObdCommandPid pid)
{
    using enum ObdCommandPid;

    switch (pid) {
    case S01P00: {
        std::string command = m_commandRepository->GetSupportedPIDs1();
        SendCommand(command);
        RawResponse parsedResponse = m_dataParser->ParseResponse(ReadResponse(), 4, command);
        return Response { parsedResponse, m_dataDecoder->GetSupportedPIDs1(parsedResponse.m_data) };
        break;
    }
    case S01P01: {
        std::string command = m_commandRepository->GetMonitorStatus();
        SendCommand(command);
        RawResponse parsedResponse = m_dataParser->ParseResponse(ReadResponse(), 4, command);
        return Response { parsedResponse, m_dataDecoder->GetMonitorStatus(parsedResponse.m_data) };
        break;
    }
    case S01P02: {
        std::string command = m_commandRepository->GetFreezeDTCs();
        SendCommand(command);
        RawResponse parsedResponse = m_dataParser->ParseResponse(ReadResponse(), 2, command);
        return Response { parsedResponse, m_dataDecoder->GetFreezeDTCs(parsedResponse.m_data),
            "FreezeDTCs" };
        break;
    }
    case S01P03: {
        std::string command = m_commandRepository->GetFuelSystemStatus();
        SendCommand(command);
        RawResponse parsedResponse = m_dataParser->ParseResponse(ReadResponse(), 2, command);
        return Response { parsedResponse,
            m_dataDecoder->GetFuelSystemStatus(parsedResponse.m_data) };
        break;
    }
    case S01P04: {
        std::string command = m_commandRepository->GetEngineLoad();
        SendCommand(command);
        RawResponse parsedResponse = m_dataParser->ParseResponse(ReadResponse(), 1, command);
        return Response { parsedResponse, m_dataDecoder->GetEngineLoad(parsedResponse.m_data),
            "%" };
        break;
    }
    case S01P05: {
        std::string command = m_commandRepository->GetEngineCoolantTemperature();
        SendCommand(command);
        RawResponse parsedResponse = m_dataParser->ParseResponse(ReadResponse(), 1, command);
        return Response { parsedResponse,
            m_dataDecoder->GetEngineCoolantTemperature(parsedResponse.m_data), "°C" };
        break;
    }
    case S01P06: {
        std::string command = m_commandRepository->GetShortTermFuelTrimBank1();
        SendCommand(command);
        RawResponse parsedResponse = m_dataParser->ParseResponse(ReadResponse(), 1, command);
        return Response { parsedResponse,
            m_dataDecoder->GetShortTermFuelTrimBank1(parsedResponse.m_data), "%" };
        break;
    }
    case S01P07: {
        std::string command = m_commandRepository->GetLongTermFuelTrimBank1();
        SendCommand(command);
        RawResponse parsedResponse = m_dataParser->ParseResponse(ReadResponse(), 1, command);
        return Response { parsedResponse,
            m_dataDecoder->GetLongTermFuelTrimBank1(parsedResponse.m_data), "%" };
        break;
    }
    case S01P08: {
        std::string command = m_commandRepository->GetShortTermFuelTrimBank2();
        SendCommand(command);
        RawResponse parsedResponse = m_dataParser->ParseResponse(ReadResponse(), 1, command);
        return Response { parsedResponse,
            m_dataDecoder->GetShortTermFuelTrimBank2(parsedResponse.m_data), "%" };
        break;
    }
    case S01P09: {
        std::string command = m_commandRepository->GetLongTermFuelTrimBank2();
        SendCommand(command);
        RawResponse parsedResponse = m_dataParser->ParseResponse(ReadResponse(), 1, command);
        return Response { parsedResponse,
            m_dataDecoder->GetLongTermFuelTrimBank2(parsedResponse.m_data), "%" };
        break;
    }
    case S01P0A: {
        std::string command = m_commandRepository->GetFuelPressure();
        SendCommand(command);
        RawResponse parsedResponse = m_dataParser->ParseResponse(ReadResponse(), 1, command);
        return Response { parsedResponse, m_dataDecoder->GetFuelPressure(parsedResponse.m_data),
            "kPa" };
        break;
    }
    case S01P0B: {
        std::string command = m_commandRepository->GetIntakeManifoldPressure();
        SendCommand(command);
        RawResponse parsedResponse = m_dataParser->ParseResponse(ReadResponse(), 1, command);
        return Response { parsedResponse,
            m_dataDecoder->GetIntakeManifoldPressure(parsedResponse.m_data), "kPa" };
        break;
    }
    case S01P0C: {
        std::string command = m_commandRepository->GetEngineRpm();
        SendCommand(command);
        RawResponse parsedResponse = m_dataParser->ParseResponse(ReadResponse(), 2, command);
        return Response { parsedResponse, m_dataDecoder->GetEngineRpm(parsedResponse.m_data),
            "rpm" };
        break;
    }
    case S01P0D: {
        std::string command = m_commandRepository->GetSpeed();
        SendCommand(command);
        RawResponse parsedResponse = m_dataParser->ParseResponse(ReadResponse(), 1, command);
        return Response { parsedResponse, m_dataDecoder->GetSpeed(parsedResponse.m_data), "km/h" };
        break;
    }
    case S01P0E: {
        std::string command = m_commandRepository->GetTimingAdvance();
        SendCommand(command);
        RawResponse parsedResponse = m_dataParser->ParseResponse(ReadResponse(), 1, command);
        return Response { parsedResponse, m_dataDecoder->GetTimingAdvance(parsedResponse.m_data),
            "° before TDC" };
        break;
    }
    case S01P0F: {
        std::string command = m_commandRepository->GetIntakeAirTemperature();
        SendCommand(command);
        RawResponse parsedResponse = m_dataParser->ParseResponse(ReadResponse(), 1, command);
        return Response { parsedResponse,
            m_dataDecoder->GetIntakeAirTemperature(parsedResponse.m_data), "°C" };
        break;
    }
    case S01P10: {
        std::string command = m_commandRepository->GetMafAirFlowRate();
        SendCommand(command);
        RawResponse parsedResponse = m_dataParser->ParseResponse(ReadResponse(), 2, command);
        return Response { parsedResponse, m_dataDecoder->GetMafAirFlowRate(parsedResponse.m_data),
            "g/s" };
        break;
    }
    case S01P11: {
        std::string command = m_commandRepository->GetThrottlePosition();
        SendCommand(command);
        RawResponse parsedResponse = m_dataParser->ParseResponse(ReadResponse(), 1, command);
        return Response { parsedResponse, m_dataDecoder->GetThrottlePosition(parsedResponse.m_data),
            "%" };
        break;
    }
    case S01P12: {
        std::string command = m_commandRepository->GetSecondaryAirStatus();
        SendCommand(command);
        RawResponse parsedResponse = m_dataParser->ParseResponse(ReadResponse(), 1, command);
        return Response { parsedResponse,
            m_dataDecoder->GetSecondaryAirStatus(parsedResponse.m_data) };
        break;
    }
    case S01P13: {
        std::string command = m_commandRepository->GetOxygenSensorsPresent1();
        SendCommand(command);
        RawResponse parsedResponse = m_dataParser->ParseResponse(ReadResponse(), 1, command);
        return Response { parsedResponse,
            m_dataDecoder->GetOxygenSensorsPresent1(parsedResponse.m_data) };
        break;
    }
    case S01P14: {
        std::string command = m_commandRepository->GetOxygenSensorFtV1();
        SendCommand(command);
        RawResponse parsedResponse = m_dataParser->ParseResponse(ReadResponse(), 2, command);
        std::pair<float, float> decodedPair
            = m_dataDecoder->GetOxygenSensorFtV1(parsedResponse.m_data);
        return Response { parsedResponse, decodedPair.first, "V", decodedPair.second, "%" };
        break;
    }
    case S01P15: {
        std::string command = m_commandRepository->GetOxygenSensorFtV2();
        SendCommand(command);
        RawResponse parsedResponse = m_dataParser->ParseResponse(ReadResponse(), 2, command);
        std::pair<float, float> decodedPair
            = m_dataDecoder->GetOxygenSensorFtV2(parsedResponse.m_data);
        return Response { parsedResponse, decodedPair.first, "V", decodedPair.second, "%" };
        break;
    }
    case S01P16: {
        std::string command = m_commandRepository->GetOxygenSensorFtV3();
        SendCommand(command);
        RawResponse parsedResponse = m_dataParser->ParseResponse(ReadResponse(), 2, command);
        std::pair<float, float> decodedPair
            = m_dataDecoder->GetOxygenSensorFtV3(parsedResponse.m_data);
        return Response { parsedResponse, decodedPair.first, "V", decodedPair.second, "%" };
        break;
    }
    case S01P17: {
        std::string command = m_commandRepository->GetOxygenSensorFtV4();
        SendCommand(command);
        RawResponse parsedResponse = m_dataParser->ParseResponse(ReadResponse(), 2, command);
        std::pair<float, float> decodedPair
            = m_dataDecoder->GetOxygenSensorFtV4(parsedResponse.m_data);
        return Response { parsedResponse, decodedPair.first, "V", decodedPair.second, "%" };
        break;
    }
    case S01P18: {
        std::string command = m_commandRepository->GetOxygenSensorFtV5();
        SendCommand(command);
        RawResponse parsedResponse = m_dataParser->ParseResponse(ReadResponse(), 2, command);
        std::pair<float, float> decodedPair
            = m_dataDecoder->GetOxygenSensorFtV5(parsedResponse.m_data);
        return Response { parsedResponse, decodedPair.first, "V", decodedPair.second, "%" };
        break;
    }
    case S01P19: {
        std::string command = m_commandRepository->GetOxygenSensorFtV6();
        SendCommand(command);
        RawResponse parsedResponse = m_dataParser->ParseResponse(ReadResponse(), 2, command);
        std::pair<float, float> decodedPair
            = m_dataDecoder->GetOxygenSensorFtV6(parsedResponse.m_data);
        return Response { parsedResponse, decodedPair.first, "V", decodedPair.second, "%" };
        break;
    }
    case S01P1A: {
        std::string command = m_commandRepository->GetOxygenSensorFtV7();
        SendCommand(command);
        RawResponse parsedResponse = m_dataParser->ParseResponse(ReadResponse(), 2, command);
        std::pair<float, float> decodedPair
            = m_dataDecoder->GetOxygenSensorFtV7(parsedResponse.m_data);
        return Response { parsedResponse, decodedPair.first, "V", decodedPair.second, "%" };
        break;
    }
    case S01P1B: {
        std::string command = m_commandRepository->GetOxygenSensorFtV8();
        SendCommand(command);
        RawResponse parsedResponse = m_dataParser->ParseResponse(ReadResponse(), 2, command);
        std::pair<float, float> decodedPair
            = m_dataDecoder->GetOxygenSensorFtV8(parsedResponse.m_data);
        return Response { parsedResponse, decodedPair.first, "V", decodedPair.second, "%" };
        break;
    }
    case S01P1C: {
        std::string command = m_commandRepository->GetObdStandard();
        SendCommand(command);
        RawResponse parsedResponse = m_dataParser->ParseResponse(ReadResponse(), 1, command);
        return Response { parsedResponse, m_dataDecoder->GetObdStandard(parsedResponse.m_data) };
        break;
    }
    case S01P1D: {
        std::string command = m_commandRepository->GetOxygenSensorsPresent2();
        SendCommand(command);
        RawResponse parsedResponse = m_dataParser->ParseResponse(ReadResponse(), 1, command);
        return Response { parsedResponse,
            m_dataDecoder->GetOxygenSensorsPresent2(parsedResponse.m_data) };
        break;
    }
    case S01P1E: {
        std::string command = m_commandRepository->GetAuxiliaryInputStatus();
        SendCommand(command);
        RawResponse parsedResponse = m_dataParser->ParseResponse(ReadResponse(), 1, command);
        return Response { parsedResponse,
            m_dataDecoder->GetAuxiliaryInputStatus(parsedResponse.m_data) };
        break;
    }
    case S01P1F: {
        std::string command = m_commandRepository->GetRunTime();
        SendCommand(command);
        RawResponse parsedResponse = m_dataParser->ParseResponse(ReadResponse(), 2, command);
        return Response { parsedResponse, m_dataDecoder->GetRunTime(parsedResponse.m_data), "s" };
        break;
    }
    case S01P20: {
        std::string command = m_commandRepository->GetSupportedPIDs2();
        SendCommand(command);
        RawResponse parsedResponse = m_dataParser->ParseResponse(ReadResponse(), 4, command);
        return Response { parsedResponse, m_dataDecoder->GetSupportedPIDs2(parsedResponse.m_data) };
        break;
    }
    case S01P21: {
        std::string command = m_commandRepository->GetDistanceWithMilOn();
        SendCommand(command);
        RawResponse parsedResponse = m_dataParser->ParseResponse(ReadResponse(), 2, command);
        return Response { parsedResponse,
            m_dataDecoder->GetDistanceWithMilOn(parsedResponse.m_data), "km" };
        break;
    }
    case S01P22: {
        std::string command = m_commandRepository->GetFuelRailPressure();
        SendCommand(command);
        RawResponse parsedResponse = m_dataParser->ParseResponse(ReadResponse(), 2, command);
        return Response { parsedResponse, m_dataDecoder->GetFuelRailPressure(parsedResponse.m_data),
            "kPa" };
        break;
    }
    case S01P23: {
        std::string command = m_commandRepository->GetFuelRailGaugePressure();
        SendCommand(command);
        RawResponse parsedResponse = m_dataParser->ParseResponse(ReadResponse(), 2, command);
        return Response { parsedResponse,
            m_dataDecoder->GetFuelRailGaugePressure(parsedResponse.m_data), "kPa" };
        break;
    }
    case S01P24: {
        std::string command = m_commandRepository->GetOxygenSensorEqV1();
        SendCommand(command);
        RawResponse parsedResponse = m_dataParser->ParseResponse(ReadResponse(), 2, command);
        std::pair<float, float> decodedPair
            = m_dataDecoder->GetOxygenSensorEqV1(parsedResponse.m_data);
        return Response { parsedResponse, decodedPair.first, "ratio", decodedPair.second, "V" };
        break;
    }
    case S01P25: {
        std::string command = m_commandRepository->GetOxygenSensorEqV2();
        SendCommand(command);
        RawResponse parsedResponse = m_dataParser->ParseResponse(ReadResponse(), 2, command);
        std::pair<float, float> decodedPair
            = m_dataDecoder->GetOxygenSensorEqV2(parsedResponse.m_data);
        return Response { parsedResponse, decodedPair.first, "ratio", decodedPair.second, "V" };
        break;
    }
    case S01P26: {
        std::string command = m_commandRepository->GetOxygenSensorEqV3();
        SendCommand(command);
        RawResponse parsedResponse = m_dataParser->ParseResponse(ReadResponse(), 2, command);
        std::pair<float, float> decodedPair
            = m_dataDecoder->GetOxygenSensorEqV3(parsedResponse.m_data);
        return Response { parsedResponse, decodedPair.first, "ratio", decodedPair.second, "V" };
        break;
    }
    case S01P27: {
        std::string command = m_commandRepository->GetOxygenSensorEqV4();
        SendCommand(command);
        RawResponse parsedResponse = m_dataParser->ParseResponse(ReadResponse(), 2, command);
        std::pair<float, float> decodedPair
            = m_dataDecoder->GetOxygenSensorEqV4(parsedResponse.m_data);
        return Response { parsedResponse, decodedPair.first, "ratio", decodedPair.second, "V" };
        break;
    }
    case S01P28: {
        std::string command = m_commandRepository->GetOxygenSensorEqV5();
        SendCommand(command);
        RawResponse parsedResponse = m_dataParser->ParseResponse(ReadResponse(), 2, command);
        std::pair<float, float> decodedPair
            = m_dataDecoder->GetOxygenSensorEqV5(parsedResponse.m_data);
        return Response { parsedResponse, decodedPair.first, "ratio", decodedPair.second, "V" };
        break;
    }
    case S01P29: {
        std::string command = m_commandRepository->GetOxygenSensorEqV6();
        SendCommand(command);
        RawResponse parsedResponse = m_dataParser->ParseResponse(ReadResponse(), 2, command);
        std::pair<float, float> decodedPair
            = m_dataDecoder->GetOxygenSensorEqV6(parsedResponse.m_data);
        return Response { parsedResponse, decodedPair.first, "ratio", decodedPair.second, "V" };
        break;
    }
    case S01P2A: {
        std::string command = m_commandRepository->GetOxygenSensorEqV7();
        SendCommand(command);
        RawResponse parsedResponse = m_dataParser->ParseResponse(ReadResponse(), 2, command);
        std::pair<float, float> decodedPair
            = m_dataDecoder->GetOxygenSensorEqV7(parsedResponse.m_data);
        return Response { parsedResponse, decodedPair.first, "ratio", decodedPair.second, "V" };
        break;
    }
    case S01P2B: {
        std::string command = m_commandRepository->GetOxygenSensorEqV8();
        SendCommand(command);
        RawResponse parsedResponse = m_dataParser->ParseResponse(ReadResponse(), 2, command);
        std::pair<float, float> decodedPair
            = m_dataDecoder->GetOxygenSensorEqV8(parsedResponse.m_data);
        return Response { parsedResponse, decodedPair.first, "ratio", decodedPair.second, "V" };
        break;
    }
    case S01P2C: {
        std::string command = m_commandRepository->GetCommandedEgr();
        SendCommand(command);
        RawResponse parsedResponse = m_dataParser->ParseResponse(ReadResponse(), 1, command);
        return Response { parsedResponse, m_dataDecoder->GetCommandedEgr(parsedResponse.m_data),
            "%" };
        break;
    }
    case S01P2D: {
        std::string command = m_commandRepository->GetEgrError();
        SendCommand(command);
        RawResponse parsedResponse = m_dataParser->ParseResponse(ReadResponse(), 1, command);
        return Response { parsedResponse, m_dataDecoder->GetEgrError(parsedResponse.m_data), "%" };
        break;
    }
    case S01P2E: {
        std::string command = m_commandRepository->GetCommandedEvaporativePurge();
        SendCommand(command);
        RawResponse parsedResponse = m_dataParser->ParseResponse(ReadResponse(), 1, command);
        return Response { parsedResponse,
            m_dataDecoder->GetCommandedEvaporativePurge(parsedResponse.m_data), "%" };
        break;
    }
    case S01P2F: {
        std::string command = m_commandRepository->GetFuelTankLevelInput();
        SendCommand(command);
        RawResponse parsedResponse = m_dataParser->ParseResponse(ReadResponse(), 1, command);
        return Response { parsedResponse,
            m_dataDecoder->GetFuelTankLevelInput(parsedResponse.m_data), "%" };
        break;
    }
    case S01P30: {
        std::string command = m_commandRepository->GetWarmupsSinceDtcCleared();
        SendCommand(command);
        RawResponse parsedResponse = m_dataParser->ParseResponse(ReadResponse(), 1, command);
        return Response { parsedResponse,
            m_dataDecoder->GetWarmupsSinceDtcCleared(parsedResponse.m_data), "" };
        break;
    }
    case S01P31: {
        std::string command = m_commandRepository->GetDistanceSinceDtcCleared();
        SendCommand(command);
        RawResponse parsedResponse = m_dataParser->ParseResponse(ReadResponse(), 2, command);
        return Response { parsedResponse,
            m_dataDecoder->GetDistanceSinceDtcCleared(parsedResponse.m_data), "km" };
        break;
    }
    case S01P32: {
        std::string command = m_commandRepository->GetEvapVaporPressure();
        SendCommand(command);
        RawResponse parsedResponse = m_dataParser->ParseResponse(ReadResponse(), 2, command);
        return Response { parsedResponse,
            m_dataDecoder->GetEvapVaporPressure(parsedResponse.m_data), "Pa" };
        break;
    }
    case S01P33: {
        std::string command = m_commandRepository->GetAbsoluteBarometricPressure();
        SendCommand(command);
        RawResponse parsedResponse = m_dataParser->ParseResponse(ReadResponse(), 1, command);
        return Response { parsedResponse,
            m_dataDecoder->GetAbsoluteBarometricPressure(parsedResponse.m_data), "kPa" };
        break;
    }
    case S01P34: {
        std::string command = m_commandRepository->GetOxygenSensorEqC1();
        SendCommand(command);
        RawResponse parsedResponse = m_dataParser->ParseResponse(ReadResponse(), 4, command);
        std::pair<float, float> decodedPair
            = m_dataDecoder->GetOxygenSensorEqC1(parsedResponse.m_data);
        return Response { parsedResponse, decodedPair.first, "ratio", decodedPair.second, "mA" };
        break;
    }
    case S01P35: {
        std::string command = m_commandRepository->GetOxygenSensorEqC2();
        SendCommand(command);
        RawResponse parsedResponse = m_dataParser->ParseResponse(ReadResponse(), 4, command);
        std::pair<float, float> decodedPair
            = m_dataDecoder->GetOxygenSensorEqC2(parsedResponse.m_data);
        return Response { parsedResponse, decodedPair.first, "ratio", decodedPair.second, "mA" };
        break;
    }
    case S01P36: {
        std::string command = m_commandRepository->GetOxygenSensorEqC3();
        SendCommand(command);
        RawResponse parsedResponse = m_dataParser->ParseResponse(ReadResponse(), 4, command);
        std::pair<float, float> decodedPair
            = m_dataDecoder->GetOxygenSensorEqC3(parsedResponse.m_data);
        return Response { parsedResponse, decodedPair.first, "ratio", decodedPair.second, "mA" };
        break;
    }
    case S01P37: {
        std::string command = m_commandRepository->GetOxygenSensorEqC4();
        SendCommand(command);
        RawResponse parsedResponse = m_dataParser->ParseResponse(ReadResponse(), 4, command);
        std::pair<float, float> decodedPair
            = m_dataDecoder->GetOxygenSensorEqC4(parsedResponse.m_data);
        return Response { parsedResponse, decodedPair.first, "ratio", decodedPair.second, "mA" };
        break;
    }
    case S01P38: {
        std::string command = m_commandRepository->GetOxygenSensorEqC5();
        SendCommand(command);
        RawResponse parsedResponse = m_dataParser->ParseResponse(ReadResponse(), 4, command);
        std::pair<float, float> decodedPair
            = m_dataDecoder->GetOxygenSensorEqC5(parsedResponse.m_data);
        return Response { parsedResponse, decodedPair.first, "ratio", decodedPair.second, "mA" };
        break;
    }
    case S01P39: {
        std::string command = m_commandRepository->GetOxygenSensorEqC6();
        SendCommand(command);
        RawResponse parsedResponse = m_dataParser->ParseResponse(ReadResponse(), 4, command);
        std::pair<float, float> decodedPair
            = m_dataDecoder->GetOxygenSensorEqC6(parsedResponse.m_data);
        return Response { parsedResponse, decodedPair.first, "ratio", decodedPair.second, "mA" };
        break;
    }
    case S01P3A: {
        std::string command = m_commandRepository->GetOxygenSensorEqC7();
        SendCommand(command);
        RawResponse parsedResponse = m_dataParser->ParseResponse(ReadResponse(), 4, command);
        std::pair<float, float> decodedPair
            = m_dataDecoder->GetOxygenSensorEqC7(parsedResponse.m_data);
        return Response { parsedResponse, decodedPair.first, "ratio", decodedPair.second, "mA" };
        break;
    }
    case S01P3B: {
        std::string command = m_commandRepository->GetOxygenSensorEqC8();
        SendCommand(command);
        RawResponse parsedResponse = m_dataParser->ParseResponse(ReadResponse(), 4, command);
        std::pair<float, float> decodedPair
            = m_dataDecoder->GetOxygenSensorEqC8(parsedResponse.m_data);
        return Response { parsedResponse, decodedPair.first, "ratio", decodedPair.second, "mA" };
        break;
    }
    case S01P3C: {
        std::string command = m_commandRepository->GetCatalystTemperatureB1S1();
        SendCommand(command);
        RawResponse parsedResponse = m_dataParser->ParseResponse(ReadResponse(), 2, command);
        return Response { parsedResponse,
            m_dataDecoder->GetCatalystTemperatureB1S1(parsedResponse.m_data), "°C" };
        break;
    }
    case S01P3D: {
        std::string command = m_commandRepository->GetCatalystTemperatureB2S1();
        SendCommand(command);
        RawResponse parsedResponse = m_dataParser->ParseResponse(ReadResponse(), 2, command);
        return Response { parsedResponse,
            m_dataDecoder->GetCatalystTemperatureB2S1(parsedResponse.m_data), "°C" };
        break;
    }
    case S01P3E: {
        std::string command = m_commandRepository->GetCatalystTemperatureB1S2();
        SendCommand(command);
        RawResponse parsedResponse = m_dataParser->ParseResponse(ReadResponse(), 2, command);
        return Response { parsedResponse,
            m_dataDecoder->GetCatalystTemperatureB1S2(parsedResponse.m_data), "°C" };
        break;
    }
    case S01P3F: {
        std::string command = m_commandRepository->GetCatalystTemperatureB2S2();
        SendCommand(command);
        RawResponse parsedResponse = m_dataParser->ParseResponse(ReadResponse(), 2, command);
        return Response { parsedResponse,
            m_dataDecoder->GetCatalystTemperatureB2S2(parsedResponse.m_data), "°C" };
        break;
    }
    default:
        return Response {};
    }
}
