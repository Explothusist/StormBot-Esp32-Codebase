
#include "Compressor.h"


// Compressor::Compressor(DcMotor _compressorDriver){

//     compressorDriver = new DcMotor(_compressorDriver);
// }
Compressor::Compressor(int _pwmPin1,int _pwmPin2 , int _enPin1, int _enPin2):
    compressorDriver{ new DcMotor(_pwmPin1, _pwmPin2, _enPin1, _enPin2) }
{

}
Compressor::Compressor(int _pwmPin1,int _pwmPin2):
    Compressor(_pwmPin1, _pwmPin2, 0, 0)
{

}

void Compressor::init(){

    compressorDriver->init();
}
void Compressor::periodic() {

};

void Compressor::setSpeed(int _speed){

    if(_speed < 0) _speed = -_speed;

    //compressorDriver->setSpeed(_speed);
    speed = _speed;
}
void Compressor::enableCompressor(){
    compressorDriver->setSpeed(speed);
}