
#ifndef STORMBOT_BELTCOMMAND_
#define STORMBOT_BELTCOMMAND_

#include "../Automat/automat.h"
#include "BeltMover.h"

class BeltCommand : public atmt::Command { // Add more functionality to this, but this is a basic framework
    public:
        BeltCommand(BeltMover* belt_mover, int direction); // Put subsystems as parameters
        BeltCommand(BeltMover* belt_mover, int direction, bool isIncremental);
        BeltCommand(BeltCommand& command); // Copy constructor
        ~BeltCommand();
        atmt::Command* clone() const override;

        void initialize() override; // User-made
        void execute() override; // User-made
        void end(bool interrupted) override; // User-made
        bool is_finished() override; // User-made

        void incrementalMove(int direction); // For small adjustments, moves a small amount in the specified direction (true for left, false for right)
        
    private:
        BeltMover* m_belt_mover;
        int m_direction;
        bool m_isIncremental = false; // Whether this command is for a small incremental move or a full move to the left or right
};

#endif