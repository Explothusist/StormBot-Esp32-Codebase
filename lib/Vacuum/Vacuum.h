#pragma once

#include <Arduino.h>
#include <DcMotor.h>

class Vacuum {
    public:
    Vacuum(DcMotor _vacuumDriver);


    void init();

    void setSpeed(int speed); // 0 to 255

    void enableVacuum(); // TODO

    private:

    int speed = 0;

    DcMotor* vacuumDriver = nullptr;

};