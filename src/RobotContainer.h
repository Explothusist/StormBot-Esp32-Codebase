#pragma once

#include "Automat/automat.h"
#include "BeltMover.h"
#include "Compressor.h"
#include "Vacuum.h"
#include "EspNowEZ.h"

#include "DCMotor.h"

class RobotContainer {
    public:
        RobotContainer();
        ~RobotContainer();

        void configure_bindings();

        atmt::Command* getAutonomousCommand();

        Compressor* m_compressor;
        Vacuum* m_vacuumPump;
        BeltMover* m_beltMover;

        DcMotor* m_motor; // As example only

        atmt::Joystick* m_operator_controller;
};