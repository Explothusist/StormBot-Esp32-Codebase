
#include "Vacuum.h"


Vacuum::Vacuum(DcMotor _vacuumDriver){

    vacuumDriver = new DcMotor(_vacuumDriver);
}

void Vacuum::init(){

    vacuumDriver->init();
}

void Vacuum::setSpeed(int _speed){

    if(_speed < 0) _speed = -_speed;

    //compressorDriver->setSpeed(_speed);
    speed = _speed;
}
void Vacuum::enableVacuum(){
    vacuumDriver->setSpeed(speed);
}