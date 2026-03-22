#pragma once
#include <string>

class Frame {
private:
    int sequenceNumber;
    std::string payload;
    unsigned short crc;

public:
    Frame();
    Frame(int seq, const std::string& data);

    int getSequenceNumber() const;
    std::string getPayload() const;
    unsigned short getCRC() const;

    void setSequenceNumber(int seq);
    void setPayload(const std::string& data);
    void setCRC(unsigned short value);
};