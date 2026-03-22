#include "CRC16.hpp"

unsigned short CRC16::compute(const std::string& data) {
    unsigned short sum = 0;

    for (char c : data) {
        sum += (unsigned char)c;
    }

    return sum;
}