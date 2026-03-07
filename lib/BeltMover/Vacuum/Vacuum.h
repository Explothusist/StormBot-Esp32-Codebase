#pragma once

#include <Arduino.h>
#include <DcMotor.h>



class Vacuum {
    public:
    // Vacuum(DcMotor _vacuumDriver); // Made DCMotor internal
    Vacuum(int _pwmPin1,int _pwmPin2 , int _enPin1, int _enPin2);
    Vacuum(int _pwmPin1,int _pwmPin2);


    void init();
    void periodic();

    void setSpeed(int speed); // 0 to 255

    void enableVacuum(); // TODO

    void disableVacuum(); // TODO

    private:

    float speedTicker = 0;
    int speed = 0;

    DcMotor* vacuumDriver = nullptr;

};