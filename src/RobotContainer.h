
#ifndef STORMBOT_CONTAINER_
#define STORMBOT_CONTAINER_

#include "../Automat/automat.h"
#include "Constants.h"

#include "Compressor.h"
#include "BeltMover.h"
#include "Vacuum.h"

class RobotContainer {
    public:
        RobotContainer();
        ~RobotContainer();

        void configure_bindings();

        atmt::Command* getAutonomousCommand();

        Compressor* m_compressor; // public because they are for Robot.cpp
        BeltMover* m_belt_mover;
        Vacuum* m_vacuum;


        atmt::Joystick* m_operator_controller;

        atmt::SerialReader* m_serial_reader;
    private:
};


#endif