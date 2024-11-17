#ifndef DECODEDTC_HPP_
#define DECODEDTC_HPP_

#include "Decode.hpp"

class DecodeDTC : DecodeString {
public:
    const size_t minimalInputSize { 4 };

    std::string decode(const std::string& text) override
    {
        if (text.length() < minimalInputSize)
            throw std::runtime_error("invalid input");

        const uint8_t byteAValue = static_cast<uint8_t>(Utils::hexStringValue(text[0]));
        const uint8_t dtcLocation { static_cast<uint8_t>((byteAValue & 0b1100) >> 2) };
        std::string dtc;

        switch (dtcLocation) {
        // clang-format off
        case 0: dtc.push_back('P'); break;
        case 1: dtc.push_back('C'); break;
        case 2: dtc.push_back('B'); break;
        case 3: dtc.push_back('U'); break;
        default: break;
        }
        // clang-format on

        const uint8_t dtcFirstDigit = byteAValue & 0b0011;
        dtc += std::to_string(dtcFirstDigit);
        // insert rest of the dtc
        dtc += text.substr(1, 3);
        return dtc;
    }
};

#endif // DECODEDTC_HPP_
