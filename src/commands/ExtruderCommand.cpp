
#include "ExtruderCommand.h"

#include <cmath>

ExtruderCommand::ExtruderCommand(Extruder* belt_mover, int direction): // Side to side movements
    atmt::Command(),
    m_belt_mover{ belt_mover },
    m_direction{ direction }
{
    usesSubsystem(m_belt_mover);
};

ExtruderCommand::ExtruderCommand(Extruder* belt_mover, int direction, bool isIncremental): // Small adjustments 
    atmt::Command(),
    m_belt_mover{ belt_mover },
    m_direction{ direction },
    m_isIncremental{ isIncremental }
{
    usesSubsystem(m_belt_mover);
};
ExtruderCommand::ExtruderCommand(const ExtruderCommand& command):
    atmt::Command(command)
{
    m_belt_mover = command.m_belt_mover;
    m_direction = command.m_direction;
    if(command.m_isIncremental){
        m_isIncremental = command.m_isIncremental;
    }
};
ExtruderCommand::~ExtruderCommand() {
    // Will run ~Command() after this is complete
};
atmt::Command* ExtruderCommand::cloneSelf() const {
    return new ExtruderCommand(m_belt_mover, m_direction, m_isIncremental);
};

void ExtruderCommand::initialize() {
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
  //  m_Extruder->setSpeed(m_direction); 

};
void ExtruderCommand::execute() {
   // m_belt_mover->update();
};
void ExtruderCommand::end(bool interrupted) {
    
};
bool ExtruderCommand::is_finished() {
    return true;
};
