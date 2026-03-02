#pragma once

#include <Arduino.h>
#include <DcMotor.h>

#include "Automat/Subsystem.h"

class Vacuum : public atmt::Subsystem {
    public:
    // Vacuum(DcMotor _vacuumDriver); // Made DCMotor internal
    Vacuum(int _pwmPin1,int _pwmPin2 , int _enPin1, int _enPin2);
    Vacuum(int _pwmPin1,int _pwmPin2);


    void init() override;
    void periodic() override;

    void setSpeed(int speed); // 0 to 255

    void enableVacuum(); // TODO

    void disableVacuum(); // TODO

    private:

    int speed = 0;

    DcMotor* vacuumDriver = nullptr;

};