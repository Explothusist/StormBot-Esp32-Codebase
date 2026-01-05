#include "DCMotor.h"


DcMotor::DcMotor(int _pwmPin1,int _pwmPin2 , int _enPin1 , int _enPin2 ){

    pwmPin1 = _pwmPin1;
    pwmPin2 = _pwmPin2;

    if(_enPin1) enPin1 = _enPin1;
    if(_enPin2) enPin2 = _enPin2;

}

DcMotor::DcMotor(int _pwmPin1,int _pwmPin2 ){

    pwmPin1 = _pwmPin1;
    pwmPin2 = _pwmPin2;

}

void DcMotor::init(){

    pinMode(pwmPin1, OUTPUT);
    pinMode(pwmPin2, OUTPUT);

    if(enPin1){
        pinMode(enPin1, OUTPUT);
        digitalWrite(enPin1, HIGH);
    }
    if(enPin2){
        pinMode(enPin2, OUTPUT);
        digitalWrite(enPin2, HIGH);
    }
}


void DcMotor::setSpeed(int _speed){
    if(_speed >= 0){
        analogWrite(pwmPin1, _speed);
        analogWrite(pwmPin2, 0);
    }
    else{
        analogWrite(pwmPin1, 0);
        analogWrite(pwmPin2, -_speed);
    }

    speed = _speed;
}
