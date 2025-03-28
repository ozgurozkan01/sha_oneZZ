//
// Created by ozgur on 3/28/2025.
//

#ifndef SHA1_SHA1_H
#define SHA1_SHA1_H

#include <iostream>
#include <bitset>
#include <vector>
#include <cstdint>

class sha1 {
public:

    std::string add_padding(const std::string& bit_string);
    std::bitset<8> char_to_byte(const char& c);
    std::string message_to_bit(const std::string& message);
    std::vector<std::bitset<512>> split_512bit_groups(const std::string& bit_string);
    std::vector<std::bitset<32>> divide_as_32bits_words(const std::bitset<512> &bit_group);

    std::bitset<32> rotate_left(const std::bitset<32> bits, const uint8_t n);
    std::bitset<160> secure_hash(const std::string& message);

    uint32_t f1(const uint32_t& b, const uint32_t& c, const uint32_t& d);
    uint32_t f2(const uint32_t& b, const uint32_t& c, const uint32_t& d);
    uint32_t f3(const uint32_t& b, const uint32_t& c, const uint32_t& d);
    uint32_t f4(const uint32_t& b, const uint32_t& c, const uint32_t& d);

private:
    // Initial value of registers
    uint32_t H0 = 0x67452301;
    uint32_t H1 = 0xEFCDAB89;
    uint32_t H2 = 0x98BADCFE;
    uint32_t H3 = 0x10325476;
    uint32_t H4 = 0xC3D2E1F0;

    const uint8_t word_size = 32;
    const uint8_t round     = 80;
};


#endif //SHA1_SHA1_H
