
#include "RobotContainer.h"

#include "commands/ExampleCommand.h"

RobotContainer::RobotContainer():
    m_compressor{ new Compressor(DcMotor(25,26,27)) },
    m_vacuumPump{ new Vacuum(DcMotor(14,12,13)) },
    m_beltMover{ new BeltMover(new StepperMotor(33,32,15)) },
    m_motor{ new DcMotor(1, 2, 3, 4) },
    m_operator_controller{ new atmt::Joystick() }
{

};
RobotContainer::~RobotContainer() {
    delete m_compressor;
    m_compressor = nullptr;
    delete m_vacuumPump;
    m_vacuumPump = nullptr;
    delete m_beltMover;
    m_beltMover = nullptr;
    delete m_motor;
    m_motor = nullptr;
    delete m_operator_controller;
    m_operator_controller = nullptr;
};

void RobotContainer::configure_bindings() {
    // Sets ExampleCommand(100, -1) to run when the A button is pressed for either 2 seconds or the A button is released
    m_operator_controller->bindKey(atmt::AButton, atmt::ButtonPressed, atmt::WhileTrigger, (new ExampleCommand(m_motor, 100, -1))->withTimeout(2.0));
    // Sets ExampleCommand(50, -1) to run when the B button is released
    m_operator_controller->bindKey(atmt::BButton, atmt::ButtonReleased, new ExampleCommand(m_motor, 50, 0));
};

atmt::Command* RobotContainer::getAutonomousCommand() {
    return new atmt::SequentialCommandGroup({ // Next Command starts when prior command finishes
        (new ExampleCommand(m_motor, 25, 1))->withTimeout(3.0), // Runs for 3 seconds or until command finishes
        (new ExampleCommand(m_motor, 200, -5))->withTimeout(2.3), // Runs for 2.3 seconds or until command finishes
        new ExampleCommand(m_motor, -30, 0) // Runs until command finishes or Autonomous finishes
    });
};