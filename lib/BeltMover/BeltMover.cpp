#include "BeltMover.h"


// BeltMover::BeltMover(StepperMotor* _StepperArm ){

// StepperArm = _StepperArm;

// }
BeltMover::BeltMover(uint8_t _enPin, uint8_t _dirPin, uint8_t _stepPin, uint8_t _MS1Pin, uint8_t _MS2Pin):
    StepperArm{ new FastStepperMotor(_enPin, _dirPin, _stepPin, _MS1Pin, _MS2Pin) }
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



};
void BeltMover::systemPeriodic() {
    
};
void BeltMover::disabledPeriodic() {};
void BeltMover::autonomousPeriodic() {};
void BeltMover::teleopPeriodic() {};

void BeltMover::moveToSide(FastStepperMotor::Side side){
    Serial.println("Moving to side: " + String(side));
    StepperArm->moveToSide(side);
}


void BeltMover::moveLeft(){

    StepperArm->moveForward();
}


void BeltMover::moveRight(){

    StepperArm->moveBackward();
}

void BeltMover::stop(){
    StepperArm->stopMotor();
}

void BeltMover::setDistance(int distance) {
    
};

bool BeltMover::moveComplete() {
    return StepperArm->moveComplete();
};

bool BeltMover::update(){

        
    return true;
}

void BeltMover::setSpeed (int _speed){

    speed = _speed;
    StepperArm->setSpeed(_speed);

}
