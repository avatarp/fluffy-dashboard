#ifndef COMMAND_REPO_TEST_H_
#define COMMAND_REPO_TEST_H_

#include "elm327-command-repository.hpp"
#include <bitset>
#include <optional>

#include <gtest/gtest.h>

using namespace testing;

class elm327CommandRepo : public ::testing::Test {
protected:
    Elm327CommandRepository repo {};
};

TEST_F(elm327CommandRepo, repo00)
{
    EXPECT_EQ(repo.GetSupportedPIDs1(), "0100\r");
}

TEST_F(elm327CommandRepo, repo01)
{
    EXPECT_EQ(repo.GetMonitorStatus(), "0101\r");
}

TEST_F(elm327CommandRepo, repo02)
{
    EXPECT_EQ(repo.GetFreezeDTCs(), "0102\r");
}

TEST_F(elm327CommandRepo, repo03)
{
    EXPECT_EQ(repo.GetFuelSystemStatus(), "0103\r");
}

TEST_F(elm327CommandRepo, repo04)
{
    EXPECT_EQ(repo.GetEngineLoad(), "0104\r");
}

TEST_F(elm327CommandRepo, repo05)
{
    EXPECT_EQ(repo.GetEngineCoolantTemperature(), "0105\r");
}

TEST_F(elm327CommandRepo, repo06)
{
    EXPECT_EQ(repo.GetShortTermFuelTrimBank1(), "0106\r");
}

TEST_F(elm327CommandRepo, repo07)
{
    EXPECT_EQ(repo.GetLongTermFuelTrimBank1(), "0107\r");
}

TEST_F(elm327CommandRepo, repo08)
{
    EXPECT_EQ(repo.GetShortTermFuelTrimBank2(), "0108\r");
}

TEST_F(elm327CommandRepo, repo09)
{
    EXPECT_EQ(repo.GetLongTermFuelTrimBank2(), "0109\r");
}

TEST_F(elm327CommandRepo, repo0A)
{
    EXPECT_EQ(repo.GetFuelPressure(), "010A\r");
}

TEST_F(elm327CommandRepo, repo0B)
{
    EXPECT_EQ(repo.GetIntakeManifoldPressure(), "010B\r");
}

TEST_F(elm327CommandRepo, repo0C)
{
    EXPECT_EQ(repo.GetEngineRpm(), "010C\r");
}

TEST_F(elm327CommandRepo, repo0D)
{
    EXPECT_EQ(repo.GetSpeed(), "010D\r");
}

TEST_F(elm327CommandRepo, repo0E)
{
    EXPECT_EQ(repo.GetTimingAdvance(), "010E\r");
}

TEST_F(elm327CommandRepo, repo0F)
{
    EXPECT_EQ(repo.GetIntakeAirTemperature(), "010F\r");
}

TEST_F(elm327CommandRepo, repo10)
{
    EXPECT_EQ(repo.GetMafAirFlowRate(), "0110\r");
}

TEST_F(elm327CommandRepo, repo11)
{
    EXPECT_EQ(repo.GetThrottlePosition(), "0111\r");
}

TEST_F(elm327CommandRepo, repo12)
{
    EXPECT_EQ(repo.GetSecondaryAirStatus(), "0112\r");
}

TEST_F(elm327CommandRepo, repo13)
{
    EXPECT_EQ(repo.GetOxygenSensorsPresent1(), "0113\r");
}

TEST_F(elm327CommandRepo, repo14)
{
    EXPECT_EQ(repo.GetOxygenSensorFtV1(), "0114\r");
}

TEST_F(elm327CommandRepo, repo15)
{
    EXPECT_EQ(repo.GetOxygenSensorFtV2(), "0115\r");
}

TEST_F(elm327CommandRepo, repo16)
{
    EXPECT_EQ(repo.GetOxygenSensorFtV3(), "0116\r");
}

TEST_F(elm327CommandRepo, repo17)
{
    EXPECT_EQ(repo.GetOxygenSensorFtV4(), "0117\r");
}

TEST_F(elm327CommandRepo, repo18)
{
    EXPECT_EQ(repo.GetOxygenSensorFtV5(), "0118\r");
}

TEST_F(elm327CommandRepo, repo19)
{
    EXPECT_EQ(repo.GetOxygenSensorFtV6(), "0119\r");
}

TEST_F(elm327CommandRepo, repo1A)
{
    EXPECT_EQ(repo.GetOxygenSensorFtV7(), "011A\r");
}

TEST_F(elm327CommandRepo, repo1B)
{
    EXPECT_EQ(repo.GetOxygenSensorFtV8(), "011B\r");
}

TEST_F(elm327CommandRepo, repo1C)
{
    EXPECT_EQ(repo.GetObdStandard(), "011C\r");
}

TEST_F(elm327CommandRepo, repo1D)
{
    EXPECT_EQ(repo.GetOxygenSensorsPresent2(), "011D\r");
}

TEST_F(elm327CommandRepo, repo1E)
{
    EXPECT_EQ(repo.GetAuxiliaryInputStatus(), "011E\r");
}

