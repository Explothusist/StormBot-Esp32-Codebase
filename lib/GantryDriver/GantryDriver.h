#ifndef GantryDriver_H
#define GantryDriver_H

#include <Arduino.h>
#include <Basicmicro.h>
#include "../Automat/command_based/Subsystem.h"
#include "Constants.h"


class GantryDriver : public atmt::Subsystem {
public:
    //enum STATES {
    //    PICKUP = 150,
    //    WHEEL = 4000,
    //    MIDDROP = 3000,
    //    TOPDROP = 5000
    //};


    int Roboclaw_Positions_Linear[4] = {consts::gantry_driver::PICKUP, consts::gantry_driver::MIDDROP, consts::gantry_driver::TOPDROP, consts::gantry_driver::WHEEL}; // Pickup, Wheel, MidDrop, TopDrop
    int Roboclaw_Positions_Load[6] = {consts::gantry_driver::LOADPOSITIONLEFTA, consts::gantry_driver::LOADPOSITIONLEFTB, consts::gantry_driver::LOADPOSITIONFRONTA, consts::gantry_driver::LOADPOSITIONFRONTB, consts::gantry_driver::LOADPOSITIONRIGHTA, consts::gantry_driver::LOADPOSITIONRIGHTB}; // Load positions
    // address: packet-serial address configured in Motion Studio (0x80 default).
    GantryDriver(uint8_t rxPin, uint8_t txPin, uint8_t _address = 0x80);
    
    void init() override;
    void systemPeriodic() override;
    void disabledPeriodic() override;
    void autonomousPeriodic() override;
    void teleopPeriodic() override;

    void setPosition(int motor,int position);
    int getPosition(int motor); 

    void setSpeed(int motor, int speed);
    void resetEncoders();

    void move(int motor);
    void justMove(int motor, int direction);
    bool moveComplete = false;
    int positionElement[2] = {0, 0}; //1,2,3,4

private:

    uint8_t address;
    uint32_t defaultTimeoutMs  = 5;
    uint16_t speed[2] = {consts::gantry_driver::SLIDESPEED, consts::gantry_driver::GANTRYSPEED};
    int foundZeros[2] = {0, 0};
    uint8_t rxPin, txPin;
    int commandedPosition[2] = {0, 0};
    bool jogging = false;

    

   

    const int MAX_HEIGHT[2] = { consts::gantry_driver::TOPDROP, consts::gantry_driver::LOADPOSITIONRIGHTB }; // Maximum encoder count for the linear slide
    const int MIN_HEIGHT[2] = {consts::gantry_driver::PICKUP, consts::gantry_driver::LOADPOSITIONLEFTA};  // Minimum encoder count to prevent overextension

    //Basicmicro* roboclaw(&Serial1, 10000); // Using Serial1, 10ms timeout
    Basicmicro* roboclaw = nullptr; // Using Serial1, 10ms timeout

    

    // Incremental CRC-16-CCITT (poly 0x1021, init 0) update.
    static uint16_t crc16Update(uint16_t crc, uint8_t dataByte);

    bool readBytesWithTimeout(uint8_t* buffer, size_t length, uint32_t timeoutMs);
};

#endif // GantryDriver_H
