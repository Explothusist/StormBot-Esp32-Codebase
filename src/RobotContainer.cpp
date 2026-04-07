
#include "RobotContainer.h"
#include "wifi_network.h"

#include <vector>

#include "commands/BeltCommand.h"
#include "commands/VacuumCommand.h"
#include "commands/RoboClawCommand.h"   
RobotContainer::RobotContainer():
    m_belt_mover{ new BeltMover(consts::belt_mover::PWM1, consts::belt_mover::PWM2) },
    m_compressor{ new Compressor(consts::compressor::pwmPin1, consts::compressor::pwmPin2, consts::compressor::enPin1, consts::compressor::enPin2) },
    m_vacuum{ new Vacuum(consts::vacuum::pwmPin1, consts::vacuum::pwmPin2, consts::vacuum::enPin1, consts::vacuum::enPin2) },
    m_roboClaw{ new RoboClawUART(consts::robo_claw::rxPin, consts::robo_claw::txPin, consts::robo_claw::address) },
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
        (new atmt::Trigger(atmt::AButton, atmt::ButtonPressed))->inMode(atmt::ModeAnyAndAll)
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
        new VacuumCommand(m_vacuum)
        //new BeltCommand(m_belt_mover, consts::belt_mover::Direction_Forward)
    );
    */
    
    m_operator_controller->bindKey(
        (new atmt::Trigger(atmt::BButton, atmt::ButtonPressed))->inMode(atmt::ModeTeleopOnly),
        new VacuumCommand(m_vacuum)
    );

    /*
    m_operator_controller->bindKey(
        (new atmt::Trigger(atmt::BButton, atmt::ButtonPressed))->inMode(atmt::ModeTeleopOnly),
        new VacuumCommand(m_vacuum)
    );
    */
    m_operator_controller->bindKey(
        (new atmt::Trigger(atmt::LeftButton, atmt::ButtonPressed))->inMode(atmt::ModeTeleopOnly),
        new RoboClawCommand(m_roboClaw, consts::robo_claw::MOTOR1, 1)
    );

    m_operator_controller->bindKey(
        (new atmt::Trigger(atmt::RightButton, atmt::ButtonPressed))->inMode(atmt::ModeTeleopOnly),
        new RoboClawCommand(m_roboClaw, consts::robo_claw::MOTOR1, -1)
    );


    m_operator_controller->bindKey(
        (new atmt::Trigger(atmt::LeftStick, atmt::StickLeft))->inMode(atmt::ModeTeleopOnly),
        //new BeltCommand(m_belt_mover, 0)
        new RoboClawCommand(m_roboClaw, consts::robo_claw::MOTOR2, 1)
        
    );

    m_operator_controller->bindKey(
        (new atmt::Trigger(atmt::LeftStick, atmt::StickRight))->inMode(atmt::ModeTeleopOnly),
        //new BeltCommand(m_belt_mover, 1)
        new RoboClawCommand(m_roboClaw, consts::robo_claw::MOTOR2, -1)
    );

    m_operator_controller->bindKey(
        (new atmt::Trigger(atmt::LeftStick, atmt::StickUp))->inMode(atmt::ModeTeleopOnly),
        new BeltCommand(m_belt_mover, 1)
    );

    m_operator_controller->bindKey(
        (new atmt::Trigger(atmt::LeftStick, atmt::StickDown))->inMode(atmt::ModeTeleopOnly),
        new BeltCommand(m_belt_mover, -1)
    );

    m_operator_controller->bindKey(
        (new atmt::Trigger(atmt::RightStick, atmt::StickLeft))->inMode(atmt::ModeTeleopOnly),
        //new BeltCommand(m_belt_mover, 0, 1)
        new RoboClawCommand(m_roboClaw, consts::robo_claw::MOTOR2, 1, true)
    );

    m_operator_controller->bindKey(
        (new atmt::Trigger(atmt::RightStick, atmt::StickRight))->inMode(atmt::ModeTeleopOnly),
        new RoboClawCommand(m_roboClaw, consts::robo_claw::MOTOR2, -1, true)
    );

    m_operator_controller->bindKey(
        (new atmt::Trigger(atmt::RightStick, atmt::StickCenter))->inMode(atmt::ModeTeleopOnly),
            new RoboClawCommand(m_roboClaw, consts::robo_claw::MOTOR2, 0, true) 
    );


    m_operator_controller->bindKey(
        (new atmt::Trigger(atmt::RightStick, atmt::StickCenter))->inMode(atmt::ModeTeleopOnly),
            new BeltCommand(m_belt_mover, 0) 
    );

    m_operator_controller->bindKey(
        (new atmt::Trigger(atmt::RightStick, atmt::StickUp))->inMode(atmt::ModeTeleopOnly),
            new BeltCommand(m_belt_mover, -1) 
    );

    m_operator_controller->bindKey(
        (new atmt::Trigger(atmt::RightStick, atmt::StickDown))->inMode(atmt::ModeTeleopOnly),
            new BeltCommand(m_belt_mover, 1) 
    );

    /*m_operator_controller->bindKey(
        (new atmt::Trigger(atmt::LeftStick, atmt::StickRight))->inMode(atmt::ModeTeleopOnly),
        new BeltCommand(m_belt_mover, 2)
    );*/


    //m_operator_controller->bindKey(
    //    (new atmt::Trigger(atmt::LTAxis, atmt::StickUp))->inMode(atmt::ModeTeleopOnly),
    //    new BeltCommand(m_belt_mover)
    //);
    
    

};

// atmt::Command* RobotContainer::getAutonomousCommand() {
//     // std::vector<atmt::Command*> commands = 
//     // return new atmt::SequentialCommandGroup({
//     //     (new DriveCommand(m_drivetrain, 0.3, 0.0, 0.0))->withTimeout(2.0),
//     //     new ApproachAndAlign(m_drivetrain, m_camera_reader)
//     // });
//     return new atmt::EmptyCommand();
// };
atmt::Command* RobotContainer::getAutonomousCommand(int indicator, void* robot_container) {
    RobotContainer* self = static_cast<RobotContainer*>(robot_container);
    switch (indicator) {
        case 0:
            return new atmt::EmptyCommand();
        case 1: // Autonomous Routine to move RoboClaw to Belt Position, and extend probes. 
            return new atmt::SequentialCommandGroup({
                std::vector<atmt::Command*>{
                    new RoboClawCommand(self->m_roboClaw, consts::robo_claw::MOTOR2, 3), // Move to Position 3
                    new BeltCommand(self->m_belt_mover, 1),
                }
            });
        
        
        default:
            return new atmt::EmptyCommand();
    }
};
int RobotContainer::getWhichAutonomousRoutine(void* robot_container) {
    RobotContainer* self = static_cast<RobotContainer*>(robot_container);
    return 0;
};
