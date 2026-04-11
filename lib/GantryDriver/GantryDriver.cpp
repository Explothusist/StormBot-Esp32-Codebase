#include "GantryDriver.h"


GantryDriver::GantryDriver(uint8_t rxPin, uint8_t txPin, uint8_t _address)
    
{
    this->rxPin = rxPin;
    this->txPin = txPin;
    this->address = _address;
    this->defaultTimeoutMs = 5;
    
}

void GantryDriver::init() {
    // Any additional initialization code can go here
    
    this->roboclaw = new Basicmicro(&Serial1, 10000);
    Serial1.begin(115200, SERIAL_8N1, rxPin, txPin); 
    this->roboclaw->begin(38400); // Initialize RoboClaw communication at 38400 baud

    // Configure position PID for both motors
    // Parameters: address, kp, ki, kd, kiMax, deadzone, minPos, maxPos
<<<<<<< HEAD:lib/RoboClaw/RoboClawUART.cpp
    this->roboclaw->SetM1PositionPID(this->address, 2.4, 0.05, 2.0, 0, 150, MIN_HEIGHT[0], MAX_HEIGHT[0]); // Slide Motor

    this->roboclaw->SetM2PositionPID(this->address, 4.4, 0.05, 4.0, 0, 150, MIN_HEIGHT[1], MAX_HEIGHT[1]);
=======
    this->roboclaw->SetM1PositionPID(this->address, 3.16, 0.15, 2.0, 1000, 150, MIN_HEIGHT[consts::gantry_driver::LIFTMOTOR], MAX_HEIGHT[consts::gantry_driver::LIFTMOTOR]); //4.16 .15 1
    this->roboclaw->SetM2PositionPID(this->address, 4.4, 0.15, 2.0, 1000, 150, MIN_HEIGHT[consts::gantry_driver::GANTRYMOTOR], MAX_HEIGHT[consts::gantry_driver::GANTRYMOTOR]);
>>>>>>> 7920f3bc468d59bd594171a7f55857834c1beeb0:lib/GantryDriver/GantryDriver.cpp

    // Set default acceleration/deceleration (counts per second^2)
    // this->roboclaw->SetM1DefaultAccel(this->address, 20000, 20000);
    // this->roboclaw->SetM2DefaultAccel(this->address, 20000, 20000);
    this->roboclaw->SetM1DefaultAccel(this->address, 100000, 100000); // Gantry
    this->roboclaw->SetM2DefaultAccel(this->address, 50000, 50000); // Lift
}
void GantryDriver::systemPeriodic() {
    // Serial.printf("Gantry Pos: %d\n", this->getPosition(consts::gantry_driver::GANTRYMOTOR));
    // Serial.printf("Lift Pos: %d\n", this->getPosition(consts::gantry_driver::LIFTMOTOR));
};
void GantryDriver::disabledPeriodic() {};
void GantryDriver::autonomousPeriodic() {};
void GantryDriver::teleopPeriodic() {};

int GantryDriver::getPosition(int motor) {
    // Serial.println("Getting position for motor: " + String(motor));
    if(motor == consts::gantry_driver::LIFTMOTOR){
        uint32_t value = this->roboclaw->ReadEncM1(this->address);
        if(value == 0){
            
            foundZeros[motor]++;
            if(foundZeros[motor] > 10){
                foundZeros[motor] = 0;
                return 0;
            }  
            return getPosition(motor);    
        } 
        foundZeros[motor] = 0;
        return value;

    }
    else if(motor == consts::gantry_driver::GANTRYMOTOR){
        uint32_t value = this->roboclaw->ReadEncM2(this->address);
        if(value == 0){
               
            foundZeros[motor]++;
            if(foundZeros[motor] > 10){
                foundZeros[motor] = 0; 
                return 0;
            }  
            return getPosition(motor);    
        }
        foundZeros[motor] = 0;
        return value;
    }
    return 0;
}
// int GantryDriver::getPosition(int motor) {
//     switch (motor) {
//         case consts::gantry_driver::GANTRYMOTOR:

//     }
// };   

