
#include "Compressor.h"


Compressor::Compressor(DcMotor _compressorDriver){

    compressorDriver = new DcMotor(_compressorDriver);
}

void Compressor::init(){

    compressorDriver->init();
}

void Compressor::setSpeed(int _speed){

    if(_speed < 0) _speed = -_speed;

    //compressorDriver->setSpeed(_speed);
    speed = _speed;
}
void Compressor::enableCompressor(){
    compressorDriver->setSpeed(speed);
}