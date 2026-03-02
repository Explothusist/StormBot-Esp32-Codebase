
#include "BeltCommand.h"

#include <cmath>

BeltCommand::BeltCommand(BeltMover* belt_mover, int direction):
    atmt::Command(),
    m_belt_mover{ belt_mover },
    m_direction{ direction }
{
    usesSubsystem(m_belt_mover);
};
BeltCommand::BeltCommand(BeltCommand& command):
    atmt::Command(command)
{
    m_belt_mover = command.m_belt_mover;
    m_direction = command.m_direction;
};
BeltCommand::~BeltCommand() {
    // Will run ~Command() after this is complete
};
atmt::Command* BeltCommand::clone() const {
    return new BeltCommand(m_belt_mover, m_direction);
};

void BeltCommand::initialize() {
    Serial.println(m_direction == 1 ? "Moving forward with magnitude: " : "Moving backward with magnitude: ");
    m_belt_mover->setDirection(m_direction);
    m_belt_mover->setDistance(m_direction == 1 ? 1000 : -1000); // Move 1000 steps in the appropriate direction as a test
};
void BeltCommand::execute() {
    m_belt_mover->update();
};
void BeltCommand::end(bool interrupted) {
    
};
bool BeltCommand::is_finished() {
    return m_belt_mover->moveComplete();
};