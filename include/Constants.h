
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
        int const RXPin = 16;
        int const TXPin = 17;
    };

    namespace heartbeat {
        int const SenderTimeoutMS = 500;
    };

    namespace belt_mover {
        uint8_t const PWM1 = 36;
        uint8_t const PWM2 = 39;

        int const FORWARDSPEED = 140;
        int const BACKWARDSPEED = -140;
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
    };

    namespace robo_claw {
        uint8_t const rxPin = 41;
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

        uint8_t const MOTOR1 = 0;
        uint8_t const MOTOR2 = 1;

        
    };

};

#endif