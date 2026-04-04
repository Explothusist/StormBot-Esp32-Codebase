
#ifndef STORMBOT_CONTAINER_
#define STORMBOT_CONTAINER_

#include "../Automat/automat.h"
#include "Constants.h"
#include "storm_serial_utils.h"
#include "stormbot_type.h"

#include "Compressor.h"
#include "BeltMover.h"
#include "Vacuum.h"
#include "FastStepperMotor.h"
#include "RoboClawUART.h"

class RobotContainer {
    public:
        RobotContainer();
        ~RobotContainer();

        void configure_auto_bindings();
        void configure_bindings();

        // atmt::Command* getAutonomousCommand();
        static atmt::Command* getAutonomousCommand(int indicator, void* robot_container);
        static int getWhichAutonomousRoutine(void* robot_container);

        Compressor* m_compressor; // public because they are for Robot.cpp
        BeltMover* m_belt_mover;
        Vacuum* m_vacuum;
        RoboClawUART* m_roboClaw;


#ifdef STORMBOT_ROBOT_DASHBOARD_
        atmt::RobotDashboardServer* m_dashboard;
#endif
        atmt::Joystick* m_operator_controller;
        atmt::SerialReader* m_serial_reader;
        atmt::HeartbeatMaker_StateMatcher* m_heartbeat_sender;
    private:
};


#endif