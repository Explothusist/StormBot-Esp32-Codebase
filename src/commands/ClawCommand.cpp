
#include "ClawCommand.h"
#include <Arduino.h>
#include <cmath>

ClawCommand::ClawCommand(Vacuum* vacuum):
    atmt::Command(),
    m_claw{ vacuum },
    m_position{ consts::claw::ClawClosed },
    m_is_toggle{ true }
{
    usesSubsystem(m_claw);
};
ClawCommand::ClawCommand(Vacuum* vacuum, consts::claw::ClawPosition position):
    atmt::Command(),
    m_claw{ vacuum },
    m_position{ position },
    m_is_toggle{ false }
{

};
ClawCommand::ClawCommand(const ClawCommand& command):
    atmt::Command(command)
{
    m_claw = command.m_claw;
    m_position = command.m_position;
    m_is_toggle = command.m_is_toggle;
};
ClawCommand::~ClawCommand() {
    // Will run ~Command() after this is complete
};
atmt::Command* ClawCommand::cloneSelf() const {
    if (!m_is_toggle) {
        return new ClawCommand(m_claw);
    }else {
        return new ClawCommand(m_claw, m_position);
    }
};

void ClawCommand::initialize() {
  //  Serial.println(m_direction == 1 ? "Moving forward with magnitude: " : "Moving backward with magnitude: ");
//   Serial.println("Initializing Vacuum Command"); 
  //m_claw->init();
};
void ClawCommand::execute() {
  //  m_claw->update();
    if (m_is_toggle) {
        bool newState = !m_claw->getState();
        // Serial.println("Toggling Claw " + String(newState ? "On" : "Off"));
        m_claw->setState(newState);
        toggleClaw();
    }else {
        switch (m_position) {
            case consts::claw::ClawClosed:
                m_claw->setState(true);
                break;
            case consts::claw::ClawOpen:
                m_claw->setState(false);
                break;
        }
    }
     

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