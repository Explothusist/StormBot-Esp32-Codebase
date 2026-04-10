
#include "ScoreBatteryBank.h"
#include "GantryCommand.h"
#include "LiftCommand.h"
#include "ExtruderCommand.h"
#include "ClawCommand.h"
#include "Constants.h"


ScoreBatteryBank::ScoreBatteryBank(ScoreBankRow row, ScoreBankSide side, Compressor* Compressor, Extruder* extruder, Vacuum* vacuum, GantryDriver* gantry_driver) {
    addCommand(new GantryCommand(gantry_driver, side == Bank_LeftSide ? consts::gantry::RelativeSetpoint::LeftScore : consts::gantry::RelativeSetpoint::RightScore));
    addCommand(new LiftCommand(gantry_driver, row == Bank_NearRow ? consts::lift::Setpoint_ScoreLow : consts::lift::Setpoint_ScoreHigh, false, true));
    addCommand(new ExtruderCommand(extruder, row == Bank_NearRow ? consts::extruder::MOVEBACKWARD : consts::extruder::MOVEFORWARD));
    addCommand(new atmt::WaitCommand(3.0));
    addCommand(new ClawCommand(vacuum));
    addCommand(new atmt::WaitCommand(0.5));
    addCommand(new ExtruderCommand(extruder, consts::extruder::MOVEBACKWARD));
    addCommand(new atmt::WaitCommand(3.0));
    addCommand(new LiftCommand(gantry_driver, consts::lift::Setpoint_Neutral, false, true));
    addCommand(new GantryCommand(gantry_driver, consts::gantry::RelativeSetpoint::Neutral));
};