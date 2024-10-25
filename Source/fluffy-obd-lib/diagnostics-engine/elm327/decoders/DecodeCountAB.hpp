#ifndef DECODECOUNTAB_HPP_
#define DECODECOUNTAB_HPP_

#include "Decode.hpp"

// Decodes:
// 22 Run time -> 0-65535 seconds
// 21 Distance with Malfunction Indicator Lamp on -> 0-65535 km
// 31 Distance since coded cleared -> 0-65535km
class DecodeCountAB : public DecodeFloat {
public:
    float decode(const std::string& text) const override
    {
        if (text.length() != 5)
            throw std::runtime_error("invalid input");

        std::string byteA { text[0], text[1] };
        float valA = static_cast<float>(Utils::hexToDec(byteA));
        std::string byteB { text[3], text[4] };
        float valB = static_cast<float>(Utils::hexToDec(byteB));
        return 256.0f * valA + valB;
    }
};

#endif // DECODECOUNTAB_HPP_