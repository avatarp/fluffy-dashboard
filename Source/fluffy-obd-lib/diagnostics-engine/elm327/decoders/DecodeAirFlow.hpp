#ifndef DECODEAIRFLOW_HPP_
#define DECODEAIRFLOW_HPP_

#include "Decode.hpp"

// Decodes 10 Mass Air Flow
//-> 0-655.35 gram/second
class DecodeAirFlow : public DecodeFloat {
public:
    float decode(const std::string& text) const override
    {
        if (text.length() != 5)
            throw std::runtime_error("invalid input");

        std::string byteA { text[0], text[1] };
        std::string byteB { text[3], text[4] };
        float valA = Utils::hexToDec(byteA);
        float valB = Utils::hexToDec(byteB);
        return (256 * valA + valB) / 100;
    }
};

#endif // DECODEAIRFLOW_HPP_