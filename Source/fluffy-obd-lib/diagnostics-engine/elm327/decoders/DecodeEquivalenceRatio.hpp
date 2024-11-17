#ifndef DECODEEQUIVALENCERATIO_HPP_
#define DECODEEQUIVALENCERATIO_HPP_

#include "Decode.hpp"

// Decodes:
// 24-2B,34-3B (AB) Air-Fuel Equivalence Ratio (lambda,λ)
//-> 0-2
class DecodeEquivalenceRatio : public DecodeFloat {
public:
    const size_t expectedInputSize { 4 };

    float decode(const std::string& text) const override
    {
        if (text.length() != expectedInputSize)
            throw std::runtime_error("invalid input");

        std::string byteA { text[0], text[1] };
        std::string byteB { text[2], text[3] };
        float valA = static_cast<float>(Utils::hexToDec(byteA));
        float valB = static_cast<float>(Utils::hexToDec(byteB));
        return 2.0f / 65536.0f * (256.0f * valA + valB);
    }
};

#endif // DECODEEQUIVALENCERATIO_HPP_
