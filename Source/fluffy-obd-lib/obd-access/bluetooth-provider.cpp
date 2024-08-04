#include "bluetooth-provider.hpp"

#include <filesystem>

namespace Obd {

bool BluetoothProvider::StartScan()
{
    if (localDevice.isValid()) {
        this->discoveryAgent->start();
        return true;
    }
    return false;
}

void BluetoothProvider::StopScan()
{
    this->discoveryAgent->stop();
}

std::vector<QBluetoothDeviceInfo> BluetoothProvider::GetAvailableDevicesInfo()
{
    // NOLINTNEXTLINE
    auto devices { discoveryAgent->discoveredDevices() };
    return std::vector<QBluetoothDeviceInfo> { devices.begin(), devices.end() };
}

bool BluetoothProvider::IsBluetoothAvailable() const
{
    return localDevice.isValid();
}

bool BluetoothProvider::isRfcommDevice(const std::string& filename) const
{
    return filename.find(Rfcomm) != std::string::npos;
}

std::vector<std::string> BluetoothProvider::GetExistingRfcommDevices()
{
    namespace fs = std::filesystem;
    std::vector<std::string> devices;

    for (const auto& p : fs::directory_iterator(DefaultRfcommFilesPath)) {
        if (isRfcommDevice(p.path().filename()))
            devices.push_back(p.path());
    }
    return devices;
}

bool BluetoothProvider::BindToRfcomm(const QBluetoothDeviceInfo& device, std::string& deviceFilePath)
{
    if (device.address().isNull()) {
        return false;
    }

    uint32_t rfcommDeviceId { 0 };
    const auto existingRfcommDevices = GetExistingRfcommDevices();
    if (!existingRfcommDevices.empty()) {
        for (auto& rfcommDevice : existingRfcommDevices) {
            uint32_t deviceId = static_cast<uint32_t>(std::stoul(rfcommDevice.substr(rfcommDevice.find(Rfcomm) + Rfcomm.size(), rfcommDevice.npos)));
            if (deviceId > rfcommDeviceId) {
                rfcommDeviceId = deviceId;
            }
        }
        rfcommDeviceId++;
    }

    std::stringstream bindCommandStream;
    bindCommandStream << "pkexec rfcomm bind " << std::to_string(rfcommDeviceId) << " " << device.address().toString().toStdString();

    auto returnValue = system(bindCommandStream.str().c_str());

    if (returnValue > 0)
        return false;

    return std::filesystem::exists((DefaultRfcommFilesPath + std::to_string(rfcommDeviceId)));
}

Obd::Device BluetoothProvider::CreateDevice(const QBluetoothDeviceInfo& device)
{
    std::string deviceFilePath;
    if (BindToRfcomm(device, deviceFilePath))
        return Obd::Device { deviceFilePath,
        Obd::ConnectionType::Bluetooth,
        device.name().toStdString() };
    else
        throw(std::runtime_error("Bind to rfcomm failed"));
}
} // namespace Obd
