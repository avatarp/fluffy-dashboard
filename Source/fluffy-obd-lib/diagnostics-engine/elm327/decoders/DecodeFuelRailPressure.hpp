#ifndef DECODEFUELRAILPRESSURE_HPP_
#define DECODEFUELRAILPRESSURE_HPP_

#include "Decode.hpp"

// Decodes:
// 22 Fuel Rail Pressure (relative to manifold vacuum)
//-> 0-5177.265 kPa
class DecodeFuelRailPressure : public DecodeFloat {
public:
    const size_t expectedInputSize { 4 };

    float decode(const std::string& text) const override
    {
        if (text.length() != expectedInputSize)
            throw std::runtime_error("invalid input");

        std::string byteA { text[0], text[1] };
        float valA = static_cast<float>(Utils::hexToDec(byteA));
        std::string byteB { text[2], text[3] };
        float valB = static_cast<float>(Utils::hexToDec(byteB));
        return 0.079f * (256.0f * valA + valB);
    }
};

// Decodes:
// 23 Fuel Rail Gauge pressure (diesel, or gasoline direct injection)
//-> 0-655350 kPa
class DecodeFuelRailGaugePressure : public DecodeFloat {
public:
    const size_t expectedInputSize { 4 };

    float decode(const std::string& text) const override
    {
        if (text.length() != expectedInputSize)
            throw std::runtime_error("invalid input");

        std::string byteA { text[0], text[1] };
        float valA = static_cast<float>(Utils::hexToDec(byteA));
        std::string byteB { text[2], text[3] };
        float valB = static_cast<float>(Utils::hexToDec(byteB));
        return 10 * (256 * valA + valB);
    }
};

#endif // DECODEFUELRAILPRESSURE_HPP_