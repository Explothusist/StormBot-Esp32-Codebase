#pragma once

#include <Arduino.h>
#include "../src/Automat/Subsystem.h"

class DcMotor : public atmt::Subsystem {
    public:
    DcMotor(int _pwmPin1,int _pwmPin2 , int _enPin1 = 0, int _enPin2 = 0);

    DcMotor(int _pwmPin1,int _pwmPin2);

    void init() override;
    void periodic() override;

    void setSpeed(int speed); // -255 to 255

    void enableMotors(); // TODO

    private:

    int pwmPin1 = 0;
    int pwmPin2 = 0;
    int enPin1 = 0;
    int enPin2 = 0;

    int speed = 0;

};