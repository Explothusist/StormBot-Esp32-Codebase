
#ifndef STORMBOT_ClawCommand_
#define STORMBOT_ClawCommand_

#include "../Automat/automat.h"
#include "Vacuum.h"

class ClawCommand : public atmt::Command { // Add more functionality to this, but this is a basic framework
    public:
        ClawCommand(Vacuum* vacuum); // Put subsystems as parameters
        ClawCommand(Vacuum* vacuum, consts::claw::ClawPosition position); // Put subsystems as parameters
        ClawCommand(const ClawCommand& command); // Copy constructor
        ~ClawCommand();
        atmt::Command* cloneSelf() const override;

        void initialize() override; // User-made
        void execute() override; // User-made
        void end(bool interrupted) override; // User-made
        bool is_finished() override; // User-made

        void toggleClaw( );
        
    private:
        Vacuum* m_claw;
        consts::claw::ClawPosition m_position;
        bool m_is_toggle;
};

#endif