TEST_F(elm327CommandRepo, repo1F)
{
    EXPECT_EQ(repo.GetRunTime(), "011F\r");
}

TEST_F(elm327CommandRepo, repo20)
{
    EXPECT_EQ(repo.GetSupportedPIDs2(), "0120\r");
}

TEST_F(elm327CommandRepo, repo21)
{
    EXPECT_EQ(repo.GetDistanceWithMilOn(), "0121\r");
}

TEST_F(elm327CommandRepo, repo22)
{
    EXPECT_EQ(repo.GetFuelRailPressure(), "0122\r");
}

TEST_F(elm327CommandRepo, repo23)
{
    EXPECT_EQ(repo.GetFuelRailGaugePressure(), "0123\r");
}

TEST_F(elm327CommandRepo, repo24)
{
    EXPECT_EQ(repo.GetOxygenSensorEqV1(), "0124\r");
}

TEST_F(elm327CommandRepo, repo25)
{
    EXPECT_EQ(repo.GetOxygenSensorEqV2(), "0125\r");
}

TEST_F(elm327CommandRepo, repo26)
{
    EXPECT_EQ(repo.GetOxygenSensorEqV3(), "0126\r");
}

TEST_F(elm327CommandRepo, repo27)
{
    EXPECT_EQ(repo.GetOxygenSensorEqV4(), "0127\r");
}

TEST_F(elm327CommandRepo, repo28)
{
    EXPECT_EQ(repo.GetOxygenSensorEqV5(), "0128\r");
}

TEST_F(elm327CommandRepo, repo29)
{
    EXPECT_EQ(repo.GetOxygenSensorEqV6(), "0129\r");
}

TEST_F(elm327CommandRepo, repo2A)
{
    EXPECT_EQ(repo.GetOxygenSensorEqV7(), "012A\r");
}

TEST_F(elm327CommandRepo, repo2B)
{
    EXPECT_EQ(repo.GetOxygenSensorEqV8(), "012B\r");
}

TEST_F(elm327CommandRepo, repo2C)
{
    EXPECT_EQ(repo.GetCommandedEgr(), "012C\r");
}

TEST_F(elm327CommandRepo, repo2D)
{
    EXPECT_EQ(repo.GetEgrError(), "012D\r");
}

TEST_F(elm327CommandRepo, repo2E)
{
    EXPECT_EQ(repo.GetCommandedEvaporativePurge(), "012E\r");
}

TEST_F(elm327CommandRepo, repo2F)
{
    EXPECT_EQ(repo.GetFuelTankLevelInput(), "012F\r");
}

TEST_F(elm327CommandRepo, repo30)
{
    EXPECT_EQ(repo.GetWarmupsSinceDtcCleared(), "0130\r");
}

TEST_F(elm327CommandRepo, repo31)
{
    EXPECT_EQ(repo.GetDistanceSinceDtcCleared(), "0131\r");
}

TEST_F(elm327CommandRepo, repo32)
{
    EXPECT_EQ(repo.GetEvapVaporPressure(), "0132\r");
}

TEST_F(elm327CommandRepo, repo33)
{
    EXPECT_EQ(repo.GetAbsoluteBarometricPressure(), "0133\r");
}

TEST_F(elm327CommandRepo, repo34)
{
    EXPECT_EQ(repo.GetOxygenSensorEqC1(), "0134\r");
}

TEST_F(elm327CommandRepo, repo35)
{
    EXPECT_EQ(repo.GetOxygenSensorEqC2(), "0135\r");
}

TEST_F(elm327CommandRepo, repo36)
{
    EXPECT_EQ(repo.GetOxygenSensorEqC3(), "0136\r");
}

TEST_F(elm327CommandRepo, repo37)
{
    EXPECT_EQ(repo.GetOxygenSensorEqC4(), "0137\r");
}

TEST_F(elm327CommandRepo, repo38)
{
    EXPECT_EQ(repo.GetOxygenSensorEqC5(), "0138\r");
}

TEST_F(elm327CommandRepo, repo39)
{
    EXPECT_EQ(repo.GetOxygenSensorEqC6(), "0139\r");
}

TEST_F(elm327CommandRepo, repo3A)
{
    EXPECT_EQ(repo.GetOxygenSensorEqC7(), "013A\r");
}

TEST_F(elm327CommandRepo, repo3B)
{
    EXPECT_EQ(repo.GetOxygenSensorEqC8(), "013B\r");
}

TEST_F(elm327CommandRepo, repo3C)
{
    EXPECT_EQ(repo.GetCatalystTemperatureB1S1(), "013C\r");
}

TEST_F(elm327CommandRepo, repo3D)
{
    EXPECT_EQ(repo.GetCatalystTemperatureB2S1(), "013D\r");
}

TEST_F(elm327CommandRepo, repo3E)
{
    EXPECT_EQ(repo.GetCatalystTemperatureB1S2(), "013E\r");
}

TEST_F(elm327CommandRepo, repo3F)
{
    EXPECT_EQ(repo.GetCatalystTemperatureB2S2(), "013F\r");
}

#endif // COMMAND_REPO_TEST_H_