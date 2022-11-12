#pragma once
#include <filesystem>
#include <vector>
#include <string>
#include <regex>
#include "../utils/system-calls.h"
#include "../obd-access/device.h"

namespace Obd {

class UsbSerialProvider
{
public:
    static std::vector<Device> GetAvailableDevices();
};

}
