
#include "BeltCommand.h"

#include <cmath>

BeltCommand::BeltCommand(BeltMover* belt_mover, int direction): // Side to side movements
    atmt::Command(),
    m_belt_mover{ belt_mover },
    m_direction{ direction }
{
    usesSubsystem(m_belt_mover);
};

BeltCommand::BeltCommand(BeltMover* belt_mover, int direction, bool isIncremental): // Small adjustments 
    atmt::Command(),
    m_belt_mover{ belt_mover },
    m_direction{ direction },
    m_isIncremental{ isIncremental }
{
    usesSubsystem(m_belt_mover);
};
BeltCommand::BeltCommand(const BeltCommand& command):
    atmt::Command(command)
{
    m_belt_mover = command.m_belt_mover;
    m_direction = command.m_direction;
    if(command.m_isIncremental){
        m_isIncremental = command.m_isIncremental;
    }
};
BeltCommand::~BeltCommand() {
    // Will run ~Command() after this is complete
};
atmt::Command* BeltCommand::clone() const {
    return new BeltCommand(m_belt_mover, m_direction, m_isIncremental);
};

void BeltCommand::initialize() {
    Serial.println("Initializing Belt Command");
    Serial.println(m_direction);
    switch (m_direction)
    {
        case -1:
            m_belt_mover->setSpeed(consts::belt_mover::BACKWARDSPEED);
            break;
        case 0:
            m_belt_mover->setSpeed(consts::belt_mover::STOP);
            break;
        case 1:
            m_belt_mover->setSpeed(consts::belt_mover::FORWARDSPEED);
            break;
    }
  //  m_beltMover->setSpeed(m_direction); 

};
void BeltCommand::execute() {
   // m_belt_mover->update();
};
void BeltCommand::end(bool interrupted) {
    
};
bool BeltCommand::is_finished() {
    return true;
};
