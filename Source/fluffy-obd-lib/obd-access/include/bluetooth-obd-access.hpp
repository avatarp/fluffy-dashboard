#ifndef BLUETOOTH_OBD_ACCESS_HPP_
#define BLUETOOTH_OBD_ACCESS_HPP_

#include "obd-access.hpp"

namespace Obd {

class BluetoothObdAccess : public ObdAccess {
private:
    virtual bool ApplyDefaultConnectionSettings();
    /// @brief Time of waiting for response after sending message in ms
    uint16_t afterWriteSleepTime { 500 };
    virtual bool IsDeviceFileOk() override;
    virtual bool OpenConnection() override;

public:
    BluetoothObdAccess() = default;
    ~BluetoothObdAccess() = default;
    virtual void SetDevice(Device device) override final;
    virtual bool Connect() override;
    virtual bool Write(const std::string& command) override;
    virtual std::string Read() override;
};
}

#endif // BLUETOOTH_OBD_ACCESS_HPP_