#pragma once

#include <Arduino.h>
#include <Basicmicro.h>
#include "../Automat/command_based/Subsystem.h"

class RoboClawUART : public atmt::Subsystem {
public:
    enum STATES {
        PICKUP = 250,
        WHEEL = 4000,
        MIDDROP = 3000,
        TOPDROP = 5600
    };


    int Roboclaw_Positions[4] = {250, 1000, 2000, 3000}; // Pickup, Wheel, MidDrop, TopDrop
    // address: packet-serial address configured in Motion Studio (0x80 default).
    RoboClawUART(uint8_t rxPin, uint8_t txPin, uint8_t _address = 0x80);
    
    void init() override;
    void periodic() override;

    void setPosition(int position);
    int getPosition();

    void setSpeed(int speed);
    void resetEncoders();

    void move();

    bool moveComplete = false;
    int positionElement = 0; //1,2,3,4

private:

    uint8_t address;
    uint32_t defaultTimeoutMs  = 5;
    uint16_t speed = 32;
    uint8_t rxPin, txPin;
    int commandedPosition = 0;

    

   

    const int MAX_HEIGHT = 4000; // Maximum encoder count for the linear slide
    const int MIN_HEIGHT = 250;  // Minimum encoder count to prevent overextension

    //Basicmicro* roboclaw(&Serial1, 10000); // Using Serial1, 10ms timeout
    Basicmicro* roboclaw = nullptr; // Using Serial1, 10ms timeout

    

    // Incremental CRC-16-CCITT (poly 0x1021, init 0) update.
    static uint16_t crc16Update(uint16_t crc, uint8_t dataByte);

    bool readBytesWithTimeout(uint8_t* buffer, size_t length, uint32_t timeoutMs);
};
