
#include "RoboClawCommand.h"
#include <Arduino.h>
#include <cmath>
#include "Constants.h"

RoboClawCommand::RoboClawCommand(RoboClawUART* roboClaw, int position):
    atmt::Command(),
    m_roboClaw{ roboClaw },
    m_position{ position }

{
    usesSubsystem(m_roboClaw);
};
RoboClawCommand::RoboClawCommand(RoboClawCommand& command):
    atmt::Command(command)
{
    m_roboClaw = command.m_roboClaw;
    m_position = command.m_position;
};
RoboClawCommand::~RoboClawCommand() {
    // Will run ~Command() after this is complete
};
atmt::Command* RoboClawCommand::clone() const {
    return new RoboClawCommand(m_roboClaw, m_position);
};

void RoboClawCommand::initialize() {
  //  Serial.println(m_direction == 1 ? "Moving forward with magnitude: " : "Moving backward with magnitude: ");
  Serial.println("Initializing RoboClaw Command"); 
    m_roboClaw->init();

  m_roboClaw->positionElement =  m_roboClaw->positionElement + m_position; // Update current position before moving
  
  if(m_roboClaw->positionElement < 0){
      m_roboClaw->positionElement = 0; // Prevent going below minimum position
  }
    if(m_roboClaw->positionElement > 3){
        m_roboClaw->positionElement = 3; // Prevent going above maximum position
    }
    m_roboClaw->setPosition(m_roboClaw->Roboclaw_Positions[m_roboClaw->positionElement]);
};
void RoboClawCommand::execute() {
  //  m_roboClaw->update();
  m_roboClaw->move();

     

};
void RoboClawCommand::end(bool interrupted) {
    
};

bool RoboClawCommand::is_finished(){

return m_roboClaw->moveComplete; 
}


