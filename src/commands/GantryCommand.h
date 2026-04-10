

#ifndef STORMBOT_GantryCommand_
#define STORMBOT_GantryCommand_

#include "../Automat/automat.h"
#include "GantryDriver.h"

class GantryCommand : public atmt::Command { // Add more functionality to this, but this is a basic framework
    public:
        GantryCommand(GantryDriver* roboClaw, int position, bool justMove = false, bool absolutePosition = false); // Put subsystems as parameters
        GantryCommand(GantryDriver* roboClaw, consts::gantry::RelativeSetpoint relative_setpoint); // Put subsystems as parameters
        GantryCommand(const GantryCommand& command); // Copy constructor
        ~GantryCommand();
        atmt::Command* cloneSelf() const override;

        void initialize() override; // User-made
        void execute() override; // User-made
        void end(bool interrupted) override; // User-made
        bool is_finished() override; // User-made

        // void toggleClaw( ); // Illegal
        
    private:
        GantryDriver* m_gantryDriver;
        int m_position;
        bool m_justMove;
        bool m_absolutePosition;
        bool m_relativeAbsolute;
        consts::gantry::RelativeSetpoint m_relative_setpoint;
};

#endif