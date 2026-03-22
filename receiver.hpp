#ifndef RECEIVER_HPP
#define RECEIVER_HPP

#include "Frame.hpp"

class Receiver {
public:
    bool receive(const Frame& frame);
};

#endif