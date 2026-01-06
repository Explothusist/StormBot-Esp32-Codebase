#pragma once

#include "../Automat/Command.h"
#include "DCMotor.h"

class ExampleCommand : public atmt::Command {
    public:
        ExampleCommand(DcMotor* motor, int speed, int speed_shift);
        ExampleCommand(ExampleCommand& command);
        ~ExampleCommand();

        void initialize() override; // User-made
        void execute() override; // User-made
        void end(bool interrupted) override; // User-made
        bool is_finished() override; // User-made
        
    private:
        DcMotor* m_motor;

        int m_speed;
        int m_speed_shift;
        int m_counter;
};