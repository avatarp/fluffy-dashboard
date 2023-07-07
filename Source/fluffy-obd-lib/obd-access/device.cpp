#include "device.hpp"

namespace Obd {

std::string Device::GetDescription() const
{
    return this->m_Description;
}

ConnectionType Device::GetConnectionType() const
{
    return this->m_ConnectionType;
}

std::string Device::GetDeviceFilePath() const
{
    return this->m_DeviceFilePath;
}
} // namespace Obd
