
#include "Compressor.h"


Compressor::Compressor(DcMotor _compressorDriver){

    compressorDriver = new DcMotor(_compressorDriver);
}

void Compressor::init(){ // Runs once when startLoop() is called

    compressorDriver->init();
}
void Compressor::periodic() { // Runs continuously while robot is enabled

};

void Compressor::setSpeed(int _speed){

    if(_speed < 0) _speed = -_speed;

    //compressorDriver->setSpeed(_speed);
    speed = _speed;
}
void Compressor::enableCompressor(){
    compressorDriver->setSpeed(speed);
}