#include "bluetooth-provider.hpp"
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

bool BluetoothProvider::IsBluetoothAvailable()
{
    return localDevice.isValid();
}

bool BluetoothProvider::BindToRfcomm(const QBluetoothDeviceInfo& device) // NOLINT
{
    if (device.address().isNull()) {
        return false; // NOLINT
    }

    return true;
}

Obd::Device BluetoothProvider::CreateDevice(const QBluetoothDeviceInfo& device)
{
    if (std::filesystem::exists(Obd::DefaultRfcommFile)) {
        BindToRfcomm(device);
    }
    return Obd::Device { Obd::DefaultRfcommFile,
        Obd::ConnectionType::Bluetooth,
        device.name().toStdString() };
}
} // namespace Obd
