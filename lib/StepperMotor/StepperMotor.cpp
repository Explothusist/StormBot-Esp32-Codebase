#include "StepperMotor.h"

StepperMotor::StepperMotor(uint8_t _enPin, uint8_t _dirPin, uint8_t _stepPin, uint8_t _MS1Pin = 0, uint8_t _MS2Pin = 0){

    enPin = _enPin;
    dirPin = _dirPin;
    stepPin = _stepPin;

    if(_MS1Pin) MS1Pin = _MS1Pin;
    if(_MS2Pin) MS2Pin = _MS2Pin;

}

StepperMotor::StepperMotor(uint8_t _enPin, uint8_t _dirPin, uint8_t _stepPin){

    enPin = _enPin;
    dirPin = _dirPin;
    stepPin = _stepPin;

}

void StepperMotor::init(){
    

    //Set the enable high at all times, as it causes a lock to appear
   // Serial.printf("En: %d - Dir: %d - Step: %d", enPin, dirPin, stepPin);

    pinMode(enPin, OUTPUT);
    pinMode(stepPin, OUTPUT);
    pinMode(dirPin, OUTPUT);

    digitalWrite(enPin, LOW); // LOW turns the stepper motor on
    digitalWrite(dirPin, LOW);
    digitalWrite(stepPin, LOW);


}

void StepperMotor::invertDrive(bool _invert ){
    invertDirection = _invert;
}

void StepperMotor::home(int height){
   // Serial.println("Setting Home");
   currDistance = 0;
   currDistance = 0; 
   // setSpeed(MEDIUM);
    toDistance = height;
    digitalWrite(dirPin, invertDirection);
    resetHome = true;
}


void StepperMotor::setDirection(int dir){
    digitalWrite(dirPin, dir);
}

bool StepperMotor::moveComplete(){

    if(currDistance != toDistance){
        return false;
    }
    else{
        if(resetHome){
            resetHome = false;
            currDistance = 0;
        }
        return true;
    }


}

void StepperMotor::setSpeed(int _speed){
    microsecondCountDown = _speed;

}

int16_t StepperMotor::getCurrentDistance(){
    return currDistance;
}

void StepperMotor::setCurrentDistance(int _currDistance){
    currDistance = _currDistance;
}

void StepperMotor::setDistance(int _distance){ // Distance is relative 
    toDistance = _distance;
    setCurrentDistance(0);
}

int StepperMotor::getToDistance(){
    return toDistance;
}

bool StepperMotor::countDown(bool state){

    //Serial.printf(" -- ToDistance %d - Current Count - %d - Current Distance - %d", toDistance, currCount, currDistance);
    //Serial.println();
    if(state){
        if(currCount == microsecondCountDown){
            currCount = 0;
            return true;
        }
        else{
            currCount++;
            return false;
        }
    }
    else{
        if(currCount == stepRegister){
            currCount = 0;
            return true;
        }
        else{
            currCount++;
            return false;
        }
    }
}



void StepperMotor::updateStepper(){

    if(!moveComplete()){
       // Serial.println("Not finished moving");
       // Serial.printf("Curr Dist: %d , toDistance: %d", currDistance, toDistance);
      //  Serial.println();
        //    digitalWrite(dirPin, HIGH); // Low is heading downwards, high is heading upwards
        
        //digitalWrite(dirPin, HIGH);
        if(countDown(!onOrOff)){
         //   Serial.println("Stepping!");
            if(!onOrOff){
            digitalWrite(stepPin, HIGH);
            currDistance++;
            onOrOff = true;
            }
            else{
                digitalWrite(stepPin, LOW);
                onOrOff = false;
            }
            
            
            
        }

    }

}
