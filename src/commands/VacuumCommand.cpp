
#include "VacuumCommand.h"
#include <Arduino.h>
#include <cmath>

VacuumCommand::VacuumCommand(Vacuum* vacuum):
    atmt::Command(),
    m_vacuum{ vacuum }

{
    usesSubsystem(m_vacuum);
};
VacuumCommand::VacuumCommand(VacuumCommand& command):
    atmt::Command(command)
{
    m_vacuum = command.m_vacuum;
};
VacuumCommand::~VacuumCommand() {
    // Will run ~Command() after this is complete
};
atmt::Command* VacuumCommand::clone() const {
    return new VacuumCommand(m_vacuum);
};

void VacuumCommand::initialize() {
  //  Serial.println(m_direction == 1 ? "Moving forward with magnitude: " : "Moving backward with magnitude: ");
  Serial.println("Initializing Vacuum Command"); 
  //m_vacuum->init();
};
void VacuumCommand::execute() {
  //  m_vacuum->update();
    bool newState = !m_vacuum->getState();
    Serial.println("Toggling Claw " + String(newState ? "On" : "Off"));
    m_vacuum->setState(newState);
    toggleClaw();
     

};
void VacuumCommand::end(bool interrupted) {
    
};

bool VacuumCommand::is_finished(){
return true; 
}


void VacuumCommand::toggleClaw(){
    if(m_vacuum->getState()){
        m_vacuum->enableVacuum(); // Turn on vacuum
    }
    else{
        m_vacuum->disableVacuum(); // Turn off vacuum
    }
}