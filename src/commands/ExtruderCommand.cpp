
#include "ExtruderCommand.h"

#include <cmath>

ExtruderCommand::ExtruderCommand(Extruder* slide, int direction): // Side to side movements
    atmt::Command(),
    m_slide{ slide },
    m_direction{ direction }
{
    usesSubsystem(m_slide);
};

ExtruderCommand::ExtruderCommand(Extruder* slide, int direction, bool isIncremental): // Small adjustments 
    atmt::Command(),
    m_slide{ slide },
    m_direction{ direction },
    m_isIncremental{ isIncremental }
{
    usesSubsystem(m_slide);
};
ExtruderCommand::ExtruderCommand(const ExtruderCommand& command):
    atmt::Command(command)
{
    m_slide = command.m_slide;
    m_direction = command.m_direction;
    if(command.m_isIncremental){
        m_isIncremental = command.m_isIncremental;
    }
};
ExtruderCommand::~ExtruderCommand() {
    // Will run ~Command() after this is complete
};
atmt::Command* ExtruderCommand::cloneSelf() const {
    return new ExtruderCommand(m_slide, m_direction, m_isIncremental);
};

void ExtruderCommand::initialize() {
    Serial.println("Initializing Belt Command");
    Serial.println(m_direction);
    switch (m_direction)
    {
        case -1:
            m_slide->setSpeed(consts::slide::BACKWARDSPEED);
            break;
        case 0:
            m_slide->setSpeed(consts::slide::STOP);
            break;
        case 1:
            m_slide->setSpeed(consts::slide::FORWARDSPEED);
            break;
    }
  //  m_Extruder->setSpeed(m_direction); 

};
void ExtruderCommand::execute() {
   // m_slide->update();
};
void ExtruderCommand::end(bool interrupted) {
    
};
bool ExtruderCommand::is_finished() {
    return true;
};
