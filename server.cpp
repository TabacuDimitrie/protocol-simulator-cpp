#define _WIN32_WINNT 0x0A00
#define WINVER 0x0A00
#define CPPHTTPLIB_USE_POLL

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <stdexcept>

#include "httplib.h"
#include "Frame.hpp"
#include "CRC16.hpp"
#include "ChannelSimulator.hpp"

using namespace httplib;
using namespace std;

int main() {
    Server svr;

    svr.set_default_headers({
        {"Access-Control-Allow-Origin", "*"}
    });

    svr.Get("/", [](const Request& req, Response& res) {
        ifstream file("index.html");
        if (!file.is_open()) {
            res.status = 404;
            res.set_content("Nu gasesc index.html", "text/plain");
            return;
        }

        stringstream buffer;
        buffer << file.rdbuf();
        res.set_content(buffer.str(), "text/html");
    });

    svr.Get("/simulate", [](const Request& req, Response& res) {
        try {
            if (!req.has_param("msg") || !req.has_param("err") || !req.has_param("retry")) {
                res.set_content("Lipsesc parametri.", "text/plain");
                return;
            }

            string msg = req.get_param_value("msg");
            string errStr = req.get_param_value("err");
            string retryStr = req.get_param_value("retry");

            if (msg.empty() || errStr.empty() || retryStr.empty()) {
                res.set_content("Completeaza toate campurile.", "text/plain");
                return;
            }

            double errorProbability = stod(errStr);
            int maxRetries = stoi(retryStr);

            if (errorProbability < 0.0) errorProbability = 0.0;
            if (errorProbability > 1.0) errorProbability = 1.0;
            if (maxRetries < 1) maxRetries = 1;

            Frame originalFrame(1, msg);
            unsigned short originalCRC = CRC16::compute(originalFrame.getPayload());
            originalFrame.setCRC(originalCRC);

            ChannelSimulator channel(errorProbability);

            ostringstream out;
            out << "Mesaj original: " << originalFrame.getPayload() << "\n";
            out << "CRC original: " << originalFrame.getCRC() << "\n";
            out << "Probabilitate eroare: " << errorProbability << "\n";
            out << "Numar incercari: " << maxRetries << "\n\n";

            bool success = false;
            int attemptsUsed = 0;

            for (int attempt = 1; attempt <= maxRetries; attempt++) {
                Frame receivedFrame = channel.transmit(originalFrame);
                unsigned short recalculatedCRC = CRC16::compute(receivedFrame.getPayload());
                bool valid = (recalculatedCRC == receivedFrame.getCRC());

                attemptsUsed = attempt;

                out << "Attempt " << attempt << ":\n";
                out << "Payload primit: " << receivedFrame.getPayload() << "\n";
                out << "CRC primit: " << receivedFrame.getCRC() << "\n";
                out << "CRC recalculat: " << recalculatedCRC << "\n";
                out << "Status: " << (valid ? "VALID" : "CORRUPTED") << "\n\n";

                if (valid) {
                    success = true;
                    break;
                }
            }

            out << "Rezultat final: ";
            if (success) {
                out << "transmisie reusita dupa " << attemptsUsed << " attempt(s).\n";
            } else {
                out << "transmisie esuata dupa " << attemptsUsed << " attempt(s).\n";
            }

            res.set_content(out.str(), "text/plain");
        } catch (const exception& e) {
            res.set_content(string("Eroare server: ") + e.what(), "text/plain");
        }
    });

    cout << "Server running on http://localhost:8080\n";
    svr.listen("localhost", 8080);

    return 0;
}