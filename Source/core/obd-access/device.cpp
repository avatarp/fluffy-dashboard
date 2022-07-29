#include "device.h"

namespace Obd {

const std::string Device::GetDescription() const
{
    return this->m_Description;
}

ConnectionType Device::GetConnectionType() const
{
    return this->m_ConnectionType;
}

const std::string Device::GetDeviceFilePath() const
{
    return this->m_DeviceFilePath;
}
}
