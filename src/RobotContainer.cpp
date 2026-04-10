
#include "RobotContainer.h"
#include "wifi_network.h"

#include <vector>

// #include "commands/BeltCommand.h"
// #include "commands/VacuumCommand.h"
// #include "commands/RoboClawCommand.h"   
#include "commands/SendSerialResumeCommand.h"
#include "commands/WaitForSerialResumeCommand.h"

#include "commands/SendSerialResumeCommand.h"
#include "commands/WaitForSerialResumeCommand.h"

#include "commands/ExtruderCommand.h"
#include "commands/ClawCommand.h"
#include "commands/GantryCommand.h"
#include "commands/LiftCommand.h"
#include "commands/ScoreBatteryBank.h"

RobotContainer::RobotContainer():
    m_slide{ new Extruder(consts::extruder::PWM1, consts::extruder::PWM2) },
    m_compressor{ new Compressor(consts::compressor::pwmPin1, consts::compressor::pwmPin2, consts::compressor::enPin1, consts::compressor::enPin2) },
    m_claw{ new Vacuum(consts::claw::pwmPin1, consts::claw::pwmPin2, consts::claw::enPin1, consts::claw::enPin2) },
    m_gantryDriver{ new GantryDriver(consts::gantry_driver::rxPin, consts::gantry_driver::txPin, consts::gantry_driver::address) },
#ifdef STORMBOT_ROBOT_DASHBOARD_
    m_dashboard{ new atmt::RobotDashboardServer("STORM_Esp32_MainBot", WIFI_SSID, WIFI_PASSWORD) },
#endif
    m_operator_controller{ new atmt::Joystick(atmt::PollMode_Manual) },
    m_serial_reader{ new atmt::SerialReader(atmt::Interface_Serial2, consts::serial::SerialAddress, consts::serial::RXPin, consts::serial::TXPin) },
    m_heartbeat_sender{ new atmt::HeartbeatMaker_StateMatcher(consts::heartbeat::SenderTimeoutMS, m_serial_reader, Serial_Heartbeat) },
    m_joystick_heartbeat{ new atmt::Heartbeat(consts::heartbeat::JoystickTimeoutMS) }
{

};
RobotContainer::~RobotContainer() { // Subsystems deleted by atmt::TimedRobot

};


