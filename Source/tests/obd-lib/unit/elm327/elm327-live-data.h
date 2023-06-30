#ifndef ELM327LIVEDATA_H
#define ELM327LIVEDATA_H
#include <gtest/gtest.h>
#include <future>
#include <thread>

#include "../obd-access-utils.h"
#include "../../../../fluffy-obd-lib/diagnostics-engine/elm327/elm327-engine.hpp"

using namespace testing;

TEST(elm327LiveData, noDeviceConnection)
{
    Elm327Engine engine;
    EXPECT_EQ(engine.OpenConnection(), false);
}

TEST(elm327LiveData, dummyUsb)
{
    PipesEnv pipe;

    Obd::Device dummyUsb = CreateUsbDevice();
    Elm327Engine engine;
    engine.SetSerialDevice(dummyUsb);
    EXPECT_EQ(engine.OpenConnection(), true);
}

TEST(elm327LiveData, dummyUsbNullCharResponse)
{
    PipesEnv pipe;

    Obd::Device dummyUsb = CreateUsbDevice();
    Elm327Engine engine;
    engine.SetSerialDevice(dummyUsb);
    engine.OpenConnection();

    EXPECT_THROW({
        Response response = engine.GetCommandResponse(ObdCommandPid::S01P04);
    }, std::runtime_error);
}

TEST(elm327LiveData, dummyUsbValidResponse)
{
    PipesEnv pipe;

    Obd::Device dummyUsb = CreateUsbDevice();
    Elm327Engine engine;
    engine.SetSerialDevice(dummyUsb);
    engine.OpenConnection();

    std::future<Response> futureResponse = std::async(&Elm327Engine::GetCommandResponse,
                                                      &engine, ObdCommandPid::S01P04);
    usleep(5 * 1000); //sleep 5 ms
    pipe.drainData();
    pipe.feedData("7E8 03 41 04 FF");
    Response response = futureResponse.get();

    EXPECT_NEAR(100.0, response.m_floatData1.first, 0.0001);
    EXPECT_EQ("%", response.m_floatData1.second);
    EXPECT_EQ(DataType::number, response.m_dataType);

    EXPECT_EQ("4104", response.m_rawResponse.m_commandId);
    EXPECT_EQ("7E8", response.m_rawResponse.m_ecuId);
    EXPECT_EQ(3, response.m_rawResponse.m_lenght);
    EXPECT_EQ("FF", response.m_rawResponse.m_data);

    std::clog<<"Decoded: "
             << response.m_floatData1.first
             << response.m_floatData1.second << std::endl;
}

#endif // ELM327LIVEDATA_H
