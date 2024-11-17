#ifndef DECODEEVAPPRESSURE_HPP_
#define DECODEEVAPPRESSURE_HPP_

#include "Decode.hpp"

// Decodes
// 32 Evap. system Vapor pressure
//-> -8192-8191.75 Pa
class DecodeEvapPressure : public DecodeFloat {
public:
    const size_t expectedInputSize { 4 };

    float decode(const std::string& text) const override
    {
        if (text.length() != expectedInputSize)
            throw std::runtime_error("invalid input");

        std::string byteA { text[0], text[1] };
        float valA = static_cast<float>(Utils::twoComplementaryHexToDec(byteA));
        std::string byteB { text[2], text[3] };
        float valB = static_cast<float>(Utils::hexToDec(byteB));
        return 0.25f * (256.0f * valA + valB);
    }
};

#endif // DECODEEVAPPRESSURE_HPP_