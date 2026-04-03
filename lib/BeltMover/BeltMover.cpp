#include "BeltMover.h"


// BeltMover::BeltMover(StepperMotor* _StepperArm ){

// StepperArm = _StepperArm;

// }
BeltMover::BeltMover(uint8_t PWM1, uint8_t PWM2):
    m_dcMotor{ new DcMotor(PWM1, PWM2) }
{

};

BeltMover::BeltMover(BeltMover& belt):
    m_dcMotor{ new DcMotor(*belt.m_dcMotor) }
{

};


BeltMover::~BeltMover() {
    delete m_dcMotor;
    m_dcMotor = nullptr;
};

void BeltMover::init(){
    m_dcMotor->init();
    setSpeed(speed);



};

void BeltMover::periodic(){

}



void BeltMover::stop(){
    m_dcMotor->setSpeed( 0);
}




void BeltMover::setSpeed (int _speed){

    speed = _speed;
    m_dcMotor->setSpeed(_speed);

}
