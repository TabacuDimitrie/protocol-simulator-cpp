#include <iostream>
#include "Receiver.hpp"
#include "CRC16.hpp"

bool Receiver::receive(const Frame& frame) {
    unsigned short recalculatedCRC = CRC16::compute(frame.getPayload());

    std::cout << "Received payload: " << frame.getPayload() << "\n";
    std::cout << "Received CRC: " << frame.getCRC() << "\n";
    std::cout << "Recalculated CRC: " << recalculatedCRC << "\n";

    if (recalculatedCRC == frame.getCRC()) {
        std::cout << "Frame valid\n";
        return true;
    } else {
        std::cout << "Frame corrupted\n";
        return false;
    }
}