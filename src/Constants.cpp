#include "Constants.h"

namespace consts {

    namespace lift {
        // Slide
        int PICKUP = 100;
        int WHEEL = 2000;
        int MIDDROP = 3000;
        int TOPDROP = 4000;
        
        int Setpoint_Intake = 100;
        int Setpoint_Neutral = 3000;
        int Setpoint_ScoreLow = 3000;
        int Setpoint_ScoreHigh = 4000;
        int Setpoint_Wheel = 2000;
    };

    namespace gantry {
        // Gantry
        int INITPOSITION = 0;
        int LOADPOSITIONLEFTA = 2300;
        int LOADPOSITIONLEFTB = 2750;
        int LOADPOSITIONFRONTA = 4400;
        int LOADPOSITIONFRONTB = 5350;
        int LOADPOSITIONRIGHTA = 6450;
        int LOADPOSITIONRIGHTB = 7150;
        
        int Setpoint_Store = 0;
        int Setpoint_Corner01 = 1000;
        int Setpoint_Side1_LeftScore = 2300;
        int Setpoint_Side1_Neutral = 2500;
        int Setpoint_Side1_RightScore = 2750;
        int Setpoint_Corner12 = 3500;
        int Setpoint_Side2_LeftScore = 4400;
        int Setpoint_Side2_Neutral = 4900;
        int Setpoint_Side2_RightScore = 5350;
        int Setpoint_Corner23 = 5900;
        int Setpoint_Side3_LeftScore = 6450;
        int Setpoint_Side3_Neutral = 6600;
        int Setpoint_Side3_RightScore = 7150;
    };

};
