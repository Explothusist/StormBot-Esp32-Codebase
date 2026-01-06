#include "ExampleCommand.h"

ExampleCommand::ExampleCommand(DcMotor* motor, int speed, int speed_shift):
    atmt::Command(),
    m_motor{ motor },
    m_speed{ speed },
    m_speed_shift{ speed_shift },
    m_counter{ 0 }
{
    usesSubsystem(motor); // May be called multiple times for multiple subsystems
};
ExampleCommand::ExampleCommand(ExampleCommand& command):
    atmt::Command(command)
{
    m_motor = command.m_motor;
    m_speed = command.m_speed;
    m_speed_shift = command.m_speed_shift;
};
ExampleCommand::~ExampleCommand() {
    // Will run ~Command() after this is complete
};

void ExampleCommand::initialize() { // Run once when scheduled
    m_motor->setSpeed(m_speed);
};
void ExampleCommand::execute() { // Run repeatedly
    // Perform PID,
    // or read Joystick,
    // or read other subsystem,
    // or check Cameras,
    // etc.
    m_counter += 1;
    m_motor->setSpeed(m_speed + (m_speed_shift * m_counter));
};
void ExampleCommand::end(bool interrupted) { // Run once on end (interrupted=true means it was ended before is_finished()=true)
    m_motor->setSpeed(0);
    if (interrupted) {
        Serial.println("ExampleCommand Interrupted!");
    }
};
bool ExampleCommand::is_finished() {
    // Check motor position, Camera vision, etc.
    return false; // Never ends itself, but can still be ended by other commands (one command per subsystem)
};