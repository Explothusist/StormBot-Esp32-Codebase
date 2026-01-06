
#include "Vacuum.h"


Vacuum::Vacuum(DcMotor _vacuumDriver){

    vacuumDriver = new DcMotor(_vacuumDriver);
}

void Vacuum::init() { // Runs once when startLoop() is called

    vacuumDriver->init();
}
void Vacuum::periodic() { // Runs continuously while robot is enabled
    
};

void Vacuum::setSpeed(int _speed){

    if(_speed < 0) _speed = -_speed;

    //compressorDriver->setSpeed(_speed);
    speed = _speed;
}
void Vacuum::enableVacuum(){
    vacuumDriver->setSpeed(speed);
}