#include "../../../../../Source/fluffy-obd-lib/obd-access/obd-access.hpp"
#include <gmock/gmock.h>

struct MockObdAccess : Obd::ObdAccess {
    MOCK_METHOD(bool, Write, (const std::string&));
    // virtual bool Write(const std::string& command) = 0;
    MOCK_METHOD(std::string, Read, ());

    MOCK_METHOD(bool, Connect, ());

    MOCK_METHOD(void, SetDevice, (Obd::Device));
    // virtual std::string Read() = 0;
    // std::string Transaction(const std::string& command);
};