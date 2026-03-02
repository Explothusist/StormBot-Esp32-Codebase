#pragma once

#include <Arduino.h>

class DcMotor {
    public:
    DcMotor(int _pwmPin1, int _pwmPin2 , int _enPin1, int _enPin2);
    DcMotor(int _pwmPin1, int _pwmPin2);
    DcMotor(int _pwmPin1);

    void init();

    void setSpeed(int speed); // -255 to 255

    void enableMotors(); // TODO

    private:

    int pwmPin1 = -1; // Changed 'no pin' to -1 instead of 0 (a theoretically valid pin)
    int pwmPin2 = -1;
    int enPin1 = -1;
    int enPin2 = -1;

    int speed = 0;

};