
#include "ClawCommand.h"
#include <Arduino.h>
#include <cmath>

ClawCommand::ClawCommand(Vacuum* vacuum):
    atmt::Command(),
    m_claw{ vacuum }

{
    usesSubsystem(m_claw);
};
ClawCommand::ClawCommand(const ClawCommand& command):
    atmt::Command(command)
{
    m_claw = command.m_claw;
};
ClawCommand::~ClawCommand() {
    // Will run ~Command() after this is complete
};
atmt::Command* ClawCommand::cloneSelf() const {
    return new ClawCommand(m_claw);
};

void ClawCommand::initialize() {
  //  Serial.println(m_direction == 1 ? "Moving forward with magnitude: " : "Moving backward with magnitude: ");
  Serial.println("Initializing Vacuum Command"); 
  //m_claw->init();
};
void ClawCommand::execute() {
  //  m_claw->update();
    bool newState = !m_claw->getState();
    Serial.println("Toggling Claw " + String(newState ? "On" : "Off"));
    m_claw->setState(newState);
    toggleClaw();
     

};
void ClawCommand::end(bool interrupted) {
    
};

bool ClawCommand::is_finished(){
return true; 
}


void ClawCommand::toggleClaw(){
    if(m_claw->getState()){
        m_claw->enableVacuum(); // Turn on vacuum
    }
    else{
        m_claw->disableVacuum(); // Turn off vacuum
    }
}