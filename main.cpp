#include <iostream>
#include "Frame.hpp"
#include "CRC16.hpp"
#include "ChannelSimulator.hpp"
#include "Receiver.hpp"

int main() {
    Frame f(1, "Hello");

    unsigned short crcValue = CRC16::compute(f.getPayload());
    f.setCRC(crcValue);

    ChannelSimulator channel(0.0);

    Frame receivedFrame = channel.transmit(f);

    std::cout << "Original payload: " << f.getPayload() << "\n";
    std::cout << "Original CRC: " << f.getCRC() << "\n";

    Receiver receiver;
    receiver.receive(receivedFrame);

    return 0;
}