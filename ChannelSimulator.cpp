#include "ChannelSimulator.hpp"
#include <random>
#include <string>

ChannelSimulator::ChannelSimulator() {
    errorProbability = 0.0;
}

ChannelSimulator::ChannelSimulator(double prob) {
    errorProbability = prob;
}

void ChannelSimulator::setErrorProbability(double prob) {
    errorProbability = prob;
}

double ChannelSimulator::getErrorProbability() const {
    return errorProbability;
}

Frame ChannelSimulator::transmit(const Frame& frame) const {
    Frame result = frame;

    static std::random_device rd;
    static std::mt19937 gen(rd());

    std::uniform_real_distribution<> probDist(0.0, 1.0);

    if (probDist(gen) < errorProbability) {
        std::string corruptedPayload = result.getPayload();

        if (!corruptedPayload.empty()) {
            std::uniform_int_distribution<> numErrDist(1, 3);
            int numErrors = numErrDist(gen);

            std::uniform_int_distribution<> posDist(0, (int)corruptedPayload.size() - 1);

            static const std::string charset =
                "abcdefghijklmnopqrstuvwxyz"
                "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                "0123456789";

            for (int i = 0; i < numErrors; i++) {
                int pos = posDist(gen);

                char newChar;
                do {
                    newChar = charset[gen() % charset.size()];
                } while (newChar == corruptedPayload[pos]);

                corruptedPayload[pos] = newChar;
            }
        }

        result.setPayload(corruptedPayload);
    }

    return result;
}