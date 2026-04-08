
#ifndef STORMBOT_CONTAINER_
#define STORMBOT_CONTAINER_

#include "../Automat/automat.h"
#include "Constants.h"
#include "storm_serial_utils.h"
#include "stormbot_type.h"

#include "Compressor.h"
#include "Extruder.h"
#include "Vacuum.h"
#include "FastStepperMotor.h"
#include "GantryDriver.h"

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
        Extruder* m_slide;
        Vacuum* m_claw;
        GantryDriver* m_gantryDriver;


#ifdef STORMBOT_ROBOT_DASHBOARD_
        atmt::RobotDashboardServer* m_dashboard;
#endif
        atmt::Joystick* m_operator_controller;
        atmt::SerialReader* m_serial_reader;
        atmt::HeartbeatMaker_StateMatcher* m_heartbeat_sender;
        atmt::Heartbeat* m_joystick_heartbeat;
    private:
};


#endif