void RobotContainer::configure_auto_bindings() {
    atmt::platform_print("Configuring Auto Bindings\n");
    m_operator_controller->bindAutoTrigger(
        // (new atmt::Trigger(atmt::AButton, atmt::ButtonPressed))->inMode(atmt::ModeAnyAndAll) // Automat overrides inMode internall on AutoTriggers
        new atmt::Trigger(atmt::AButton, atmt::ButtonPressed)
    );
    m_operator_controller->bindTeleopTrigger(
        // (new atmt::Trigger(atmt::AButton, atmt::ButtonPressed))->inMode(atmt::ModeAnyAndAll) // Automat overrides inMode internall on AutoTriggers
        new atmt::Trigger(atmt::R1Button, atmt::ButtonPressed)
    );
};
void RobotContainer::configure_bindings() {
     //m_driver_controller->bindKey(atmt::AButton, atmt::ButtonPressed, atmt::WhileTrigger, new ApproachAndAlign(m_drivetrain, m_camera_reader));
    // m_driver_controller->bindKey(atmt::R1Button, atmt::ButtonPressed, atmt::WhileTrigger, new AlignAndPounce(m_drivetrain, m_camera_reader));
    
    // m_drivetrain->setDefaultCommand(new TeleopDriveCommand(m_drivetrain, m_driver_controller));
    
    // AButton is autonomous mode.

    //Automated mode is going to be only wheel spinning - 
    /*
    m_operator_controller->bindKey(
        (new atmt::Trigger(atmt::BButton, atmt::ButtonPressed))->inMode(atmt::ModeTeleopAndAuto),
        new ClawCommand(m_claw)
        //new ExtruderCommand(m_slide, consts::lift::Direction_Forward)
    );
    */
    std::shared_ptr<atmt::Trigger> inRegularControllerMode = std::shared_ptr<atmt::Trigger>(new atmt::Trigger(atmt::RightButton, atmt::ButtonReleased));
    std::shared_ptr<atmt::Trigger> inManualControllerMode = std::shared_ptr<atmt::Trigger>(new atmt::Trigger(atmt::RightButton, atmt::ButtonPressed));
    
    m_operator_controller->bindKey(
        (new atmt::Trigger(atmt::LeftButton, atmt::ButtonPressed))->inMode(atmt::ModeTeleopOnly)->setCriteria(inManualControllerMode),
        new ClawCommand(m_claw)
    );

    /*
    m_operator_controller->bindKey(
        (new atmt::Trigger(atmt::BButton, atmt::ButtonPressed))->inMode(atmt::ModeTeleopOnly),
        new ClawCommand(m_claw)
    );
    */
    m_operator_controller->bindKey(
        (new atmt::Trigger(atmt::AButton, atmt::ButtonPressed))->inMode(atmt::ModeTeleopOnly)->setCriteria(inManualControllerMode),
        // new GantryDriverCommand(m_gantryDriver, consts::gantry_driver::LIFTMOTOR, consts::gantry_driver::MOVEUPPOSITION, consts::gantry_driver::POSITIONMOVE)
        new LiftCommand(m_gantryDriver, consts::gantry_driver::MOVEUPPOSITION, consts::gantry_driver::POSITIONMOVE)
    );

    m_operator_controller->bindKey(
        (new atmt::Trigger(atmt::BButton, atmt::ButtonPressed))->inMode(atmt::ModeTeleopOnly)->setCriteria(inManualControllerMode),
        // new GantryDriverCommand(m_gantryDriver, consts::gantry_driver::LIFTMOTOR, consts::gantry_driver::MOVEDOWNPOSITION, consts::gantry_driver::POSITIONMOVE)
        new LiftCommand(m_gantryDriver, consts::gantry_driver::MOVEDOWNPOSITION, consts::gantry_driver::POSITIONMOVE)
    );


    m_operator_controller->bindKey(
        (new atmt::Trigger(atmt::LeftStick, atmt::StickLeft))->inMode(atmt::ModeTeleopOnly)->setCriteria(inManualControllerMode),
        //new ExtruderCommand(m_slide, 0)
        // new GantryDriverCommand(m_gantryDriver, consts::gantry_driver::GANTRYMOTOR, consts::gantry_driver::MOVEUPPOSITION, consts::gantry_driver::POSITIONMOVE)
        new GantryCommand(m_gantryDriver, consts::gantry_driver::MOVEUPPOSITION, consts::gantry_driver::POSITIONMOVE)
        
    );

    m_operator_controller->bindKey(
        (new atmt::Trigger(atmt::LeftStick, atmt::StickRight))->inMode(atmt::ModeTeleopOnly)->setCriteria(inManualControllerMode),
        //new ExtruderCommand(m_slide, 1)
        // new GantryDriverCommand(m_gantryDriver, consts::gantry_driver::GANTRYMOTOR, consts::gantry_driver::MOVEDOWNPOSITION, consts::gantry_driver::POSITIONMOVE)
        new GantryCommand(m_gantryDriver, consts::gantry_driver::MOVEDOWNPOSITION, consts::gantry_driver::POSITIONMOVE)
    );

    m_operator_controller->bindKey(
        (new atmt::Trigger(atmt::LeftStick, atmt::StickUp))->inMode(atmt::ModeTeleopOnly)->setCriteria(inManualControllerMode),
        new ExtruderCommand(m_slide, consts::extruder::MOVEFORWARD)
    );

    m_operator_controller->bindKey(
        (new atmt::Trigger(atmt::LeftStick, atmt::StickDown))->inMode(atmt::ModeTeleopOnly)->setCriteria(inManualControllerMode),
        new ExtruderCommand(m_slide, consts::extruder::MOVEBACKWARD)
    );

    m_operator_controller->bindKey(
        (new atmt::Trigger(atmt::RightStick, atmt::StickLeft))->inMode(atmt::ModeTeleopOnly)->setCriteria(inManualControllerMode),
        //new ExtruderCommand(m_slide, 0, 1)
        // new GantryDriverCommand(m_gantryDriver, consts::gantry_driver::GANTRYMOTOR, consts::gantry_driver::FORWARDVELOCITY, consts::gantry_driver::VELOCITYMOVE)
        new GantryCommand(m_gantryDriver, consts::gantry_driver::FORWARDVELOCITY, consts::gantry_driver::VELOCITYMOVE)
    );

    m_operator_controller->bindKey(
        (new atmt::Trigger(atmt::RightStick, atmt::StickRight))->inMode(atmt::ModeTeleopOnly)->setCriteria(inManualControllerMode),
        // new GantryDriverCommand(m_gantryDriver, consts::gantry_driver::GANTRYMOTOR, consts::gantry_driver::BACKWARDVELOCITY, consts::gantry_driver::VELOCITYMOVE)
        new GantryCommand(m_gantryDriver, consts::gantry_driver::BACKWARDVELOCITY, consts::gantry_driver::VELOCITYMOVE)
    );

    m_operator_controller->bindKey(
        (new atmt::Trigger(atmt::RightStick, atmt::StickCenter))->inMode(atmt::ModeTeleopOnly)->setCriteria(inManualControllerMode),
        // new GantryDriverCommand(m_gantryDriver, consts::gantry_driver::GANTRYMOTOR, consts::gantry_driver::STOP, consts::gantry_driver::VELOCITYMOVE) 
        new GantryCommand(m_gantryDriver, consts::gantry_driver::STOP, consts::gantry_driver::VELOCITYMOVE) 
    );


    m_operator_controller->bindKey(
        (new atmt::Trigger(atmt::RightStick, atmt::StickCenter))->inMode(atmt::ModeTeleopOnly)->setCriteria(inManualControllerMode),
            new ExtruderCommand(m_slide, consts::extruder::STOP) 
    );

    m_operator_controller->bindKey(
        (new atmt::Trigger(atmt::RightStick, atmt::StickUp))->inMode(atmt::ModeTeleopOnly)->setCriteria(inManualControllerMode),
            new ExtruderCommand(m_slide, consts::extruder::MOVEFORWARD) 
    );

    m_operator_controller->bindKey(
        (new atmt::Trigger(atmt::RightStick, atmt::StickDown))->inMode(atmt::ModeTeleopOnly)->setCriteria(inManualControllerMode),
            new ExtruderCommand(m_slide, consts::extruder::MOVEBACKWARD) 
    );

    /*m_operator_controller->bindKey(
        (new atmt::Trigger(atmt::LeftStick, atmt::StickRight))->inMode(atmt::ModeTeleopOnly),
        new ExtruderCommand(m_slide, 2)
    );*/


    //m_operator_controller->bindKey(
    //    (new atmt::Trigger(atmt::LTAxis, atmt::StickUp))->inMode(atmt::ModeTeleopOnly),
    //    new ExtruderCommand(m_slide)
    //);
    
    m_operator_controller->bindKey(
        (new atmt::Trigger(atmt::BButton, atmt::ButtonPressed))->setCriteria(inRegularControllerMode),
        new ScoreBatteryBank(Bank_FarRow, Bank_RightSide, m_compressor, m_slide, m_claw, m_gantryDriver)
    );

};

