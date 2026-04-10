#include "Extruder.h"


// Extruder::Extruder(StepperMotor* _StepperArm ){

// StepperArm = _StepperArm;

// }
Extruder::Extruder(uint8_t PWM1, uint8_t PWM2):
    m_dcMotor{ new DcMotor(PWM1, PWM2) }
{

};

Extruder::Extruder(Extruder& belt):
    m_dcMotor{ new DcMotor(*belt.m_dcMotor) }
{

};


Extruder::~Extruder() {
    delete m_dcMotor;
    m_dcMotor = nullptr;
};

void Extruder::init(){
    m_dcMotor->init();
    setSpeed(speed);



};
void Extruder::systemPeriodic() {
    
};
void Extruder::disabledPeriodic() {};
void Extruder::autonomousPeriodic() {};
void Extruder::teleopPeriodic() {};



void Extruder::stop(){
    m_dcMotor->setSpeed( 0);
}




void Extruder::setSpeed (int _speed){

    speed = _speed;
    m_dcMotor->setSpeed(_speed);

}
