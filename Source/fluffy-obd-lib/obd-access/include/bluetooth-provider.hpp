#ifndef BLUETOOTH_PROVIDER_HPP_
#define BLUETOOTH_PROVIDER_HPP_

#include "device.hpp"
#include <QtBluetooth/QBluetoothDeviceDiscoveryAgent>
#include <QtBluetooth/QBluetoothLocalDevice>
#include <filesystem>

namespace Obd {

const std::string DefaultRfcommFile = "/dev/rfcomm0";
class BluetoothProvider {
    std::shared_ptr<QBluetoothDeviceDiscoveryAgent> discoveryAgent { std::make_shared<QBluetoothDeviceDiscoveryAgent>() };
    QBluetoothLocalDevice localDevice {};

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
    bool IsBluetoothAvailable();
    bool BindToRfcomm(const QBluetoothDeviceInfo& device);
    Obd::Device CreateDevice(const QBluetoothDeviceInfo& device);
};

}

#endif // BLUETOOTH_PROVIDER_HPP_