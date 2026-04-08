#include "RoboClawUART.h"


RoboClawUART::RoboClawUART(uint8_t rxPin, uint8_t txPin, uint8_t _address)
    
{
    this->rxPin = rxPin;
    this->txPin = txPin;
    this->address = _address;
    this->defaultTimeoutMs = 5;
    
}

void RoboClawUART::init() {
    // Any additional initialization code can go here
    
    this->roboclaw = new Basicmicro(&Serial1, 10000);
    Serial1.begin(115200, SERIAL_8N1, rxPin, txPin); 
    this->roboclaw->begin(38400); // Initialize RoboClaw communication at 38400 baud

    // Configure position PID for both motors
    // Parameters: address, kp, ki, kd, kiMax, deadzone, minPos, maxPos
    this->roboclaw->SetM1PositionPID(this->address, 3.16, 0.15, 2.0, 1000, 150, MIN_HEIGHT[0], MAX_HEIGHT[0]); //4.16 .15 1
    this->roboclaw->SetM2PositionPID(this->address, 4.4, 0.15, 2.0, 1000, 150, MIN_HEIGHT[1], MAX_HEIGHT[1]);

    // Set default acceleration/deceleration (counts per second^2)
    this->roboclaw->SetM1DefaultAccel(this->address, 20000, 20000);
    this->roboclaw->SetM2DefaultAccel(this->address, 20000, 20000);
}
void RoboClawUART::systemPeriodic() {
    
};
void RoboClawUART::disabledPeriodic() {};
void RoboClawUART::autonomousPeriodic() {};
void RoboClawUART::teleopPeriodic() {};

int RoboClawUART::getPosition(int motor) {
    Serial.println("Getting position for motor: " + String(motor));
    if(motor == consts::robo_claw::MOTOR1){
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
    else if(motor == consts::robo_claw::MOTOR2){
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

void RoboClawUART::setPosition(int motor, int position) {
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

void RoboClawUART::justMove(int motor, int direction) {
    //moveComplete = false;
    Serial.println("Just moving motor: " + String(motor) + " in direction: " + String(direction));
    if(motor == consts::robo_claw::MOTOR1){
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
    else if(motor == consts::robo_claw::MOTOR2){
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


void RoboClawUART::resetEncoders() {

    this->roboclaw->ResetEncoders(this->address);


}

void RoboClawUART::setSpeed(int motor, int speed) {
    this->speed[motor] = speed;
    //this->roboclaw->ForwardM1(this->address, this->speed);
}

void RoboClawUART::move(int motor) {
    Serial.println("Moving motor " + String(motor) + " to position: " + String(commandedPosition[motor]));
    if(motor == consts::robo_claw::MOTOR1){
        this->roboclaw->M1SpeedPosition(this->address, speed[motor], commandedPosition[motor], 1);
    }
    else if(motor == consts::robo_claw::MOTOR2){
        this->roboclaw->M2SpeedPosition(this->address, speed[motor], commandedPosition[motor], 1);
    }
    moveComplete = true;
}



    