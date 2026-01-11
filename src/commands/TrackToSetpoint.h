#pragma once

#include "../Automat/Command.h"
#include "StepperMotor.h"

class TrackToSetpoint : public atmt::Command {
    public:
        TrackToSetpoint(StepperMotor* stepper, int setpoint);
        TrackToSetpoint(TrackToSetpoint& command);
        ~TrackToSetpoint();

        void initialize() override; // User-made
        void execute() override; // User-made
        void end(bool interrupted) override; // User-made
        bool is_finished() override; // User-made
        
    private:
        StepperMotor* m_stepper;
        
        int m_setpoint;
};