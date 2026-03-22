#pragma once
#include "Frame.hpp"

class ChannelSimulator {
private:
    double errorProbability; 

public:
    ChannelSimulator();
    ChannelSimulator(double errorProb);

    void setErrorProbability(double errorProb);
    double getErrorProbability() const;

    Frame transmit(const Frame& frame) const; 
};
