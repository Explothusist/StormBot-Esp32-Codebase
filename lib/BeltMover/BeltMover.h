#pragma once
#include <StepperMotor.h>
#include "../src/Automat/Subsystem.h"


class BeltMover : public atmt::Subsystem {

    public:

    BeltMover(StepperMotor* _StepperArm );

    void init() override;
    void periodic() override;


    bool update();

    void setSpeed(int _speed);
    




    StepperMotor* StepperArm = nullptr;


    
    int moveDistance = 0; // Update using main
    bool direction = false;

    private:


    int speed = StepperMotor::FAST;


    
 

    

};
