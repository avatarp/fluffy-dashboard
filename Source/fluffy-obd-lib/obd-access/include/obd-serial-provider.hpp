#ifndef OBD_SERIAL_PROVIDER_HPP_
#define OBD_SERIAL_PROVIDER_HPP_

#include "device.hpp"
#include <vector>

#include <spdlog/spdlog.h>

namespace Obd {

class ObdSerialProvider {
public:
    static std::vector<Device> GetAvailableDevices();
    static std::vector<std::string> get_available_ports();
};

}

#endif // OBD_SERIAL_PROVIDER_HPP_