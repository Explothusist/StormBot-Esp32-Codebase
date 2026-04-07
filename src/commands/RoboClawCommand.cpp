
#include "RoboClawCommand.h"
#include <Arduino.h>
#include <cmath>
#include "Constants.h"

RoboClawCommand::RoboClawCommand(RoboClawUART* roboClaw,int motor, int position, bool justMove):
    atmt::Command(),
    m_roboClaw{ roboClaw },
    m_motor{ motor },   
    m_position{ position },
    m_justMove{ justMove }

{
    usesSubsystem(m_roboClaw);
};
RoboClawCommand::RoboClawCommand(const RoboClawCommand& command):
    atmt::Command(command)
{
    m_roboClaw = command.m_roboClaw;
    m_position = command.m_position;
    m_motor = command.m_motor;
    m_justMove = command.m_justMove;
};
RoboClawCommand::~RoboClawCommand() {
    // Will run ~Command() after this is complete
};
atmt::Command* RoboClawCommand::clone() const {
    return new RoboClawCommand(m_roboClaw,m_motor, m_position, m_justMove);
};

void RoboClawCommand::initialize() {
  //  Serial.println(m_direction == 1 ? "Moving forward with magnitude: " : "Moving backward with magnitude: ");
  //Serial.println("Initializing RoboClaw Command"); 
    m_roboClaw->init();

 if(!m_justMove){ // Set to a specific position 

    m_roboClaw->positionElement[m_motor] =  m_roboClaw->positionElement[m_motor] + m_position; // Update current position before moving
    
    if(m_roboClaw->positionElement[m_motor] < 0){
        m_roboClaw->positionElement[m_motor] = 0; // Prevent going below minimum position
    }
    if(m_motor == consts::robo_claw::MOTOR1){
        if(m_roboClaw->positionElement[m_motor] > 3){
            m_roboClaw->positionElement[m_motor] = 3; // Prevent going above maximum position
            

        }
        m_roboClaw->setPosition(m_motor, m_roboClaw->Roboclaw_Positions_Linear[m_roboClaw->positionElement[m_motor]]);
    }
    if(m_motor == consts::robo_claw::MOTOR2){
        if(m_roboClaw->positionElement[m_motor] > 5){
            m_roboClaw->positionElement[m_motor] = 5; // Prevent going above maximum position
        
        }
        m_roboClaw->setPosition(m_motor, m_roboClaw->Roboclaw_Positions_Load[m_roboClaw->positionElement[m_motor]]);
    }
}
else{

    m_roboClaw->justMove(m_motor, m_position);
}


    
};
void RoboClawCommand::execute() {
  //  m_roboClaw->update();
  if(!m_justMove){
    m_roboClaw->move(m_motor);
  }
     

};
void RoboClawCommand::end(bool interrupted) {
    
};

bool RoboClawCommand::is_finished(){

return m_roboClaw->moveComplete; 
}


