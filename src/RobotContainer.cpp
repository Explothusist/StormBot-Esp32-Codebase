
#include "RobotContainer.h"

#include <vector>

#include "commands/BeltCommand.h"

RobotContainer::RobotContainer():
    m_belt_mover{ new BeltMover(consts::belt_mover::EnPin, consts::belt_mover::DirPin, consts::belt_mover::StepPin, consts::belt_mover::MS1Pin, consts::belt_mover::MS2Pin) },
    m_compressor{ new Compressor(consts::compressor::pwmPin1, consts::compressor::pwmPin2, consts::compressor::enPin1, consts::compressor::enPin2) },
    m_vacuum{ new Vacuum(consts::vacuum::pwmPin1, consts::vacuum::pwmPin2, consts::vacuum::enPin1, consts::vacuum::enPin2) },
    m_operator_controller{ new atmt::Joystick(atmt::PollMode_Manual) }
{

};
RobotContainer::~RobotContainer() { // Subsystems deleted by atmt::TimedRobot

};

void RobotContainer::configure_bindings() {
    // m_driver_controller->bindKey(atmt::R2Button, atmt::ButtonPressed, atmt::WhileTrigger, new ApproachAndAlign(m_drivetrain, m_camera_reader));
    // m_driver_controller->bindKey(atmt::R1Button, atmt::ButtonPressed, atmt::WhileTrigger, new AlignAndPounce(m_drivetrain, m_camera_reader));
    
    // m_drivetrain->setDefaultCommand(new TeleopDriveCommand(m_drivetrain, m_driver_controller));
    /*
    m_operator_controller->bindKey(
        new atmt::Trigger(atmt::LeftStick, atmt::StickUp),
        new BeltCommand(m_belt_mover, consts::belt_mover::Direction_Forward)
    );
    m_operator_controller->bindKey(
        new atmt::Trigger(atmt::LeftStick, atmt::StickDown),
        new BeltCommand(m_belt_mover, consts::belt_mover::Direction_Backward)
    );
    */

};

atmt::Command* RobotContainer::getAutonomousCommand() {
    // std::vector<atmt::Command*> commands = 
    // return new atmt::SequentialCommandGroup({
    //     (new DriveCommand(m_drivetrain, 0.3, 0.0, 0.0))->withTimeout(2.0),
    //     new ApproachAndAlign(m_drivetrain, m_camera_reader)
    // });
    return new atmt::EmptyCommand();
};