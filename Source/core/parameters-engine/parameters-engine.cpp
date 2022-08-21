#include "parameters-engine.h"

bool ParametersEngine::SendCommand(const std::string &command)
{

    int bytesWritten = write(m_ConnectionHandle , command.c_str(), command.length());

    if(!command.ends_with('\r'))
        write(m_ConnectionHandle, "\r", 1);

    if(bytesWritten == -1)
        throw(std::runtime_error(
                std::string("Exception on sending command ")
                + command + " : " + strerror(errno)));
    else
        return true;


}

std::string ParametersEngine::ReadResponse()
{
    char readBuffer[BUFFER_SIZE];
    memset(&readBuffer, '\0', sizeof(readBuffer));
    int dataReadCount = read(m_ConnectionHandle, &readBuffer, BUFFER_SIZE);

    if(dataReadCount < 0)
        throw(std::runtime_error(
                std::string("Exception on reading response : ") + strerror(errno)));

    return std::string(readBuffer);

}

ParametersEngine::ParametersEngine()
{

}

void ParametersEngine::SetSerialDevice(Obd::Device device)
{
    m_SerialDevice = std::move(device);
}

Response ParametersEngine::GetCommandResponse(ObdCommandPid pid)
{
    using enum ObdCommandPid;

    switch (pid) {
    case S01P00:
    {
        std::string command = m_CommandRepository->GetSupportedPIDs1();
        SendCommand(command);
        std::string response = ReadResponse();
        return Response( m_DataObtainer->GetSupportedPIDs1(
                             m_DataFilter->FilterBytes(response, command, 4)
                             ));
        break;
    }
    case S01P01:
    {
        std::string command = m_CommandRepository->GetMonitorStatus();
        SendCommand(command);
        std::string response = ReadResponse();
        return Response(m_DataObtainer->GetMonitorStatus(
                            m_DataFilter->FilterBytes(response, command, 4)
                            ));
        break;
    }
    case S01P02:
    {
        std::string command = m_CommandRepository->GetFreezeDTCs();
        SendCommand(command);
        std::string response = ReadResponse();
        return Response(m_DataObtainer->GetFreezeDTCs(
                            m_DataFilter->FilterBytes(response, command, 2)
                            ),"FreezeDTCs");
        break;
    }
    case S01P03:
    {
        std::string command = m_CommandRepository->GetFuelSystemStatus();
        SendCommand(command);
        std::string response = ReadResponse();
        return Response(m_DataObtainer->GetFuelSystemStatus(
                            m_DataFilter->FilterBytes(response, command, 2)
                            ));
        break;
    }
    case S01P04:
    {
        std::string command = m_CommandRepository->GetEngineLoad();
        SendCommand(command);
        std::string response = ReadResponse();
        return Response(m_DataObtainer->GetEngineLoad(
                            m_DataFilter->FilterBytes(response, command, 1)
                            ),"%");
        break;
    }
    case S01P05:
    {
        std::string command = m_CommandRepository->GetEngineCoolantTemperature();
        SendCommand(command);
        std::string response = ReadResponse();
        return Response( m_DataObtainer->GetEngineCoolantTemperature(
                             m_DataFilter->FilterBytes(response, command, 1)
                             ),"°C");
        break;
    }
    case S01P06:
    {
        std::string command = m_CommandRepository->GetShortTermFuelTrimBank1();
        SendCommand(command);
        std::string response = ReadResponse();
        return Response( m_DataObtainer->GetShortTermFuelTrimBank1(
                             m_DataFilter->FilterBytes(response, command, 1)
                             ),"%");
        break;
    }
    case S01P07:
    {
        std::string command = m_CommandRepository->GetLongTermFuelTrimBank1();
        SendCommand(command);
        std::string response = ReadResponse();
        return Response( m_DataObtainer->GetLongTermFuelTrimBank1(
                             m_DataFilter->FilterBytes(response, command, 1)
                             ),"%");
        break;
    }
    case S01P08:
    {
        std::string command = m_CommandRepository->GetShortTermFuelTrimBank2();
        SendCommand(command);
        std::string response = ReadResponse();
        return Response( m_DataObtainer->GetShortTermFuelTrimBank2(
                             m_DataFilter->FilterBytes(response, command, 1)
                             ),"%");
        break;
    }
    case S01P09:
    {
        std::string command = m_CommandRepository->GetLongTermFuelTrimBank2();
        SendCommand(command);
        std::string response = ReadResponse();
        return Response( m_DataObtainer->GetLongTermFuelTrimBank2(
                             m_DataFilter->FilterBytes(response, command, 1)
                             ),"%");
        break;
    }
    case S01P0A:
    {
        std::string command = m_CommandRepository->GetFuelPressure();
        SendCommand(command);
        std::string response = ReadResponse();
        return Response( m_DataObtainer->GetFuelPressure(
                             m_DataFilter->FilterBytes(response, command, 1)
                             ),"kPa");
        break;
    }
    case S01P0B:
    {
        std::string command = m_CommandRepository->GetIntakeManifoldPressure();
        SendCommand(command);
        std::string response = ReadResponse();
        return Response( m_DataObtainer->GetIntakeManifoldPressure(
                             m_DataFilter->FilterBytes(response, command, 1)
                             ),"kPa");
        break;
    }
    case S01P0C:
    {
        std::string command = m_CommandRepository->GetEngineRpm();
        SendCommand(command);
        std::string response = ReadResponse();
        return Response( m_DataObtainer->GetEngineRpm(
                             m_DataFilter->FilterBytes(response, command, 2)
                             ),"rpm");
        break;
    }
    case S01P0D:
    {
        std::string command = m_CommandRepository->GetSpeed();
        SendCommand(command);
        std::string response = ReadResponse();
        return Response( m_DataObtainer->GetSpeed(
                             m_DataFilter->FilterBytes(response, command, 1)
                             ),"km/h");
        break;
    }
    case S01P0E:
    {
        std::string command = m_CommandRepository->GetTimingAdvance();
        SendCommand(command);
        std::string response = ReadResponse();
        return Response( m_DataObtainer->GetTimingAdvance(
                             m_DataFilter->FilterBytes(response, command, 1)
                             ),"° before TDC");
        break;
    }
    case S01P0F:
    {
        std::string command = m_CommandRepository->GetIntakeAirTemperature();
        SendCommand(command);
        std::string response = ReadResponse();
        return Response( m_DataObtainer->GetIntakeAirTemperature(
                             m_DataFilter->FilterBytes(response, command, 1)
                             ),"°C");
        break;
    }
    case S01P10:
    {
        std::string command = m_CommandRepository->GetMafAirFlowRate();
        SendCommand(command);
        std::string response = ReadResponse();
        return Response( m_DataObtainer->GetMafAirFlowRate(
                             m_DataFilter->FilterBytes(response, command, 2)
                             ),"g/s");
        break;
    }
    case S01P11:
    {
        std::string command = m_CommandRepository->GetThrottlePosition();
        SendCommand(command);
        std::string response = ReadResponse();
        return Response( m_DataObtainer->GetThrottlePosition(
                             m_DataFilter->FilterBytes(response, command, 1)
                             ),"%");
        break;
    }
    case S01P12:
    {
        std::string command = m_CommandRepository->GetSecondaryAirStatus();
        SendCommand(command);
        std::string response = ReadResponse();
        return Response( m_DataObtainer->GetSecondaryAirStatus(
                             m_DataFilter->FilterBytes(response, command, 1)
                             ));
        break;
    }
    case S01P13:
    {
        std::string command = m_CommandRepository->GetOxygenSensorsPresent1();
        SendCommand(command);
        std::string response = ReadResponse();
        return Response( m_DataObtainer->GetSensorsPresent1(
                             m_DataFilter->FilterBytes(response, command, 1)
                             ));
        break;
    }
    case S01P14:
    {
        std::string command = m_CommandRepository->GetOxygenSensorFtV1();
        SendCommand(command);
        std::string response = ReadResponse();
        std::pair<float, float> decodedPair = m_DataObtainer->GetOxygenSensorFtV1(
                    m_DataFilter->FilterBytes(response, command, 2));
        return Response( decodedPair.first,"V",decodedPair.second,"%");
        break;
    }
    case S01P15:
    {
        std::string command = m_CommandRepository->GetOxygenSensorFtV2();
        SendCommand(command);
        std::string response = ReadResponse();
        std::pair<float, float> decodedPair = m_DataObtainer->GetOxygenSensorFtV2(
                    m_DataFilter->FilterBytes(response, command, 2));
        return Response( decodedPair.first,"V",decodedPair.second,"%");
        break;
    }
    case S01P16:
    {
        std::string command = m_CommandRepository->GetOxygenSensorFtV3();
        SendCommand(command);
        std::string response = ReadResponse();
        std::pair<float, float> decodedPair = m_DataObtainer->GetOxygenSensorFtV3(
                    m_DataFilter->FilterBytes(response, command, 2));
        return Response( decodedPair.first,"V",decodedPair.second,"%");
        break;
    }
    case S01P17:
    {
        std::string command = m_CommandRepository->GetOxygenSensorFtV4();
        SendCommand(command);
        std::string response = ReadResponse();
        std::pair<float, float> decodedPair = m_DataObtainer->GetOxygenSensorFtV4(
                    m_DataFilter->FilterBytes(response, command, 2));
        return Response( decodedPair.first,"V",decodedPair.second,"%");
        break;
    }
    case S01P18:
    {
        std::string command = m_CommandRepository->GetOxygenSensorFtV5();
        SendCommand(command);
        std::string response = ReadResponse();
        std::pair<float, float> decodedPair = m_DataObtainer->GetOxygenSensorFtV5(
                    m_DataFilter->FilterBytes(response, command, 2));
        return Response( decodedPair.first,"V",decodedPair.second,"%");
        break;
    }
    case S01P19:
    {
        std::string command = m_CommandRepository->GetOxygenSensorFtV6();
        SendCommand(command);
        std::string response = ReadResponse();
        std::pair<float, float> decodedPair = m_DataObtainer->GetOxygenSensorFtV6(
                    m_DataFilter->FilterBytes(response, command, 2));
        return Response( decodedPair.first,"V",decodedPair.second,"%");
        break;
    }
    case S01P1A:
    {
        std::string command = m_CommandRepository->GetOxygenSensorFtV7();
        SendCommand(command);
        std::string response = ReadResponse();
        std::pair<float, float> decodedPair = m_DataObtainer->GetOxygenSensorFtV7(
                    m_DataFilter->FilterBytes(response, command, 2));
        return Response( decodedPair.first,"V",decodedPair.second,"%");
        break;
    }
    case S01P1B:
    {
        std::string command = m_CommandRepository->GetOxygenSensorFtV8();
        SendCommand(command);
        std::string response = ReadResponse();
        std::pair<float, float> decodedPair = m_DataObtainer->GetOxygenSensorFtV8(
                    m_DataFilter->FilterBytes(response, command, 2));
        return Response( decodedPair.first,"V",decodedPair.second,"%");
        break;
    }
    case S01P1C:
    {
        std::string command = m_CommandRepository->GetObdStandard();
        SendCommand(command);
        std::string response = ReadResponse();
        return Response( m_DataObtainer->GetObdStandard(
                             m_DataFilter->FilterBytes(response, command, 1)
                             ));
        break;
    }
    case S01P1D:
    {
        std::string command = m_CommandRepository->GetOxygenSensorsPresent2();
        SendCommand(command);
        std::string response = ReadResponse();
        return Response( m_DataObtainer->GetOxygenSensorsPresent2(
                             m_DataFilter->FilterBytes(response, command, 1)
                             ));
        break;
    }
    case S01P1E:
    {
        std::string command = m_CommandRepository->GetAuxiliaryInputStatus();
        SendCommand(command);
        std::string response = ReadResponse();
        return Response( m_DataObtainer->GetAuxiliaryInputStatus(
                             m_DataFilter->FilterBytes(response, command, 1)
                             ));
        break;
    }
    case S01P1F:
    {
        std::string command = m_CommandRepository->GetRunTime();
        SendCommand(command);
        std::string response = ReadResponse();
        return Response( m_DataObtainer->GetRunTime(
                             m_DataFilter->FilterBytes(response, command, 2)
                             ),"s");
        break;
    }
    case S01P20:
    {
        std::string command = m_CommandRepository->GetSupportedPIDs2();
        SendCommand(command);
        std::string response = ReadResponse();
        return Response( m_DataObtainer->GetSupportedPIDs2(
                             m_DataFilter->FilterBytes(response, command, 4)
                             ));
        break;
    }
    case S01P21:
    {
        std::string command = m_CommandRepository->GetDistanceWithMilOn();
        SendCommand(command);
        std::string response = ReadResponse();
        return Response( m_DataObtainer->GetDistanceWithMilOn(
                             m_DataFilter->FilterBytes(response, command, 2)
                             ),"km");
        break;
    }
    case S01P22:
    {
        std::string command = m_CommandRepository->GetFuelRailPressure();
        SendCommand(command);
        std::string response = ReadResponse();
        return Response( m_DataObtainer->GetFuelRailPressure(
                             m_DataFilter->FilterBytes(response, command, 2)
                             ),"kPa");
        break;
    }
    case S01P23:
    {
        std::string command = m_CommandRepository->GetFuelRailGaugePressure();
        SendCommand(command);
        std::string response = ReadResponse();
        return Response( m_DataObtainer->GetFuelRailGaugePressure(
                             m_DataFilter->FilterBytes(response, command, 2)
                             ),"kPa");
        break;
    }
    case S01P24:
    {
        std::string command = m_CommandRepository->GetOxygenSensorEqV1();
        SendCommand(command);
        std::string response = ReadResponse();
        std::pair<float, float> decodedPair = m_DataObtainer->GetOxygenSensorEqV1(
                    m_DataFilter->FilterBytes(response, command, 2));
        return Response( decodedPair.first,"ratio",decodedPair.second,"V");
        break;
    }
    case S01P25:
    {
        std::string command = m_CommandRepository->GetOxygenSensorEqV2();
        SendCommand(command);
        std::string response = ReadResponse();
        std::pair<float, float> decodedPair = m_DataObtainer->GetOxygenSensorEqV2(
                    m_DataFilter->FilterBytes(response, command, 2));
        return Response( decodedPair.first,"ratio",decodedPair.second,"V");
        break;
    }
    case S01P26:
    {
        std::string command = m_CommandRepository->GetOxygenSensorEqV3();
        SendCommand(command);
        std::string response = ReadResponse();
        std::pair<float, float> decodedPair = m_DataObtainer->GetOxygenSensorEqV3(
                    m_DataFilter->FilterBytes(response, command, 2));
        return Response( decodedPair.first,"ratio",decodedPair.second,"V");
        break;
    }
    case S01P27:
    {
        std::string command = m_CommandRepository->GetOxygenSensorEqV4();
        SendCommand(command);
        std::string response = ReadResponse();
        std::pair<float, float> decodedPair = m_DataObtainer->GetOxygenSensorEqV4(
                    m_DataFilter->FilterBytes(response, command, 2));
        return Response( decodedPair.first,"ratio",decodedPair.second,"V");
        break;
    }
    case S01P28:
    {
        std::string command = m_CommandRepository->GetOxygenSensorEqV5();
        SendCommand(command);
        std::string response = ReadResponse();
        std::pair<float, float> decodedPair = m_DataObtainer->GetOxygenSensorEqV5(
                    m_DataFilter->FilterBytes(response, command, 2));
        return Response( decodedPair.first,"ratio",decodedPair.second,"V");
        break;
    }
    case S01P29:
    {
        std::string command = m_CommandRepository->GetOxygenSensorEqV6();
        SendCommand(command);
        std::string response = ReadResponse();
        std::pair<float, float> decodedPair = m_DataObtainer->GetOxygenSensorEqV6(
                    m_DataFilter->FilterBytes(response, command, 2));
        return Response( decodedPair.first,"ratio",decodedPair.second,"V");
        break;
    }
    case S01P2A:
    {
        std::string command = m_CommandRepository->GetOxygenSensorEqV7();
        SendCommand(command);
        std::string response = ReadResponse();
        std::pair<float, float> decodedPair = m_DataObtainer->GetOxygenSensorEqV7(
                    m_DataFilter->FilterBytes(response, command, 2));
        return Response( decodedPair.first,"ratio",decodedPair.second,"V");
        break;
    }
    case S01P2B:
    {
        std::string command = m_CommandRepository->GetOxygenSensorEqV8();
        SendCommand(command);
        std::string response = ReadResponse();
        std::pair<float, float> decodedPair = m_DataObtainer->GetOxygenSensorEqV8(
                    m_DataFilter->FilterBytes(response, command, 2));
        return Response( decodedPair.first,"ratio",decodedPair.second,"V");
        break;
    }
    case S01P2C:
    {
        std::string command = m_CommandRepository->GetCommandedEgr();
        SendCommand(command);
        std::string response = ReadResponse();
        return Response( m_DataObtainer->GetCommandedEgr(
                             m_DataFilter->FilterBytes(response, command, 1)
                             ),"%");
        break;
    }
    case S01P2D:
    {
        std::string command = m_CommandRepository->GetEgrError();
        SendCommand(command);
        std::string response = ReadResponse();
        return Response( m_DataObtainer->GetEgrError(
                             m_DataFilter->FilterBytes(response, command, 1)
                             ),"%");
        break;
    }
    case S01P2E:
    {
        std::string command = m_CommandRepository->GetCommandedEvaporativePurge();
        SendCommand(command);
        std::string response = ReadResponse();
        return Response( m_DataObtainer->GetCommandedEvaporativePurge(
                             m_DataFilter->FilterBytes(response, command, 1)
                             ),"%");
        break;
    }
    case S01P2F:
    {
        std::string command = m_CommandRepository->GetFuelTankLevelInput();
        SendCommand(command);
        std::string response = ReadResponse();
        return Response( m_DataObtainer->GetFuelTankLevelInput(
                             m_DataFilter->FilterBytes(response, command, 1)
                             ),"%");
        break;
    }
    case S01P30:
    {
        std::string command = m_CommandRepository->GetWarmupsSinceDtcCleared();
        SendCommand(command);
        std::string response = ReadResponse();
        return Response( m_DataObtainer->GetWarmupsSinceDtcCleared(
                             m_DataFilter->FilterBytes(response, command, 1)
                             ),"");
        break;
    }
    case S01P31:
    {
        std::string command = m_CommandRepository->GetDistanceSinceDtcCleared();
        SendCommand(command);
        std::string response = ReadResponse();
        return Response( m_DataObtainer->GetDistanceSinceDtcCleared(
                             m_DataFilter->FilterBytes(response, command, 2)
                             ),"km");
        break;
    }
    case S01P32:
    {
        std::string command = m_CommandRepository->GetEvapVaporPressure();
        SendCommand(command);
        std::string response = ReadResponse();
        return Response( m_DataObtainer->GetEvapVaporPressure(
                             m_DataFilter->FilterBytes(response, command, 2)
                             ),"Pa");
        break;
    }
    case S01P33:
    {
        std::string command = m_CommandRepository->GetAbsoluteBarometricPressure();
        SendCommand(command);
        std::string response = ReadResponse();
        return Response( m_DataObtainer->GetAbsoluteBarometricPressure(
                             m_DataFilter->FilterBytes(response, command, 1)
                             ),"kPa");
        break;
    }
    case S01P34:
    {
        std::string command = m_CommandRepository->GetOxygenSensorEqC1();
        SendCommand(command);
        std::string response = ReadResponse();
        std::pair<float, float> decodedPair = m_DataObtainer->GetOxygenSensorEqC1(
                    m_DataFilter->FilterBytes(response, command, 4));
        return Response( decodedPair.first,"ratio",decodedPair.second,"mA");
        break;
    }
    case S01P35:
    {
        std::string command = m_CommandRepository->GetOxygenSensorEqC2();
        SendCommand(command);
        std::string response = ReadResponse();
        std::pair<float, float> decodedPair = m_DataObtainer->GetOxygenSensorEqC2(
                    m_DataFilter->FilterBytes(response, command, 4));
        return Response( decodedPair.first,"ratio",decodedPair.second,"mA");
        break;
    }
    case S01P36:
    {
        std::string command = m_CommandRepository->GetOxygenSensorEqC3();
        SendCommand(command);
        std::string response = ReadResponse();
        std::pair<float, float> decodedPair = m_DataObtainer->GetOxygenSensorEqC3(
                    m_DataFilter->FilterBytes(response, command, 4));
        return Response( decodedPair.first,"ratio",decodedPair.second,"mA");
        break;
    }
    case S01P37:
    {
        std::string command = m_CommandRepository->GetOxygenSensorEqC4();
        SendCommand(command);
        std::string response = ReadResponse();
        std::pair<float, float> decodedPair = m_DataObtainer->GetOxygenSensorEqC4(
                    m_DataFilter->FilterBytes(response, command, 4));
        return Response( decodedPair.first,"ratio",decodedPair.second,"mA");
        break;
    }
    case S01P38:
    {
        std::string command = m_CommandRepository->GetOxygenSensorEqC5();
        SendCommand(command);
        std::string response = ReadResponse();
        std::pair<float, float> decodedPair = m_DataObtainer->GetOxygenSensorEqC5(
                    m_DataFilter->FilterBytes(response, command, 4));
        return Response( decodedPair.first,"ratio",decodedPair.second,"mA");
        break;
    }
    case S01P39:
    {
        std::string command = m_CommandRepository->GetOxygenSensorEqC6();
        SendCommand(command);
        std::string response = ReadResponse();
        std::pair<float, float> decodedPair = m_DataObtainer->GetOxygenSensorEqC6(
                    m_DataFilter->FilterBytes(response, command, 4));
        return Response( decodedPair.first,"ratio",decodedPair.second,"mA");
        break;
    }
    case S01P3A:
    {
        std::string command = m_CommandRepository->GetOxygenSensorEqC7();
        SendCommand(command);
        std::string response = ReadResponse();
        std::pair<float, float> decodedPair = m_DataObtainer->GetOxygenSensorEqC7(
                    m_DataFilter->FilterBytes(response, command, 4));
        return Response( decodedPair.first,"ratio",decodedPair.second,"mA");
        break;
    }
    case S01P3B:
    {
        std::string command = m_CommandRepository->GetOxygenSensorEqC8();
        SendCommand(command);
        std::string response = ReadResponse();
        std::pair<float, float> decodedPair = m_DataObtainer->GetOxygenSensorEqC8(
                    m_DataFilter->FilterBytes(response, command, 4));
        return Response( decodedPair.first,"ratio",decodedPair.second,"mA");
        break;
    }
    case S01P3C:
    {
        std::string command = m_CommandRepository->GetCatalystTemperatureB1S1();
        SendCommand(command);
        std::string response = ReadResponse();
        return Response( m_DataObtainer->GetCatalystTemperatureB1S1(
                             m_DataFilter->FilterBytes(response, command, 2)
                             ),"°C");
        break;
    }
    case S01P3D:
    {
        std::string command = m_CommandRepository->GetCatalystTemperatureB2S1();
        SendCommand(command);
        std::string response = ReadResponse();
        return Response( m_DataObtainer->GetCatalystTemperatureB2S1(
                             m_DataFilter->FilterBytes(response, command, 2)
                             ),"°C");
        break;
    }
    case S01P3E:
    {
        std::string command = m_CommandRepository->GetCatalystTemperatureB1S2();
        SendCommand(command);
        std::string response = ReadResponse();
        return Response( m_DataObtainer->GetCatalystTemperatureB1S2(
                             m_DataFilter->FilterBytes(response, command, 2)
                             ),"°C");
        break;
    }
    case S01P3F:
    {
        std::string command = m_CommandRepository->GetCatalystTemperatureB2S2();
        SendCommand(command);
        std::string response = ReadResponse();
        return Response( m_DataObtainer->GetCatalystTemperatureB2S2(
                             m_DataFilter->FilterBytes(response, command, 2)
                             ),"°C");
        break;
    }
    default:
        return Response();
    }
}
