

#ifndef STORMBOT_LiftCommand_
#define STORMBOT_LiftCommand_

#include "../Automat/automat.h"
#include "GantryDriver.h"

class LiftCommand : public atmt::Command { // Add more functionality to this, but this is a basic framework
    public:
        LiftCommand(GantryDriver* roboClaw, int position, bool justMove = false, bool absolutePosition = false); // Put subsystems as parameters
        LiftCommand(const LiftCommand& command); // Copy constructor
        ~LiftCommand();
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
};

#endif