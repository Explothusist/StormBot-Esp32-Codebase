
#include "TrackToSetpoint.h"
#include "../Constants.h"

TrackToSetpoint::TrackToSetpoint(StepperMotor* stepper, int setpoint):
    atmt::Command(),
    m_stepper{ stepper },
    m_setpoint{ setpoint }
{
    usesSubsystem(stepper); // May be called multiple times for multiple subsystems
};
TrackToSetpoint::TrackToSetpoint(TrackToSetpoint& command):
    atmt::Command(command)
{
    m_stepper = command.m_stepper;
    m_setpoint = command.m_setpoint;
};
TrackToSetpoint::~TrackToSetpoint() {
    // Will run ~Command() after this is complete
};

void TrackToSetpoint::initialize() { // Run once when scheduled
    // double dist = m_stepper->pos() - m_setpoint; // EXAMPLE
    // m_stepper->setSpeed(constants::TrackSpeed * dist); // EXAMPLE
};
void TrackToSetpoint::execute() { // Run repeatedly
    // Perform PID, if we want
};
void TrackToSetpoint::end(bool interrupted) { // Run once on end (interrupted=true means it was ended before is_finished()=true)
    // m_stepper->setSpeed(constants::TrackStopSpeed); // EXAMPLE
};
bool TrackToSetpoint::is_finished() {
    // return std::abs(m_stepper->pos() - m_setpoint) < constants::TrackPIDEpsilon; // EXAMPLE
    return false;
};