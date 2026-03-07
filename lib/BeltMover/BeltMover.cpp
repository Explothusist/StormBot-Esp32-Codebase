#include "BeltMover.h"


// BeltMover::BeltMover(StepperMotor* _StepperArm ){

// StepperArm = _StepperArm;

// }
BeltMover::BeltMover(uint8_t _enPin, uint8_t _dirPin, uint8_t _stepPin, uint8_t _MS1Pin, uint8_t _MS2Pin):
    StepperArm{ new StepperMotor(_enPin, _dirPin, _stepPin, _MS1Pin, _MS2Pin) }
{

};
BeltMover::BeltMover(uint8_t _enPin, uint8_t _dirPin, uint8_t _stepPin):
    BeltMover(_enPin, _dirPin, _stepPin, 0, 0)
{

};
BeltMover::~BeltMover() {
    delete StepperArm;
    StepperArm = nullptr;
};

void BeltMover::init(){
    StepperArm->init();
    setSpeed(speed);



}
void BeltMover::periodic() {

};


void BeltMover::setDirection(int dir) {
    StepperArm->setDirection(dir);
};
void BeltMover::setDistance(int distance) {
    StepperArm->setDistance(distance);
};

bool BeltMover::moveComplete() {
    return StepperArm->moveComplete();
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
