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

int RoboClawUART::getPosition() {
    return this->roboclaw->ReadEncM1(this->address);
}   

void RoboClawUART::setPosition(int position) {
    this->commandedPosition = position;

    moveComplete = false;

    if(commandedPosition < MIN_HEIGHT){
        commandedPosition = MIN_HEIGHT; // Minimum position to prevent overextension
    }
    if(commandedPosition > MAX_HEIGHT){
        commandedPosition = MAX_HEIGHT; // Maximum position to prevent overextension
    }
    Serial.println("Setting Position to: " + String(commandedPosition));
    move();

}

void RoboClawUART::resetEncoders() {

    this->roboclaw->ResetEncoders(this->address);


}

void RoboClawUART::setSpeed(int speed) {
    this->speed = speed;
    //this->roboclaw->ForwardM1(this->address, this->speed);
}

void RoboClawUART::move() {
    // Read current position from encoder
    //while(!moveCompelte){

    int currentPosition = this->roboclaw->ReadEncM1(this->address);
    Serial.println(currentPosition);
    if(currentPosition > commandedPosition + 100) { // If we're above the target position, move backward
       // Serial.println("Moving backward");
        this->roboclaw->BackwardM1(this->address, this->speed);
    }
    else if (currentPosition < commandedPosition - 100) { // If we're below the target position, move forward
       // Serial.println("Moving forward");
        this->roboclaw->ForwardM1(this->address, this->speed);
    }
    else {
        moveComplete = true;
        this->roboclaw->ForwardM1(this->address, 0); // Stop if we're within the target range
    }

   // }
}



    