
#ifndef STORMBOT_ScoreBatteryBank_
#define STORMBOT_ScoreBatteryBank_

#include "../Automat/automat.h"
#include "Compressor.h"
#include "BeltMover.h"
#include "Vacuum.h"
#include "RoboClawUART.h"

typedef enum {
    Bank_LeftSide,
    Bank_RightSide
} ScoreBankSide;
typedef enum {
    Bank_FarRow,
    Bank_NearRow
} ScoreBankRow;

class ScoreBatteryBank : public atmt::SequentialCommandGroup {
    public:
        ScoreBatteryBank(ScoreBankRow row, ScoreBankSide side, Compressor* Compressor, BeltMover* belt_mover, Vacuum* vacuum, RoboClawUART robo_claw);
        
    private:
};

#endif