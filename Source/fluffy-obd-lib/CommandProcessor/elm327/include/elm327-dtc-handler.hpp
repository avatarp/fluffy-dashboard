
#ifndef ELM327_DTC_HANDLER_HPP
#define ELM327_DTC_HANDLER_HPP

#include "IDtc-handler.hpp"

class Elm327DtcHandler : public IDtcHandler {
    static std::vector<std::string> ParseDtcResponse(Response& dtcResponse);

public:
    // Default constructor and destructor
    Elm327DtcHandler() = default;
    virtual ~Elm327DtcHandler() = default;

    // Decode stored DTCs from the response
    virtual void ParseStoredDtc(Response& dtcResponse) override;

    // Decode pending DTCs from the response
    virtual void ParsePendingDtc(Response& dtcResponse) override;

    // Decode permanent DTCs from the response
    virtual void ParsePermanentDtc(Response& dtcResponse) override;
};

#endif // ELM327_DTC_HANDLER_HPP