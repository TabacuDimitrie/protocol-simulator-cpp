# Protocol Simulator (C++)

A C++ project that simulates a simple communication protocol with frame transmission, CRC-based error detection, channel corruption, and retransmission logic.

## Overview

This project was built to explore how data transmission can be validated and retransmitted in the presence of channel errors.

The application includes:
- a C++ backend that simulates the protocol logic
- a lightweight HTTP server using `cpp-httplib`
- a simple HTML/JavaScript interface for testing the simulator from the browser

## Features

- Frame-based message transmission
- CRC validation for error detection
- Simulated noisy channel with configurable error probability
- Retransmission mechanism with configurable retry count
- Browser-based test interface

## Project Structure

- `Frame.*`  
  Handles the frame structure and payload data

- `CRC16.*`  
  Computes CRC values used for transmission validation

- `ChannelSimulator.*`  
  Simulates corruption during transmission based on a chosen error probability

- `server.cpp`  
  Runs the HTTP server and exposes the simulator endpoints

- `index.html`  
  Simple browser interface for sending requests to the simulator

## How It Works

1. The user enters:
   - a message
   - an error probability
   - a maximum number of retries

2. The backend:
   - builds a frame
   - computes the CRC for the payload
   - sends the frame through a simulated noisy channel

3. On reception:
   - the CRC is recalculated
   - the received CRC is compared against the recalculated one

4. If the frame is corrupted:
   - retransmission is attempted until success
   - or until the maximum retry count is reached

## Technologies Used

- C++
- `cpp-httplib`
- HTML
- JavaScript

## Running the Project

Compile:


```g++ server.cpp Frame.cpp CRC16.CPP ChannelSimulator.cpp -o proto.exe -pthread -D_WIN32_WINNT=0x0A00 -lws2_32```

## RUN
```./proto.exe```

#Open in Browser
click on ```http://localhost:8080```

## Notes

The frontend was built using existing HTML/CSS examples as a starting point and adapted for this project.  
The main focus of the implementation is the backend logic and protocol simulation in C++.

##Current Status

This project is still being improved. Possible next steps include:

- more realistic bit-level corruption
- better visualization of corrupted characters
- improved result formatting in the UI
- additional protocol features
