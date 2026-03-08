
#ifndef STORMBOT_BELTCOMMAND_
#define STORMBOT_BELTCOMMAND_

#include "../Automat/automat.h"
#include "BeltMover.h"

class BeltCommand : public atmt::Command { // Add more functionality to this, but this is a basic framework
    public:
        BeltCommand(BeltMover* belt_mover, int direction); // Put subsystems as parameters
        BeltCommand(BeltCommand& command); // Copy constructor
        ~BeltCommand();
        atmt::Command* clone() const override;

        void initialize() override; // User-made
        void execute() override; // User-made
        void end(bool interrupted) override; // User-made
        bool is_finished() override; // User-made

        void moveLeft(bool direction, int distance); 
        void moveRight(bool direction, int distance);
        
    private:
        BeltMover* m_belt_mover;
        int m_direction;
};

#endif