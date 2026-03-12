
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
BeltCommand::BeltCommand(BeltCommand& command):
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
    //Serial.println("Initializing Belt Command");
    //Serial.println(m_direction);

    if(m_isIncremental){
        Serial.println("Performing incremental move in direction: " + String(m_direction));
        incrementalMove(m_direction);
        return;
    }
    else{
        m_belt_mover->moveToSide(static_cast<FastStepperMotor::Side>(m_direction)); // Move 1000 steps in the appropriate direction as a test
    }
    
};
void BeltCommand::execute() {
    m_belt_mover->update();
};
void BeltCommand::end(bool interrupted) {
    
};
bool BeltCommand::is_finished() {
    return m_belt_mover->moveComplete();
};

void BeltCommand::incrementalMove(int direction){
    if(direction == 0){
        m_belt_mover->moveLeft();
    }
    else if (direction == 1){
        m_belt_mover->moveRight();
    }
    else if (direction == 2){
        Serial.println("Stopping Belt");
        m_belt_mover->stop();
    }
}