#include "Frame.hpp"

Frame::Frame() {
    sequenceNumber = 0;
    payload = "";
    crc = 0;
}

Frame::Frame(int seq, const std::string& data) {
    sequenceNumber = seq;
    payload = data;
    crc = 0;
}

int Frame::getSequenceNumber() const {
    return sequenceNumber;
}

std::string Frame::getPayload() const {
    return payload;
}

unsigned short Frame::getCRC() const {
    return crc;
}

void Frame::setSequenceNumber(int seq) {
    sequenceNumber = seq;
}

void Frame::setPayload(const std::string& payload) {
    this->payload = payload;
}

void Frame::setCRC(unsigned short value) {
    crc = value;
}