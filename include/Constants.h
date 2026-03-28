
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
    }

    namespace belt_mover {
        uint8_t const EnPin = 34;
        uint8_t const DirPin = 47;
        uint8_t const StepPin = 33;
        uint8_t const MS1Pin = 0;
        uint8_t const MS2Pin = 0;

        static constexpr int FAST      = 150;
        static constexpr int MEDIUM    = 300;
        static constexpr int SLOW      = 600;
        static constexpr int SUPERSLOW = 1000;

        static constexpr int INITPOS = 2000; // Amount of steps to get out of inital poisition

        static constexpr int TURNSTEPS = 1500; // Inital steps to match corner movements

        static constexpr int LEFTRIGHTMOVE = 500; // Adjust to be moved left or giht
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

        
    };

};

#endif