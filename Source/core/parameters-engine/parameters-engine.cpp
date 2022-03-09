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

std::variant<
std::optional<float>,
std::optional<std::pair<std::optional<float>,std::optional<float>>>,
std::optional<std::bitset<32>>,
std::optional<std::string>
> ParametersEngine::GetCommandResponse(ObdCommandPid pid)
{
    using enum ObdCommandPid;

    switch (pid) {
    case S01P00:
    {
        std::string command = m_CommandRepository->GetSupportedPIDs1()+'\r';
        SendCommand(command);
        std::string response = ReadResponse();
        return m_DataObtainer->GetSupportedPIDs1(
                    m_DataFilter->FilterBytes(response, command, 4)
                    );
    }
    case S01P01:
    {
        std::string command = m_CommandRepository->GetMonitorStatus()+'\r';
        SendCommand(command);
        std::string response = ReadResponse();
        return m_DataObtainer->GetMonitorStatus(
                    m_DataFilter->FilterBytes(response, command, 4)
                    );
    }
    case S01P02:
    {
        std::string command = m_CommandRepository->GetFreezeDTCs()+'\r';
        SendCommand(command);
        std::string response = ReadResponse();
        return m_DataObtainer->GetFreezeDTCs(
                    m_DataFilter->FilterBytes(response, command, 2)
                    );
    }
    case S01P03:
    {
        std::string command = m_CommandRepository->GetFuelSystemStatus()+'\r';
        SendCommand(command);
        std::string response = ReadResponse();
        return m_DataObtainer->GetFuelSystemStatus(
                    m_DataFilter->FilterBytes(response, command, 2)
                    );
    }
    case S01P04:
    {
        std::string command = m_CommandRepository->GetEngineLoad()+'\r';
        SendCommand(command);
        std::string response = ReadResponse();
        return m_DataObtainer->GetEngineLoad(
                    m_DataFilter->FilterBytes(response, command, 1)
                    );
    }
    case S01P05:
    {
        std::string command = m_CommandRepository->GetEngineCoolantTemperature()+'\r';
        SendCommand(command);
        std::string response = ReadResponse();
        return m_DataObtainer->GetEngineCoolantTemperature(
                    m_DataFilter->FilterBytes(response, command, 1)
                    );
    }
    case S01P06:
    {
        std::string command = m_CommandRepository->GetShortTermFuelTrimBank1()+'\r';
        SendCommand(command);
        std::string response = ReadResponse();
        return m_DataObtainer->GetShortTermFuelTrimBank1(
                    m_DataFilter->FilterBytes(response, command, 1)
                    );
    }
    case S01P07:
    {
        std::string command = m_CommandRepository->GetLongTermFuelTrimBank1()+'\r';
        SendCommand(command);
        std::string response = ReadResponse();
        return m_DataObtainer->GetLongTermFuelTrimBank1(
                    m_DataFilter->FilterBytes(response, command, 1)
                    );
    }
    case S01P08:
    {
        std::string command = m_CommandRepository->GetShortTermFuelTrimBank2()+'\r';
        SendCommand(command);
        std::string response = ReadResponse();
        return m_DataObtainer->GetShortTermFuelTrimBank2(
                    m_DataFilter->FilterBytes(response, command, 1)
                    );
    }
    case S01P09:
    {
        std::string command = m_CommandRepository->GetLongTermFuelTrimBank2()+'\r';
        SendCommand(command);
        std::string response = ReadResponse();
        return m_DataObtainer->GetLongTermFuelTrimBank2(
                    m_DataFilter->FilterBytes(response, command, 1)
                    );
    }
    case S01P0A:
    {
        std::string command = m_CommandRepository->GetFuelPressure()+'\r';
        SendCommand(command);
        std::string response = ReadResponse();
        return m_DataObtainer->GetFuelPressure(
                    m_DataFilter->FilterBytes(response, command, 1)
                    );
    }
    case S01P0B:
    {
        std::string command = m_CommandRepository->GetIntakeManifoldPressure()+'\r';
        SendCommand(command);
        std::string response = ReadResponse();
        return m_DataObtainer->GetIntakeManifoldPressure(
                    m_DataFilter->FilterBytes(response, command, 1)
                    );
    }
    case S01P0C:
    {
        std::string command = m_CommandRepository->GetEngineRpm()+'\r';
        SendCommand(command);
        std::string response = ReadResponse();
        return m_DataObtainer->GetEngineRpm(
                    m_DataFilter->FilterBytes(response, command, 2)
                    );
    }
    case S01P0D:
    {
        std::string command = m_CommandRepository->GetSpeed()+'\r';
        SendCommand(command);
        std::string response = ReadResponse();
        return m_DataObtainer->GetSpeed(
                    m_DataFilter->FilterBytes(response, command, 1)
                    );
    }
    case S01P0E:
    {
        std::string command = m_CommandRepository->GetTimingAdvance()+'\r';
        SendCommand(command);
        std::string response = ReadResponse();
        return m_DataObtainer->GetTimingAdvance(
                    m_DataFilter->FilterBytes(response, command, 1)
                    );
    }
    case S01P0F:
    {
        std::string command = m_CommandRepository->GetIntakeAirTemperature()+'\r';
        SendCommand(command);
        std::string response = ReadResponse();
        return m_DataObtainer->GetIntakeAirTemperature(
                    m_DataFilter->FilterBytes(response, command, 1)
                    );
    }
    case S01P10:
    {
        std::string command = m_CommandRepository->GetMafAirFlowRate()+'\r';
        SendCommand(command);
        std::string response = ReadResponse();
        return m_DataObtainer->GetMafAirFlowRate(
                    m_DataFilter->FilterBytes(response, command, 2)
                    );
    }
    case S01P11:
    {
        std::string command = m_CommandRepository->GetThrottlePosition()+'\r';
        SendCommand(command);
        std::string response = ReadResponse();
        return m_DataObtainer->GetThrottlePosition(
                    m_DataFilter->FilterBytes(response, command, 1)
                    );
    }
    case S01P12:
    {
        std::string command = m_CommandRepository->GetSecondaryAirStatus()+'\r';
        SendCommand(command);
        std::string response = ReadResponse();
        return m_DataObtainer->GetSecondaryAirStatus(
                    m_DataFilter->FilterBytes(response, command, 1)
                    );
    }
    case S01P13:
    {
        std::string command = m_CommandRepository->GetOxygenSensorsPresent1()+'\r';
        SendCommand(command);
        std::string response = ReadResponse();
        return m_DataObtainer->GetSensorsPresent1(
                    m_DataFilter->FilterBytes(response, command, 1)
                    );
    }
    case S01P14:
    {
        std::string command = m_CommandRepository->GetOxygenSensorFtV1()+'\r';
        SendCommand(command);
        std::string response = ReadResponse();
        return m_DataObtainer->GetOxygenSensorFtV1(
                    m_DataFilter->FilterBytes(response, command, 2)
                    );
    }
    case S01P15:
    {
        std::string command = m_CommandRepository->GetOxygenSensorFtV2()+'\r';
        SendCommand(command);
        std::string response = ReadResponse();
        return m_DataObtainer->GetOxygenSensorFtV2(
                    m_DataFilter->FilterBytes(response, command, 2)
                    );
    }
    case S01P16:
    {
        std::string command = m_CommandRepository->GetOxygenSensorFtV3()+'\r';
        SendCommand(command);
        std::string response = ReadResponse();
        return m_DataObtainer->GetOxygenSensorFtV3(
                    m_DataFilter->FilterBytes(response, command, 2)
                    );
    }
    case S01P17:
    {
        std::string command = m_CommandRepository->GetOxygenSensorFtV4()+'\r';
        SendCommand(command);
        std::string response = ReadResponse();
        return m_DataObtainer->GetOxygenSensorFtV4(
                    m_DataFilter->FilterBytes(response, command, 2)
                    );
    }
    case S01P18:
    {
        std::string command = m_CommandRepository->GetOxygenSensorFtV5()+'\r';
        SendCommand(command);
        std::string response = ReadResponse();
        return m_DataObtainer->GetOxygenSensorFtV5(
                    m_DataFilter->FilterBytes(response, command, 2)
                    );
    }
    case S01P19:
    {
        std::string command = m_CommandRepository->GetOxygenSensorFtV6()+'\r';
        SendCommand(command);
        std::string response = ReadResponse();
        return m_DataObtainer->GetOxygenSensorFtV6(
                    m_DataFilter->FilterBytes(response, command, 2)
                    );
    }
    case S01P1A:
    {
        std::string command = m_CommandRepository->GetOxygenSensorFtV7()+'\r';
        SendCommand(command);
        std::string response = ReadResponse();
        return m_DataObtainer->GetOxygenSensorFtV7(
                    m_DataFilter->FilterBytes(response, command, 2)
                    );
    }
    case S01P1B:
    {
        std::string command = m_CommandRepository->GetOxygenSensorFtV8()+'\r';
        SendCommand(command);
        std::string response = ReadResponse();
        return m_DataObtainer->GetOxygenSensorFtV8(
                    m_DataFilter->FilterBytes(response, command, 2)
                    );
    }
    case S01P1C:
    {
        std::string command = m_CommandRepository->GetObdStandard()+'\r';
        SendCommand(command);
        std::string response = ReadResponse();
        return m_DataObtainer->GetObdStandard(
                    m_DataFilter->FilterBytes(response, command, 1)
                    );
    }
    case S01P1D:
    {
        std::string command = m_CommandRepository->GetOxygenSensorsPresent2()+'\r';
        SendCommand(command);
        std::string response = ReadResponse();
        return m_DataObtainer->GetOxygenSensorsPresent2(
                    m_DataFilter->FilterBytes(response, command, 1)
                    );
    }
    case S01P1E:
    {
        std::string command = m_CommandRepository->GetAuxiliaryInputStatus()+'\r';
        SendCommand(command);
        std::string response = ReadResponse();
        return m_DataObtainer->GetAuxiliaryInputStatus(
                    m_DataFilter->FilterBytes(response, command, 1)
                    );
    }
    case S01P1F:
    {
        std::string command = m_CommandRepository->GetRunTime()+'\r';
        SendCommand(command);
        std::string response = ReadResponse();
        return m_DataObtainer->GetRunTime(
                    m_DataFilter->FilterBytes(response, command, 2)
                    );
    }
    case S01P20:
    {
        std::string command = m_CommandRepository->GetSupportedPIDs2()+'\r';
        SendCommand(command);
        std::string response = ReadResponse();
        return m_DataObtainer->GetSupportedPIDs2(
                    m_DataFilter->FilterBytes(response, command, 4)
                    );
    }
    case S01P21:
    {
        std::string command = m_CommandRepository->GetDistanceWithMilOn()+'\r';
        SendCommand(command);
        std::string response = ReadResponse();
        return m_DataObtainer->GetDistanceWithMilOn(
                    m_DataFilter->FilterBytes(response, command, 2)
                    );
    }
    case S01P22:
    {
        std::string command = m_CommandRepository->GetFuelRailPressure()+'\r';
        SendCommand(command);
        std::string response = ReadResponse();
        return m_DataObtainer->GetFuelRailPressure(
                    m_DataFilter->FilterBytes(response, command, 2)
                    );
    }
    case S01P23:
    {
        std::string command = m_CommandRepository->GetFuelRailGaugePressure()+'\r';
        SendCommand(command);
        std::string response = ReadResponse();
        return m_DataObtainer->GetFuelRailGaugePressure(
                    m_DataFilter->FilterBytes(response, command, 2)
                    );
    }
    case S01P24:
    {
        std::string command = m_CommandRepository->GetOxygenSensorEqV1()+'\r';
        SendCommand(command);
        std::string response = ReadResponse();
        return m_DataObtainer->GetOxygenSensorEqV1(
                    m_DataFilter->FilterBytes(response, command, 4)
                    );
    }
    case S01P25:
    {
        std::string command = m_CommandRepository->GetOxygenSensorEqV2()+'\r';
        SendCommand(command);
        std::string response = ReadResponse();
        return m_DataObtainer->GetOxygenSensorEqV2(
                    m_DataFilter->FilterBytes(response, command, 4)
                    );
    }
    case S01P26:
    {
        std::string command = m_CommandRepository->GetOxygenSensorEqV3()+'\r';
        SendCommand(command);
        std::string response = ReadResponse();
        return m_DataObtainer->GetOxygenSensorEqV3(
                    m_DataFilter->FilterBytes(response, command, 4)
                    );
    }
    case S01P27:
    {
        std::string command = m_CommandRepository->GetOxygenSensorEqV4()+'\r';
        SendCommand(command);
        std::string response = ReadResponse();
        return m_DataObtainer->GetOxygenSensorEqV4(
                    m_DataFilter->FilterBytes(response, command, 4)
                    );
    }
    case S01P28:
    {
        std::string command = m_CommandRepository->GetOxygenSensorEqV5()+'\r';
        SendCommand(command);
        std::string response = ReadResponse();
        return m_DataObtainer->GetOxygenSensorEqV5(
                    m_DataFilter->FilterBytes(response, command, 4)
                    );
    }
    case S01P29:
    {
        std::string command = m_CommandRepository->GetOxygenSensorEqV6()+'\r';
        SendCommand(command);
        std::string response = ReadResponse();
        return m_DataObtainer->GetOxygenSensorEqV6(
                    m_DataFilter->FilterBytes(response, command, 4)
                    );
    }
    case S01P2A:
    {
        std::string command = m_CommandRepository->GetOxygenSensorEqV7()+'\r';
        SendCommand(command);
        std::string response = ReadResponse();
        return m_DataObtainer->GetOxygenSensorEqV7(
                    m_DataFilter->FilterBytes(response, command, 4)
                    );
    }
    case S01P2B:
    {
        std::string command = m_CommandRepository->GetOxygenSensorEqV8()+'\r';
        SendCommand(command);
        std::string response = ReadResponse();
        return m_DataObtainer->GetOxygenSensorEqV8(
                    m_DataFilter->FilterBytes(response, command, 4)
                    );
    }
    case S01P2C:
    {
        std::string command = m_CommandRepository->GetCommandedEgr()+'\r';
        SendCommand(command);
        std::string response = ReadResponse();
        return m_DataObtainer->GetCommandedEgr(
                    m_DataFilter->FilterBytes(response, command, 1)
                    );
    }
    case S01P2D:
    {
        std::string command = m_CommandRepository->GetEgrError()+'\r';
        SendCommand(command);
        std::string response = ReadResponse();
        return m_DataObtainer->GetEgrError(
                    m_DataFilter->FilterBytes(response, command, 1)
                    );
    }
    case S01P2E:
    {
        std::string command = m_CommandRepository->GetCommandedEvaporativePurge()+'\r';
        SendCommand(command);
        std::string response = ReadResponse();
        return m_DataObtainer->GetCommandedEvaporativePurge(
                    m_DataFilter->FilterBytes(response, command, 1)
                    );
    }
    case S01P2F:
    {
        std::string command = m_CommandRepository->GetFuelTankLevelInput()+'\r';
        SendCommand(command);
        std::string response = ReadResponse();
        return m_DataObtainer->GetFuelTankLevelInput(
                    m_DataFilter->FilterBytes(response, command, 1)
                    );
    }
    case S01P30:
    {
        std::string command = m_CommandRepository->GetWarmupsSinceDtcCleared()+'\r';
        SendCommand(command);
        std::string response = ReadResponse();
        return m_DataObtainer->GetWarmupsSinceDtcCleared(
                    m_DataFilter->FilterBytes(response, command, 1)
                    );
    }
    case S01P31:
    {
        std::string command = m_CommandRepository->GetDistanceSinceDtcCleared()+'\r';
        SendCommand(command);
        std::string response = ReadResponse();
        return m_DataObtainer->GetDistanceSinceDtcCleared(
                    m_DataFilter->FilterBytes(response, command, 2)
                    );
    }
    case S01P32:
    {
        std::string command = m_CommandRepository->GetEvapVaporPressure()+'\r';
        SendCommand(command);
        std::string response = ReadResponse();
        return m_DataObtainer->GetEvapVaporPressure(
                    m_DataFilter->FilterBytes(response, command, 2)
                    );
    }
    case S01P33:
    {
        std::string command = m_CommandRepository->GetAbsoluteBarometricPressure()+'\r';
        SendCommand(command);
        std::string response = ReadResponse();
        return m_DataObtainer->GetAbsoluteBarometricPressure(
                    m_DataFilter->FilterBytes(response, command, 1)
                    );
    }
    case S01P34:
    {
        std::string command = m_CommandRepository->GetOxygenSensorEqC1()+'\r';
        SendCommand(command);
        std::string response = ReadResponse();
        return m_DataObtainer->GetOxygenSensorEqC1(
                    m_DataFilter->FilterBytes(response, command, 4)
                    );
    }
    case S01P35:
    {
        std::string command = m_CommandRepository->GetOxygenSensorEqC2()+'\r';
        SendCommand(command);
        std::string response = ReadResponse();
        return m_DataObtainer->GetOxygenSensorEqC2(
                    m_DataFilter->FilterBytes(response, command, 4)
                    );
    }
    case S01P36:
    {
        std::string command = m_CommandRepository->GetOxygenSensorEqC3()+'\r';
        SendCommand(command);
        std::string response = ReadResponse();
        return m_DataObtainer->GetOxygenSensorEqC3(
                    m_DataFilter->FilterBytes(response, command, 4)
                    );
    }
    case S01P37:
    {
        std::string command = m_CommandRepository->GetOxygenSensorEqC4()+'\r';
        SendCommand(command);
        std::string response = ReadResponse();
        return m_DataObtainer->GetOxygenSensorEqC4(
                    m_DataFilter->FilterBytes(response, command, 4)
                    );
    }
    case S01P38:
    {
        std::string command = m_CommandRepository->GetOxygenSensorEqC5()+'\r';
        SendCommand(command);
        std::string response = ReadResponse();
        return m_DataObtainer->GetOxygenSensorEqC5(
                    m_DataFilter->FilterBytes(response, command, 4)
                    );
    }
    case S01P39:
    {
        std::string command = m_CommandRepository->GetOxygenSensorEqC6()+'\r';
        SendCommand(command);
        std::string response = ReadResponse();
        return m_DataObtainer->GetOxygenSensorEqC6(
                    m_DataFilter->FilterBytes(response, command, 4)
                    );
    }
    case S01P3A:
    {
        std::string command = m_CommandRepository->GetOxygenSensorEqC7()+'\r';
        SendCommand(command);
        std::string response = ReadResponse();
        return m_DataObtainer->GetOxygenSensorEqC7(
                    m_DataFilter->FilterBytes(response, command, 4)
                    );
    }
    case S01P3B:
    {
        std::string command = m_CommandRepository->GetOxygenSensorEqC8()+'\r';
        SendCommand(command);
        std::string response = ReadResponse();
        return m_DataObtainer->GetOxygenSensorEqC8(
                    m_DataFilter->FilterBytes(response, command, 4)
                    );
    }
    case S01P3C:
    {
        std::string command = m_CommandRepository->GetCatalystTemperatureB1S1()+'\r';
        SendCommand(command);
        std::string response = ReadResponse();
        return m_DataObtainer->GetCatalystTemperatureB1S1(
                    m_DataFilter->FilterBytes(response, command, 2)
                    );
    }
    case S01P3D:
    {
        std::string command = m_CommandRepository->GetCatalystTemperatureB2S1()+'\r';
        SendCommand(command);
        std::string response = ReadResponse();
        return m_DataObtainer->GetCatalystTemperatureB2S1(
                    m_DataFilter->FilterBytes(response, command, 2)
                    );
    }
    case S01P3E:
    {
        std::string command = m_CommandRepository->GetCatalystTemperatureB1S2()+'\r';
        SendCommand(command);
        std::string response = ReadResponse();
        return m_DataObtainer->GetCatalystTemperatureB1S2(
                    m_DataFilter->FilterBytes(response, command, 2)
                    );
    }
    case S01P3F:
    {
        std::string command = m_CommandRepository->GetCatalystTemperatureB2S2()+'\r';
        SendCommand(command);
        std::string response = ReadResponse();
        return m_DataObtainer->GetCatalystTemperatureB2S2(
                    m_DataFilter->FilterBytes(response, command, 2)
                    );
    }
    default:
            return std::optional<std::string>();
        }
    }
