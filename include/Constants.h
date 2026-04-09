
#pragma once
#ifndef STORMBOT_CONSTANTS_
#define STORMBOT_CONSTANTS_

#include <cstdint>
#include "storm_serial_utils.h"




namespace consts {

    namespace robot {
        int const AutonomousLength = 3;
    };

    namespace serial {
        int const SerialAddress = Address_EspBot;
        int const RXPin = 33;
        int const TXPin = 47;
    };

    namespace heartbeat {
        int const SenderTimeoutMS = 200;
        int const JoystickTimeoutMS = 450; // +300 (450)
    };

    namespace slide {
        uint8_t const PWM1 = 36;
        uint8_t const PWM2 = 39;

        int const FORWARDSPEED = 140;
        int const BACKWARDSPEED = -140;


        int const MOVEFORWARD = 1;
        int const MOVEBACKWARD = -1;
        int const STOP = 0;


    };

    namespace compressor {
        uint8_t const pwmPin1 = 0;
        uint8_t const pwmPin2 = 0;
        uint8_t const enPin1 = 0;
        uint8_t const enPin2 = 0;
    };

    namespace vacuum {
        uint8_t const pwmPin1 = 45;
        uint8_t const pwmPin2 = 0;
        uint8_t const enPin1 = 0;
        uint8_t const enPin2 = 0;
        uint8_t const speed = 160;
    };

    namespace gantry_driver {
        uint8_t const rxPin = 48;
        uint8_t const txPin = 40;

        uint8_t const address = 0x80; // Default address for RoboClaw

        extern int PICKUP;
        extern int WHEEL;
        extern int MIDDROP;
        extern int TOPDROP;

        extern int INITPOSITION;
        extern int LOADPOSITIONLEFTA;
        extern int LOADPOSITIONLEFTB;
        extern int LOADPOSITIONFRONTA;
        extern int LOADPOSITIONFRONTB; 
        extern int LOADPOSITIONRIGHTA;
        extern int LOADPOSITIONRIGHTB;

        uint8_t const SLIDEMOTOR = 0;
        uint8_t const GANTRYMOTOR = 1;

        uint8_t const SLIDESPEED = 2500;
        uint8_t const GANTRYSPEED = 25;

        int const MOVEUPPOSITION = 1;
        int const MOVEDOWNPOSITION = -1;

        int const FORWARDVELOCITY = 1;
        int const BACKWARDVELOCITY = -1;
        int const STOP = 0;

        bool const POSITIONMOVE = false;
        bool const VELOCITYMOVE = true;
        
    };

};

#endif