#ifndef IDTC_HANDLER_HPP_
#define IDTC_HANDLER_HPP_

#include "response.hpp"

#include <string>
#include <vector>

struct RetrievedDtc {
    std::vector<std::string> storedDtcCodes;
    std::vector<std::string> pendingDtcCodes;
    std::vector<std::string> permanentDtcCodes;
};

class IDtcHandler {
protected:
    RetrievedDtc m_retrievedDtc;

public:
    IDtcHandler() = default;
    virtual ~IDtcHandler() = default;

    virtual void ParseStoredDtc(Response& dtcResponse) = 0;
    virtual void ParsePendingDtc(Response& dtcResponse) = 0;
    virtual void ParsePermanentDtc(Response& dtcResponse) = 0;

    void ClearDtcData()
    {
        m_retrievedDtc.storedDtcCodes.clear();
        m_retrievedDtc.pendingDtcCodes.clear();
        m_retrievedDtc.permanentDtcCodes.clear();
    }

    std::vector<std::string> GetStoredDtcCodes() const
    {
        return m_retrievedDtc.storedDtcCodes;
    }

    std::vector<std::string> GetPendingDtcCodes() const
    {
        return m_retrievedDtc.pendingDtcCodes;
    }

    std::vector<std::string> GetPermanentDtcCodes() const
    {
        return m_retrievedDtc.permanentDtcCodes;
    }
};

#endif // IDTC_HANDLER_HPP_