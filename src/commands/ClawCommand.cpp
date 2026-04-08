
#include "ClawCommand.h"
#include <Arduino.h>
#include <cmath>

ClawCommand::ClawCommand(Vacuum* vacuum):
    atmt::Command(),
    m_vacuum{ vacuum }

{
    usesSubsystem(m_vacuum);
};
ClawCommand::ClawCommand(const ClawCommand& command):
    atmt::Command(command)
{
    m_vacuum = command.m_vacuum;
};
ClawCommand::~ClawCommand() {
    // Will run ~Command() after this is complete
};
atmt::Command* ClawCommand::cloneSelf() const {
    return new ClawCommand(m_vacuum);
};

void ClawCommand::initialize() {
  //  Serial.println(m_direction == 1 ? "Moving forward with magnitude: " : "Moving backward with magnitude: ");
  Serial.println("Initializing Vacuum Command"); 
  //m_vacuum->init();
};
void ClawCommand::execute() {
  //  m_vacuum->update();
    bool newState = !m_vacuum->getState();
    Serial.println("Toggling Claw " + String(newState ? "On" : "Off"));
    m_vacuum->setState(newState);
    toggleClaw();
     

};
void ClawCommand::end(bool interrupted) {
    
};

bool ClawCommand::is_finished(){
return true; 
}


void ClawCommand::toggleClaw(){
    if(m_vacuum->getState()){
        m_vacuum->enableVacuum(); // Turn on vacuum
    }
    else{
        m_vacuum->disableVacuum(); // Turn off vacuum
    }
}