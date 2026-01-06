#pragma once

#include <Arduino.h>
#include <DcMotor.h>
#include "../src/Automat/Subsystem.h"

class Vacuum : public atmt::Subsystem {
    public:
    Vacuum(DcMotor _vacuumDriver);


    void init() override;
    void periodic() override;

    void setSpeed(int speed); // 0 to 255

    void enableVacuum(); // TODO

    private:

    int speed = 0;

    DcMotor* vacuumDriver = nullptr;

};