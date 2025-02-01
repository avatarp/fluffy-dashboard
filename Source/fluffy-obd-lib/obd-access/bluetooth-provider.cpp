#include "bluetooth-provider.hpp"

#include <filesystem>
#include <fstream>
#include <iostream>

namespace Obd {

bool BluetoothProvider::StartScan()
{
    if (bluetoothLocalDevice.isValid()) {
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
    return bluetoothLocalDevice.isValid();
}

bool BluetoothProvider::isRfcommDevice(const std::string& filename)
{
    return filename.find(rfcomm) != std::string::npos;
}

std::vector<std::string> BluetoothProvider::GetExistingRfcommDevices()
{
    namespace fs = std::filesystem;
    std::vector<std::string> devices;

    for (const auto& dirEntry : fs::directory_iterator(deviceFilesPath)) {
        if (isRfcommDevice(dirEntry.path().filename())) {
            devices.push_back(dirEntry.path().filename());
        }
    }
    return devices;
}

bool BluetoothProvider::BindToRfcomm(const std::string& deviceAddress, uint16_t rfcommDeviceId)
{
    std::stringstream bindCommandStream;
    bindCommandStream << "pkexec rfcomm bind " << std::to_string(rfcommDeviceId)
                      << " " << deviceAddress;
    auto const bindCommand { bindCommandStream.str() };
    spdlog::info("Executing bind to rfcomm command: {}", bindCommand);

    auto returnValue = system(bindCommand.c_str());

    if (returnValue > 0) {
        spdlog::error("bind command failed with value: {}", returnValue);
        return false;
    }

    bool const directoryExist = std::filesystem::exists((deviceFilesPath + rfcomm + std::to_string(rfcommDeviceId)));
    if (directoryExist) {
        spdlog::info("Bind successful, device file created");
    } else {
        spdlog::error("Bind failed! Device file not created");
    }
    return directoryExist;
}

std::string getDeviceMacAddress(const std::string& rfcommDevice)
{
    const std::string addressPrefix { "/sys/class/tty/" };
    const std::string addressPostfix { "/address" };
    std::ifstream addressFile(addressPrefix + rfcommDevice + addressPostfix);
    std::string address(std::istreambuf_iterator<char> { addressFile }, {});
    std::transform(address.begin(), address.end(), address.begin(), [](unsigned char chr) { return std::toupper(chr); });
    return address;
}

Obd::Device BluetoothProvider::CreateDevice(const QBluetoothDeviceInfo& device)
{
    if (device.address().isNull()) {
        throw(std::runtime_error("Invalid device address"));
    }

    const auto existingRfcommDevices = GetExistingRfcommDevices();
    std::string deviceAddress { device.address().toString().toStdString() };
    uint16_t rfcommDeviceId { 0 };
    if (!existingRfcommDevices.empty()) {
        for (const auto& rfcommDevice : existingRfcommDevices) {
            uint16_t deviceId = static_cast<uint16_t>(std::stoul(
                rfcommDevice.substr(rfcommDevice.find(rfcomm) + rfcomm.size(), std::string::npos)));

            if (deviceId > rfcommDeviceId) {
                rfcommDeviceId = deviceId;
            }
            if (getDeviceMacAddress(rfcommDevice).find(deviceAddress) != std::string::npos) {
                std::string deviceFilePath = deviceFilesPath + rfcomm + std::to_string(rfcommDeviceId);
                return Obd::Device { deviceFilePath,
                    Obd::ConnectionType::Bluetooth,
                    device.name().toStdString() };
            }
        }
        rfcommDeviceId++;
    }

    if (BindToRfcomm(deviceAddress, rfcommDeviceId)) {
        std::string deviceFilePath = deviceFilesPath + rfcomm + std::to_string(rfcommDeviceId);
        return Obd::Device { deviceFilePath,
            Obd::ConnectionType::Bluetooth,
            device.name().toStdString() };
    }
    throw(std::runtime_error("Bind to rfcomm failed"));
}
} // namespace Obd
