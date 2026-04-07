

#ifndef STORMBOT_ROBOCLAWCOMMAND_
#define STORMBOT_ROBOCLAWCOMMAND_

#include "../Automat/automat.h"
#include "RoboClawUART.h"

class RoboClawCommand : public atmt::Command { // Add more functionality to this, but this is a basic framework
    public:
        RoboClawCommand(RoboClawUART* roboClaw,int motor, int position, bool justMove = false); // Put subsystems as parameters
        RoboClawCommand(const RoboClawCommand& command); // Copy constructor
        ~RoboClawCommand();
        atmt::Command* cloneSelf() const override;

        void initialize() override; // User-made
        void execute() override; // User-made
        void end(bool interrupted) override; // User-made
        bool is_finished() override; // User-made

        // void toggleClaw( ); // Illegal
        
    private:
        RoboClawUART* m_roboClaw;
        int m_position;
        int m_motor;
        bool m_justMove;
};

#endif