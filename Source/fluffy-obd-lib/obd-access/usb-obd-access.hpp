#pragma once
#include "obd-access.hpp"

namespace Obd {

class UsbObdAccess : public ObdAccess
{
private:
    virtual bool Write(const std::string& command) override;
    virtual std::string Read() override;
    void SetupDefaultTermios();
public:
    UsbObdAccess() = default;
    ~UsbObdAccess();
    virtual void SetDevice(Device device) override final;
    virtual bool Connect() override;
};
}
