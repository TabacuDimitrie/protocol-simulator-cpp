#pragma once
#include <string>

class CRC16 {
public:
    static unsigned short compute(const std::string& data);
};