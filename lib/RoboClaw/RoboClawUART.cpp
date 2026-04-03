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
}


void RoboClawUART::periodic(){

}

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
        
            foundZeros[motor] = 0;
        return value;
        }   
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
    // Read current position from encoder
    //while(!moveCompelte){
    
    int currentPosition = getPosition(motor);

    //int currentPosition = motor == 1 ?   this->roboclaw->ReadEncM2(this->address) : this->roboclaw->ReadEncM1(this->address);
    Serial.println("Current Position: " + String(currentPosition) + " Commanded Position: " + String(commandedPosition[motor]) + " Speed: " + String(speed[motor]));
   //Serial.println(currentPosition);
    if(motor == consts::robo_claw::MOTOR1){
        if(currentPosition > commandedPosition[motor] + 100) { // If we're above the target position, move backward
        // Serial.println("Moving backward");
            this->roboclaw->BackwardM1(this->address, this->speed[motor]);
        }
        else if (currentPosition < commandedPosition[motor] - 100) { // If we're below the target position, move forward
        // Serial.println("Moving forward");
            this->roboclaw->ForwardM1(this->address, this->speed[motor]);
        }
        else {
            moveComplete = true;
            this->roboclaw->ForwardM1(this->address, 0); // Stop if we're within the target range
        }
    }
    else if(motor == consts::robo_claw::MOTOR2){
        if(currentPosition > commandedPosition[motor] + 100) { // If we're above the target position, move backward
        // Serial.println("Moving backward");
            this->roboclaw->BackwardM2(this->address, this->speed[motor]);
        }
        else if (currentPosition < commandedPosition[motor] - 100) { // If we're below the target position, move forward
        // Serial.println("Moving forward");
            this->roboclaw->ForwardM2(this->address, this->speed[motor]);
        }
        else {
            moveComplete = true;
            this->roboclaw->ForwardM2(this->address, 0); // Stop if we're within the target range
        }
    }

   // }
}



    