void GantryDriver::setPosition(int motor, int position) {
    this->commandedPosition[motor] = position;

    moveComplete = false;

    if(commandedPosition[motor] < MIN_HEIGHT[motor]){
        commandedPosition[motor] = MIN_HEIGHT[motor]; // Minimum position to prevent overextension
    }
    if(commandedPosition[motor] > MAX_HEIGHT[motor]){
        commandedPosition[motor] = MAX_HEIGHT[motor]; // Maximum position to prevent overextension
    }
    //Serial.println("Setting Position to: " + String(commandedPosition[motor]) + 
    //    " for motor: " + String(motor));
    move(motor);

}

void GantryDriver::justMove(int motor, int direction) {
    //moveComplete = false;
    Serial.println("Just moving motor: " + String(motor) + " in direction: " + String(direction));
    if(motor == consts::gantry_driver::LIFTMOTOR){
        if(direction == 1){
            this->roboclaw->ForwardM1(this->address, this->speed[motor]);
        }
        else if(direction == -1){
            this->roboclaw->BackwardM1(this->address, this->speed[motor]);
        }
        else{
            this->roboclaw->ForwardM1(this->address, 0);
        }
    }
    else if(motor == consts::gantry_driver::GANTRYMOTOR){
        if(direction == 1){
            Serial.println("Just moving motor: " + String(motor) + " in direction: " + String(direction));
            this->roboclaw->ForwardM2(this->address, this->speed[motor]);
        }
        else if(direction == -1){
            Serial.println("Just moving motor: " + String(motor) + " in direction: " + String(direction));
            this->roboclaw->BackwardM2(this->address, this->speed[motor]);
        }
        else{
            this->roboclaw->ForwardM2(this->address, 0);
            Serial.println(String(this->roboclaw->ReadEncM2(this->address)));
        }

    }
}


void GantryDriver::resetEncoders() {

    this->roboclaw->ResetEncoders(this->address);


}

void GantryDriver::setSpeed(int motor, int speed) {
    this->speed[motor] = speed;
    //this->roboclaw->ForwardM1(this->address, this->speed);
}

void GantryDriver::move(int motor) {
    Serial.println("Moving motor " + String(motor) + " to position: " + String(commandedPosition[motor]));
    if(motor == consts::gantry_driver::LIFTMOTOR){
        this->roboclaw->M1SpeedPosition(this->address, speed[motor], commandedPosition[motor], 1);
    }
    else if(motor == consts::gantry_driver::GANTRYMOTOR){
        this->roboclaw->M2SpeedPosition(this->address, speed[motor], commandedPosition[motor], 1);
    }
    moveComplete = true;
}


int GantryDriver::getAbsoluteGantryFromRelativeGantry(consts::gantry::RelativeSetpoint relative_setpoint) {
    int last_position = this->commandedPosition[consts::gantry_driver::GANTRYMOTOR];

    if (last_position < consts::gantry::Setpoint_Corner01) {
        return consts::gantry::Setpoint_Store;
    }else if (last_position < consts::gantry::Setpoint_Corner12) {
        switch (relative_setpoint) {
            case consts::gantry::RelativeSetpoint::LeftScore:
                return consts::gantry::Setpoint_Side1_LeftScore;
            case consts::gantry::RelativeSetpoint::Neutral:
                return consts::gantry::Setpoint_Side1_Neutral;
            case consts::gantry::RelativeSetpoint::RightScore:
                return consts::gantry::Setpoint_Side1_RightScore;
        }
    }else if (last_position < consts::gantry::Setpoint_Corner23) {
        switch (relative_setpoint) {
            case consts::gantry::RelativeSetpoint::LeftScore:
                return consts::gantry::Setpoint_Side2_LeftScore;
            case consts::gantry::RelativeSetpoint::Neutral:
                return consts::gantry::Setpoint_Side2_Neutral;
            case consts::gantry::RelativeSetpoint::RightScore:
                return consts::gantry::Setpoint_Side2_RightScore;
        }
    }else {
        switch (relative_setpoint) {
            case consts::gantry::RelativeSetpoint::LeftScore:
                return consts::gantry::Setpoint_Side3_LeftScore;
            case consts::gantry::RelativeSetpoint::Neutral:
                return consts::gantry::Setpoint_Side3_Neutral;
            case consts::gantry::RelativeSetpoint::RightScore:
                return consts::gantry::Setpoint_Side3_RightScore;
        }
    }
};


    