atmt::Command* RobotContainer::getAutonomousCommand(int indicator, void* robot_container) {
    RobotContainer* self = static_cast<RobotContainer*>(robot_container);
    switch (indicator) {
        case 0:
            return new atmt::EmptyCommand();
        case 1: // Autonomous Routine to move RoboClaw to Belt Position, and extend probes. 
            return new atmt::SequentialCommandGroup({
                // new GantryDriverCommand(self->m_gantryDriver, consts::gantry_driver::GANTRYMOTOR, 3), // Move to Position 3
                new GantryCommand(self->m_gantryDriver, 3), // Move to Position 3
                new ExtruderCommand(self->m_slide, 1),
            });
        case 2:
            return new atmt::SequentialCommandGroup({
                new WaitForSerialResumeCommand(self->m_serial_reader),
                // new VacuumCommand(self->m_vacuum),
                new SendSerialResumeCommand(self->m_serial_reader),
                new WaitForSerialResumeCommand(self->m_serial_reader),
                // new VacuumCommand(self->m_vacuum),
            });
        
        default:
            return new atmt::EmptyCommand();
    }
};
int RobotContainer::getWhichAutonomousRoutine(void* robot_container) {
    RobotContainer* self = static_cast<RobotContainer*>(robot_container);
    return 0;
};
