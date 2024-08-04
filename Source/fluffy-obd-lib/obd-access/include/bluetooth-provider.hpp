#ifndef BLUETOOTH_PROVIDER_HPP_
#define BLUETOOTH_PROVIDER_HPP_

#include "device.hpp"
#include <QtBluetooth/QBluetoothDeviceDiscoveryAgent>
#include <QtBluetooth/QBluetoothLocalDevice>
#include <filesystem>

namespace Obd {
static std::string const Rfcomm { "rfcomm" };
static std::string const DefaultRfcommFilesPath = "/dev/rfcomm";
static std::string const DefaultRfcommDeviceFilePath = "/dev/rfcomm0";
class BluetoothProvider {
    std::shared_ptr<QBluetoothDeviceDiscoveryAgent> discoveryAgent { std::make_shared<QBluetoothDeviceDiscoveryAgent>() };
    QBluetoothLocalDevice localDevice {};
    bool isRfcommDevice(const std::string& filename) const;
    std::vector<std::string> GetExistingRfcommDevices();

public:
    BluetoothProvider() = default;
    ~BluetoothProvider() = default;
    BluetoothProvider(const BluetoothProvider& other) = delete;
    BluetoothProvider(BluetoothProvider&& other) = default;
    BluetoothProvider& operator=(const BluetoothProvider& other) = delete;
    BluetoothProvider& operator=(BluetoothProvider&& other) = default;

    bool StartScan();
    void StopScan();
    std::vector<QBluetoothDeviceInfo> GetAvailableDevicesInfo();
    bool IsBluetoothAvailable() const;
    bool BindToRfcomm(const QBluetoothDeviceInfo& device);
    Obd::Device CreateDevice(const QBluetoothDeviceInfo& device);
};

}

#endif // BLUETOOTH_PROVIDER_HPP_