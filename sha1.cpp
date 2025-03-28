//
// Created by ozgur on 3/28/2025.
//

#include "sha1.h"

std::string sha1::add_padding(const std::string& bit_string)
{
    size_t message_length = bit_string.length();
    size_t k = (448 - (message_length + 1)) % 512;  // 448-bit sınırına tamamla

    std::string padded_message = bit_string + "1" + std::string(k, '0');
    padded_message += std::bitset<64>(message_length).to_string();

    return padded_message;
}

std::bitset<8> sha1::char_to_byte(const char& c)
{
    std::bitset<8> c_to_byte(c);
    return c_to_byte;
}

std::string sha1::message_to_bit(const std::string& message)
{
    std::string bit_string{};
    for(auto c : message)
    {
        bit_string += char_to_byte(c).to_string();
    }

    return bit_string;
}

std::vector<std::bitset<512>> sha1::split_512bit_groups(const std::string& bit_string)
{
    std::vector<std::bitset<512>> bit_groups{};
    int group_size = 512;


    for (int i = 0; i < bit_string.length(); i += group_size)
    {
        std::string group = bit_string.substr(i, group_size);

        if (group.length() < group_size)
        {
            group = add_padding(group);
        }

        std::bitset<512> bitset(group);
        bit_groups.push_back(bitset);
    }

    return bit_groups;
}

std::bitset<160> sha1::secure_hash(const std::string& message)
{
    std::string bit_string = message_to_bit(message);
    bit_string = add_padding(bit_string);

    std::vector<std::bitset<512>> bit_blocks = split_512bit_groups(bit_string);

    uint32_t A = H0;
    uint32_t B = H1;
    uint32_t C = H2;
    uint32_t D = H3;
    uint32_t E = H4;

    for (const auto& block : bit_blocks)
    {
        std::vector<std::bitset<32>> words = divide_as_32bits_words(block);  // 80 Word oluşturuluyor

        uint32_t a = A, b = B, c = C, d = D, e = E;

        for (int i = 0; i < 80; ++i)
        {
            uint32_t f, k;
            if (i < 20)         { f = f1(b, c, d); k = 0x5A827999; }
            else if (i < 40)    { f = f2(b, c, d); k = 0x6ED9EBA1; }
            else if (i < 60)    { f = f3(b, c, d); k = 0x8F1BBCDC; }
            else                { f = f4(b, c, d); k = 0xCA62C1D6; }

            uint32_t temp = rotate_left(std::bitset<32>(a), 5).to_ulong() + f + e + k + words[i].to_ulong();

            e = d;
            d = c;
            c = rotate_left(b, 30).to_ulong();
            b = a;
            a = temp;
        }

        A += a;
        B += b;
        C += c;
        D += d;
        E += e;
    }

    std::bitset<160> hash_value;
    hash_value |= (std::bitset<160>(A) << 128);
    hash_value |= (std::bitset<160>(B) << 96);
    hash_value |= (std::bitset<160>(C) << 64);
    hash_value |= (std::bitset<160>(D) << 32);
    hash_value |= std::bitset<160>(E);
    return hash_value;
}

std::vector<std::bitset<32>> sha1::divide_as_32bits_words(const std::bitset<512> &bit_group)
{
    // Size should be as 80
    std::vector<std::bitset<32>> word_list{};

    for (int i = 0; i < bit_group.size(); i += word_size)
    {
        std::string group = bit_group.to_string().substr(i, word_size);

        if (group.length() < word_size)
        {
            group = add_padding(group);
        }

        std::bitset<32> bitset(group);
        word_list.push_back(bitset);
    }

    for (int i = 16; i < round; ++i)
    {

        std::bitset<32> w = rotate_left((word_list[i-16] ^ word_list[i-14] ^ word_list[i-8] ^ word_list[i-3]), 1);
        word_list.push_back(w);
    }

    return word_list;
}

std::bitset<32> sha1::rotate_left(const std::bitset<32> bits, const uint8_t n)
{
    return (bits << n) | (bits >> (32 - n));
}

uint32_t sha1::f1(const uint32_t &b, const uint32_t &c, const uint32_t &d) { return (b & c) | (~b & d); }
uint32_t sha1::f2(const uint32_t &b, const uint32_t &c, const uint32_t &d) { return b ^ c ^ d; }
uint32_t sha1::f3(const uint32_t &b, const uint32_t &c, const uint32_t &d) { return (b & c) | (b & d) | (c & d); }
uint32_t sha1::f4(const uint32_t &b, const uint32_t &c, const uint32_t &d) { return b ^ c ^ d; }