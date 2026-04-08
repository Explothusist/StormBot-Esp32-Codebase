
#ifndef STORMBOT_ExtruderCommand_
#define STORMBOT_ExtruderCommand_

#include "../Automat/automat.h"
#include "Extruder.h"

class ExtruderCommand : public atmt::Command { // Add more functionality to this, but this is a basic framework
    public:
        ExtruderCommand(Extruder* slide, int direction); // Put subsystems as parameters
        ExtruderCommand(Extruder* slide, int direction, bool isIncremental);
        ExtruderCommand(const ExtruderCommand& command); // Copy constructor
        ~ExtruderCommand();
        atmt::Command* cloneSelf() const override;

        void initialize() override; // User-made
        void execute() override; // User-made
        void end(bool interrupted) override; // User-made
        bool is_finished() override; // User-made


    private:
        Extruder* m_slide;
        int m_direction;
        bool m_isIncremental = false; // Whether this command is for a small incremental move or a full move to the left or right
};

#endif