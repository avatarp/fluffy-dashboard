#ifndef BLUETOOTH_PROVIDER_HPP_
#define BLUETOOTH_PROVIDER_HPP_

#include "device.hpp"
#include <QtBluetooth/QBluetoothDeviceDiscoveryAgent>
#include <QtBluetooth/QBluetoothLocalDevice>
#include <filesystem>

#include "spdlog/spdlog.h"

namespace Obd {
static std::string const rfcomm { "rfcomm" };
static std::string const deviceFilesPath = "/dev/";

class BluetoothProvider {
    std::shared_ptr<QBluetoothDeviceDiscoveryAgent> discoveryAgent { std::make_shared<QBluetoothDeviceDiscoveryAgent>() };
    QBluetoothLocalDevice bluetoothLocalDevice {};
    static bool isRfcommDevice(const std::string& filename);
    static std::vector<std::string> GetExistingRfcommDevices();

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
    static bool BindToRfcomm(const std::string& deviceAddress, uint16_t rfcommDeviceId);
    static Obd::Device CreateDevice(const QBluetoothDeviceInfo& device);
};

}

#endif // BLUETOOTH_PROVIDER_HPP_