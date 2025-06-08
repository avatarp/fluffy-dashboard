#ifndef IDTC_HANDLER_HPP_
#define IDTC_HANDLER_HPP_

#include "response.hpp"

#include <string>
#include <vector>

class IDtcHandler {
protected:
    std::vector<std::string> m_storedDtcCodes;
    std::vector<std::string> m_pendingDtcCodes;
    std::vector<std::string> m_permanentDtcCodes;

public:
    // Default constructor and destructor
    IDtcHandler() = default;
    virtual ~IDtcHandler() = default;

    virtual void ParseStoredDtc(Response& dtcResponse) = 0;
    virtual void ParsePendingDtc(Response& dtcResponse) = 0;
    virtual void ParsePermanentDtc(Response& dtcResponse) = 0;
};

#endif // IDTC_HANDLER_HPP_