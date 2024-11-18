#ifndef DECODERPM_HPP_
#define DECODERPM_HPP_

#include "Decode.hpp"

// Decodes
// 0C Engine RPM -> 0-16 383.75 RPM
class DecodeRPM : public DecodeFloat {
public:
    const size_t expectedInputSize { 4 };

    float decode(const std::string& text) const override
    {
        if (text.length() != 4)
            throw std::runtime_error("invalid input");

        std::string byteA { text[0], text[1] };
        std::string byteB { text[2], text[3] };
        float valA = static_cast<float>(Utils::hexToDec(byteA));
        float valB = static_cast<float>(Utils::hexToDec(byteB));
        return (256 * valA + valB) / 4;
    }
};

#endif // DECODERPM_HPP_