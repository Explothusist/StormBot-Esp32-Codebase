
#include "GantryDriverCommand.h"
#include <Arduino.h>
#include <cmath>
#include "Constants.h"

GantryDriverCommand::GantryDriverCommand(GantryDriver* roboClaw,int motor, int position, bool justMove, bool absolutePosition):
    atmt::Command(),
    m_gantryDriver{ roboClaw },
    m_motor{ motor },   
    m_position{ position },
    m_justMove{ justMove }, // Just move when true only turns the motor on. No encoder based movement. Encoder is still tracking position
    m_absolutePosition{ absolutePosition }


{
    usesSubsystem(m_gantryDriver);
};
GantryDriverCommand::GantryDriverCommand(const GantryDriverCommand& command):
    atmt::Command(command)
{
    m_gantryDriver = command.m_gantryDriver;
    m_position = command.m_position;
    m_motor = command.m_motor;
    m_justMove = command.m_justMove;
    m_absolutePosition = command.m_absolutePosition;
};
GantryDriverCommand::~GantryDriverCommand() {
    // Will run ~Command() after this is complete
};
atmt::Command* GantryDriverCommand::cloneSelf() const {
    return new GantryDriverCommand(m_gantryDriver,m_motor, m_position, m_justMove, m_absolutePosition);
};

void GantryDriverCommand::initialize() {
    //  Serial.println(m_direction == 1 ? "Moving forward with magnitude: " : "Moving backward with magnitude: ");
    //Serial.println("Initializing RoboClaw Command"); 
    m_gantryDriver->init();



        if(!m_justMove){
            if(!m_absolutePosition){
                m_gantryDriver->positionElement[m_motor] =  m_gantryDriver->positionElement[m_motor] + m_position; // Update current position before moving
            }
            else{
                m_gantryDriver->positionElement[m_motor] = m_position; // Set absolute position
            }

            if(m_gantryDriver->positionElement[m_motor] < 0){
                m_gantryDriver->positionElement[m_motor] = 0; // Prevent going below minimum position
            }
            if(m_motor == consts::gantry_driver::SLIDEMOTOR){
                if(m_gantryDriver->positionElement[m_motor] > 3){
                    m_gantryDriver->positionElement[m_motor] = 3; // Prevent going above maximum position
                }
                m_gantryDriver->setPosition(m_motor, m_gantryDriver->Roboclaw_Positions_Linear[m_gantryDriver->positionElement[m_motor]]);
            }
            if(m_motor == consts::gantry_driver::GANTRYMOTOR){
                if(m_gantryDriver->positionElement[m_motor] > 5){
                    m_gantryDriver->positionElement[m_motor] = 5; // Prevent going above maximum position
                }
                m_gantryDriver->setPosition(m_motor, m_gantryDriver->Roboclaw_Positions_Load[m_gantryDriver->positionElement[m_motor]]);
            }
        }
        else{
            m_gantryDriver->justMove(m_motor, m_position);
        }



};
void GantryDriverCommand::execute() {
  //  m_gantryDriver->update();
  if(!m_justMove){
    m_gantryDriver->move(m_motor);
  }
     

};
void GantryDriverCommand::end(bool interrupted) {
    
};

bool GantryDriverCommand::is_finished(){

    return m_gantryDriver->moveComplete; 
}


