#ifndef ELM327_DTC_HANDLER_HPP_
#define ELM327_DTC_HANDLER_HPP_

#include "../dtc-handler.h"

class Elm327dtcHandler : public DtcHandler {
private:
    virtual std::vector<std::string> SanitizeData(std::string& data);

public:
    Elm327dtcHandler();
    virtual ~Elm327dtcHandler();
    virtual std::vector<std::string> GetDTCs(const std::string& data);
};

#endif // ELM327_DTC_HANDLER_HPP_