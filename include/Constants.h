
#ifndef STORMBOT_CONSTANTS_
#define STORMBOT_CONSTANTS_

#include <cstdint>





namespace consts {

    namespace robot {
        int const AutonomousLength = 3;
    };

    namespace belt_mover {
        uint8_t const EnPin = 34;
        uint8_t const DirPin = 47;
        uint8_t const StepPin = 33;
        uint8_t const MS1Pin = 0;
        uint8_t const MS2Pin = 0;

        int const Direction_Forward = 1;
        int const Direction_Backward = 0;
    };

    namespace compressor {
        uint8_t const pwmPin1 = 0;
        uint8_t const pwmPin2 = 0;
        uint8_t const enPin1 = 0;
        uint8_t const enPin2 = 0;
    };

    namespace vacuum {
        uint8_t const pwmPin1 = 0;
        uint8_t const pwmPin2 = 0;
        uint8_t const enPin1 = 0;
        uint8_t const enPin2 = 0;
    };

};

#endif