#include <sstream>
#include "sha1.h"

int main()
{
    sha1 s1;

    std::stringstream ss;

    for (size_t i = 0; i < 160; i += 4)
    {
        std::bitset<4> nibble(s1.secure_hash("abclfkhdjfgsd<xjchçöxgnvd<<zfgxhcçjögnbv").to_string().substr(i, 4));
        ss << std::hex << nibble.to_ulong();
    }

    std::cout << "SHA-1 Hash (Hex): " << ss.str() << std::endl;


    return 0;
}