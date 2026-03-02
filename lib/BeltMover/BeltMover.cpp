#include "BeltMover.h"


BeltMover::BeltMover(StepperMotor* _StepperArm ){

StepperArm = _StepperArm;

}

void BeltMover::init(){
    StepperArm->init();
    setSpeed(speed);



}


bool BeltMover::update(){

        
    StepperArm->setDirection(direction);
    StepperArm->updateStepper();
    return true;
}

void BeltMover::setSpeed (int _speed){

    speed = _speed;
    StepperArm->setSpeed(_speed);

}

void BeltMover::moveLeft(int _moveDistance){
    direction = false;
    StepperArm->setDirection(direction);
     lastMoveDistance = _moveDistance;
    StepperArm->setDistance(_moveDistance);

    while(!StepperArm->moveComplete()){
        StepperArm->updateStepper();
    }
    
}

void BeltMover::moveRight(int _moveDistance){
    direction = true;
    StepperArm->setDirection(direction);
     lastMoveDistance = _moveDistance;
    StepperArm->setDistance(_moveDistance);

    while(!StepperArm->moveComplete()){
        StepperArm->updateStepper();
    }
    
}
