#include "BeltMover.h"


BeltMover::BeltMover(StepperMotor* _StepperArm ){

StepperArm = _StepperArm;

}

void BeltMover::init(){ // Runs once when startLoop() is called
    StepperArm->init();
    setSpeed(speed);



}

void BeltMover::periodic() { // Runs continuously while robot is enabled

};


bool BeltMover::update(){

        
    StepperArm->setDirection(direction);
    StepperArm->updateStepper();
    return true;
}

void BeltMover::setSpeed (int _speed){

    speed = _speed;
    StepperArm->setSpeed(_speed);

}

