#ifndef DECODE_HPP_
#define DECODE_HPP_

#include <bitset>
#include <optional>
#include <sstream>

namespace Utils {

inline long hexToDec(std::string& hex) { return strtol(hex.c_str(), nullptr, 16); }

inline uint32_t hexStringValue(std::string hex)
{
    std::stringstream converter(hex);
    uint32_t value;
    converter >> std::hex >> value;
    return value;
}

inline uint32_t hexStringValue(char hex)
{
    std::stringstream converter;
    converter << hex;

    uint32_t value;
    converter >> std::hex >> value;
    return value;
}

inline int32_t twoComplementaryHexToDec(std::string hexString)
{
    std::bitset<8> binary(hexStringValue(hexString));

    if (binary.test(7)) {
        binary.reset(7);
        int32_t temp = static_cast<int32_t>(binary.to_ulong());
        temp -= 128;
        return temp;
    }
    return static_cast<int32_t>(binary.to_ulong());
}

} // namespace Utils

class DecodeFloat {
public:
    virtual ~DecodeFloat() { }
    virtual float decode(const std::string& text) const = 0;
};

class DecodeBitEncoded {
public:
    const std::size_t minimalInputSize { 2 };

    virtual ~DecodeBitEncoded() { }

    // Decodes
    // PIDs supported 00, 20, 40, 60, 80, A0, C0
    // 12 Commanded secondary air status
    // 13 Oxygen sensors present (in 2 banks)
    // 1D Oxygen sensors present (in 4 banks)
    // 1E Auxiliary input status
    virtual std::bitset<32> decode(const std::string& text) const
    {
        if (text.length() < minimalInputSize)
            throw std::runtime_error("invalid input");

        return std::bitset<32>(Utils::hexStringValue(text));
    }
};

class DecodeString {
public:
    DecodeString() = default;
    virtual ~DecodeString() = default;
    virtual std::string decode(const std::string& text)
    {
        std::string result;
        result.reserve(text.size() / 2);
        for (size_t i = 0; i < text.length(); i += 2) {
            std::string byte = text.substr(i, 2);
            result.push_back(static_cast<char>(strtol(byte.c_str(), nullptr, 16)));
        }

        return result;
    }
};

#endif // DECODE_HPP_