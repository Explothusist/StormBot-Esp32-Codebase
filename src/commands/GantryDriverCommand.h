

#ifndef STORMBOT_GantryDriverCommand_
#define STORMBOT_GantryDriverCommand_

#include "../Automat/automat.h"
#include "GantryDriver.h"

class GantryDriverCommand : public atmt::Command { // Add more functionality to this, but this is a basic framework
    public:
        GantryDriverCommand(GantryDriver* roboClaw,int motor, int position, bool justMove = false, bool absolutePosition = false); // Put subsystems as parameters
        GantryDriverCommand(const GantryDriverCommand& command); // Copy constructor
        ~GantryDriverCommand();
        atmt::Command* cloneSelf() const override;

        void initialize() override; // User-made
        void execute() override; // User-made
        void end(bool interrupted) override; // User-made
        bool is_finished() override; // User-made

        // void toggleClaw( ); // Illegal
        
    private:
        GantryDriver* m_roboClaw;
        int m_position;
        int m_motor;
        bool m_justMove;
        bool m_absolutePosition;
};

#endif