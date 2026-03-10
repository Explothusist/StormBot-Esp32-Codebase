
#include "Vacuum.h"


// Vacuum::Vacuum(DcMotor _vacuumDriver){

//     vacuumDriver = new DcMotor(_vacuumDriver);
// }
Vacuum::Vacuum(int _pwmPin1, int _pwmPin2, int _enPin1, int _enPin2):
    vacuumDriver{ new DcMotor(_pwmPin1, _pwmPin2, _enPin1, _enPin2) }
{

}
Vacuum::Vacuum(int _pwmPin1,int _pwmPin2):
    Vacuum(_pwmPin1, _pwmPin2, 0, 0)
{

}

void Vacuum::init(){

    vacuumDriver->init();
};
void Vacuum::periodic() {

};

void Vacuum::setSpeed(int _speed){

    if(_speed < 0) _speed = -_speed;

    //compressorDriver->setSpeed(_speed);
    speed = _speed;
}
void Vacuum::enableVacuum(){
    vacuumDriver->setSpeed(speed);
}

void Vacuum::disableVacuum(){
    vacuumDriver->setSpeed(0);
}

