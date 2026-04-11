
#include "GantryCommand.h"
#include <Arduino.h>
#include <cmath>
#include "Constants.h"

GantryCommand::GantryCommand(GantryDriver* roboClaw, int position, bool justMove, bool absolutePosition):
    atmt::Command(),
    m_gantryDriver{ roboClaw },
    m_position{ position },
    m_justMove{ justMove }, // Just move when true only turns the motor on. No encoder based movement. Encoder is still tracking position
    m_absolutePosition{ absolutePosition },
    m_relativeAbsolute{ false },
    m_relative_setpoint{ consts::gantry::RelativeSetpoint::Neutral }


{
    usesSubsystem(m_gantryDriver);
};
GantryCommand::GantryCommand(GantryDriver* roboClaw, consts::gantry::RelativeSetpoint relative_setpoint):
    atmt::Command(),
    m_gantryDriver{ roboClaw },
    m_position{ 0 },
    m_justMove{ false }, // Just move when true only turns the motor on. No encoder based movement. Encoder is still tracking position
    m_absolutePosition{ true },
    m_relativeAbsolute{ true },
    m_relative_setpoint{ relative_setpoint }


{
    usesSubsystem(m_gantryDriver);
};
GantryCommand::GantryCommand(const GantryCommand& command):
    atmt::Command(command)
{
    m_gantryDriver = command.m_gantryDriver;
    m_position = command.m_position;
    m_justMove = command.m_justMove;
    m_absolutePosition = command.m_absolutePosition;
    m_relativeAbsolute = command.m_relativeAbsolute;
    m_relative_setpoint = command.m_relative_setpoint;
};
GantryCommand::~GantryCommand() {
    // Will run ~Command() after this is complete
};
atmt::Command* GantryCommand::cloneSelf() const {
    if (!m_relativeAbsolute) {
        return new GantryCommand(m_gantryDriver, m_position, m_justMove, m_absolutePosition);
    }else {
        return new GantryCommand(m_gantryDriver, m_relative_setpoint, m_relativeAbsolute);
    }
};

void GantryCommand::initialize() {
    Serial.println("Starting Gantry");
    //  Serial.println(m_direction == 1 ? "Moving forward with magnitude: " : "Moving backward with magnitude: ");
    //Serial.println("Initializing RoboClaw Command"); 
    m_gantryDriver->init();

    if (m_relativeAbsolute) {
        m_position = m_gantryDriver->getAbsoluteGantryFromRelativeGantry(m_relative_setpoint);
    }



    if(!m_justMove){
        if(!m_absolutePosition){
            m_gantryDriver->positionElement[consts::gantry_driver::GANTRYMOTOR] =  m_gantryDriver->positionElement[consts::gantry_driver::GANTRYMOTOR] + m_position; // Update current position before moving
        }
        else{
            m_gantryDriver->positionElement[consts::gantry_driver::GANTRYMOTOR] = m_position; // Set absolute position
        }

        if(m_gantryDriver->positionElement[consts::gantry_driver::GANTRYMOTOR] < 0){
            m_gantryDriver->positionElement[consts::gantry_driver::GANTRYMOTOR] = 0; // Prevent going below minimum position
        }
        // if(consts::gantry_driver::GANTRYMOTOR == consts::gantry_driver::LIFTMOTOR){
        //     if(m_gantryDriver->positionElement[consts::gantry_driver::GANTRYMOTOR] > 3){
        //         m_gantryDriver->positionElement[consts::gantry_driver::GANTRYMOTOR] = 3; // Prevent going above maximum position
        //     }
        //     m_gantryDriver->setPosition(consts::gantry_driver::GANTRYMOTOR, m_gantryDriver->Roboclaw_Positions_Linear[m_gantryDriver->positionElement[consts::gantry_driver::GANTRYMOTOR]]);
        // }
        // if(consts::gantry_driver::GANTRYMOTOR == consts::gantry_driver::GANTRYMOTOR){
            if(m_gantryDriver->positionElement[consts::gantry_driver::GANTRYMOTOR] > 5){
                m_gantryDriver->positionElement[consts::gantry_driver::GANTRYMOTOR] = 5; // Prevent going above maximum position
            }
            m_gantryDriver->setPosition(consts::gantry_driver::GANTRYMOTOR, m_gantryDriver->Roboclaw_Positions_Load[m_gantryDriver->positionElement[consts::gantry_driver::GANTRYMOTOR]]);
        // }
    }
    else{
        m_gantryDriver->justMove(consts::gantry_driver::GANTRYMOTOR, m_position);
    }



};
void GantryCommand::execute() {
  //  m_gantryDriver->update();
  if(!m_justMove){
    m_gantryDriver->move(consts::gantry_driver::GANTRYMOTOR);
  }
     

};
void GantryCommand::end(bool interrupted) {
    Serial.println("Ending Gantry");
    m_gantryDriver->justMove(consts::gantry_driver::GANTRYMOTOR, consts::gantry_driver::STOP);
};

bool GantryCommand::is_finished(){
    if (!m_justMove) {
        return m_gantryDriver->moveComplete; 
    }else {
        return false;
    }
}


