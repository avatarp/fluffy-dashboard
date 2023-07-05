#pragma once
#include "obd-access.hpp"

namespace Obd {

class BluetoothObdAccess : public ObdAccess
{
private:
    virtual bool Write(const std::string& command) override;
    virtual std::string Read() override;
    void SetupDefaultTermios();
public:
    BluetoothObdAccess() = default;
    ~BluetoothObdAccess() = default;
    virtual void SetDevice(Device device) override final;
    virtual bool Connect() override;
};
}
