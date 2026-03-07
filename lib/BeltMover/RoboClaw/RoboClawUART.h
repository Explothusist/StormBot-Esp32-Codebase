#pragma once

#include <Arduino.h>
#include <Basicmicro.h>

class RoboClawUART {
public:
    enum STATES {
        PICKUP = 250,
        WHEEL = 4000,
        MIDDROP = 3000,
        TOPDROP = 5600
    };

    // address: packet-serial address configured in Motion Studio (0x80 default).
    RoboClawUART(uint8_t rxPin, uint8_t txPin, uint8_t _address = 0x80);
    void init();
    void setPosition(int position);
    int getPosition();

    void setSpeed(int speed);
    void resetEncoders();

    void move();



private:

    uint8_t address;
    uint32_t defaultTimeoutMs  = 5;
    uint16_t speed = 0;
    uint8_t rxPin, txPin;
    int commandedPosition = 0;

    bool moveCompelte = false;

    const int MAX_HEIGHT = 5750; // Maximum encoder count for the linear slide
    const int MIN_HEIGHT = 300;  // Minimum encoder count to prevent overextension

    //Basicmicro* roboclaw(&Serial1, 10000); // Using Serial1, 10ms timeout
    Basicmicro* roboclaw = nullptr; // Using Serial1, 10ms timeout

    

    // Incremental CRC-16-CCITT (poly 0x1021, init 0) update.
    static uint16_t crc16Update(uint16_t crc, uint8_t dataByte);

    bool readBytesWithTimeout(uint8_t* buffer, size_t length, uint32_t timeoutMs);
};
