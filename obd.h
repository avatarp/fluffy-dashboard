#pragma once
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <iostream>
#include <errno.h>
#include <regex>
#include <map>
//#include <QtDebug>
#include "utils.h"
#include "constants.h"
#include <gtest/gtest.h>

class obd2Interface
{

private:
    friend class TEST;
    struct termios serialConnection;
    const std::string port="/dev/rfcomm0";
    const int baudRate=B38400;
    int connectionHandle;
    bool connected=false;
    void setupTermios();
    bool sendMessage(std::string msg);
    std::string readMessage();
    std::string getDataBytes(std::string command,std::string text);
    std::string getRawData(std::string command);
    std::map<std::string,bool> supportedPIDs;
    bool findSupportedPIDs();
public:
    obd2Interface();
    ~obd2Interface();
    bool initConnection();
    bool isConnected(){return connected;}
    std::string getCarPIDs();
    std::vector<std::string> getSupportedPIDs();
    bool isCommandSupported(std::string PID);
    double getEngineLoadPercentage();
    long getEngineRPM();
    long getCoolantTemp();
    long getAirIntakeTemp();
    long getSpeed();
    float getMafAirFlow();
    long getIntakeManifoldPressure();
    double getThrottlePosition();
    double getTimingAdvance();
    double getShortTermFuelTrim1();
    double getLongTermFuelTrim1();

    double getO2Bank1Sensor1Voltage();
    double getO2Bank1Sensor1ShortTermFuelTrim();
    double getO2Bank1Sensor2Voltage();
    double getO2Bank1Sensor2ShortTermFuelTrim();
    std::string getFuelSystemStatus();

    std::string getVIN();
};
