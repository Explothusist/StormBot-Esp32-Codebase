
#ifndef STORMBOT_ScoreBatteryBank_
#define STORMBOT_ScoreBatteryBank_

#include "../Automat/automat.h"
#include "Compressor.h"
#include "Extruder.h"
#include "Vacuum.h"
#include "GantryDriver.h"

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
        ScoreBatteryBank(ScoreBankRow row, ScoreBankSide side, Compressor* Compressor, Extruder* slide, Vacuum* vacuum, GantryDriver gantry_driver);
        
    private:
};

#endif