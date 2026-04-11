
#include "LiftCommand.h"
#include <Arduino.h>
#include <cmath>
#include "Constants.h"

LiftCommand::LiftCommand(GantryDriver* roboClaw, int position, bool justMove, bool absolutePosition):
    atmt::Command(),
    m_gantryDriver{ roboClaw },
    m_position{ position },
    m_justMove{ justMove }, // Just move when true only turns the motor on. No encoder based movement. Encoder is still tracking position
    m_absolutePosition{ absolutePosition }


{
    usesSubsystem(m_gantryDriver);
};
LiftCommand::LiftCommand(const LiftCommand& command):
    atmt::Command(command)
{
    m_gantryDriver = command.m_gantryDriver;
    m_position = command.m_position;
    m_justMove = command.m_justMove;
    m_absolutePosition = command.m_absolutePosition;
};
LiftCommand::~LiftCommand() {
    // Will run ~Command() after this is complete
};
atmt::Command* LiftCommand::cloneSelf() const {
    return new LiftCommand(m_gantryDriver, m_position, m_justMove, m_absolutePosition);
};

void LiftCommand::initialize() {
    //  Serial.println(m_direction == 1 ? "Moving forward with magnitude: " : "Moving backward with magnitude: ");
    //Serial.println("Initializing RoboClaw Command"); 
    m_gantryDriver->init();



    if(!m_justMove){
        if(!m_absolutePosition){
            m_gantryDriver->positionElement[consts::gantry_driver::LIFTMOTOR] =  m_gantryDriver->positionElement[consts::gantry_driver::LIFTMOTOR] + m_position; // Update current position before moving
        }
        else{
            m_gantryDriver->positionElement[consts::gantry_driver::LIFTMOTOR] = m_position; // Set absolute position
        }

        if(m_gantryDriver->positionElement[consts::gantry_driver::LIFTMOTOR] < 0){
            m_gantryDriver->positionElement[consts::gantry_driver::LIFTMOTOR] = 0; // Prevent going below minimum position
        }
        // if(consts::gantry_driver::LIFTMOTOR == consts::gantry_driver::LIFTMOTOR){
            if(m_gantryDriver->positionElement[consts::gantry_driver::LIFTMOTOR] > 3){
                m_gantryDriver->positionElement[consts::gantry_driver::LIFTMOTOR] = 3; // Prevent going above maximum position
            }
            m_gantryDriver->setPosition(consts::gantry_driver::LIFTMOTOR, m_gantryDriver->Roboclaw_Positions_Linear[m_gantryDriver->positionElement[consts::gantry_driver::LIFTMOTOR]]);
        // }
        // if(consts::gantry_driver::LIFTMOTOR == consts::gantry_driver::GANTRYMOTOR){
        //     if(m_gantryDriver->positionElement[consts::gantry_driver::LIFTMOTOR] > 5){
        //         m_gantryDriver->positionElement[consts::gantry_driver::LIFTMOTOR] = 5; // Prevent going above maximum position
        //     }
        //     m_gantryDriver->setPosition(consts::gantry_driver::LIFTMOTOR, m_gantryDriver->Roboclaw_Positions_Load[m_gantryDriver->positionElement[consts::gantry_driver::LIFTMOTOR]]);
        // }
    }
    else{
        m_gantryDriver->justMove(consts::gantry_driver::LIFTMOTOR, m_position);
    }



};
void LiftCommand::execute() {
  //  m_gantryDriver->update();
  if(!m_justMove){
    m_gantryDriver->move(consts::gantry_driver::LIFTMOTOR);
  }
     

};
void LiftCommand::end(bool interrupted) {
    m_gantryDriver->justMove(consts::gantry_driver::LIFTMOTOR, 0);
};

bool LiftCommand::is_finished(){
    if (!m_justMove) {
        return m_gantryDriver->moveComplete; 
    }else {
        return false;
    }
}


