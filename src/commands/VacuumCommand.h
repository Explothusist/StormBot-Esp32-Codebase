
#ifndef STORMBOT_VACUUMCOMMAND_
#define STORMBOT_VACUUMCOMMAND_

#include "../Automat/automat.h"
#include "Vacuum.h"

class VacuumCommand : public atmt::Command { // Add more functionality to this, but this is a basic framework
    public:
        VacuumCommand(Vacuum* vacuum); // Put subsystems as parameters
        VacuumCommand(VacuumCommand& command); // Copy constructor
        ~VacuumCommand();
        atmt::Command* clone() const override;

        void initialize() override; // User-made
        void execute() override; // User-made
        void end(bool interrupted) override; // User-made
        bool is_finished() override; // User-made

        void toggleClaw( );
        
    private:
        Vacuum* m_vacuum;
        int m_direction;
};

#endif