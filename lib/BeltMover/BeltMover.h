#pragma once
#include <StepperMotor.h>


class BeltMover {

    public:

    BeltMover(StepperMotor* _StepperArm );

    void init();


    bool update();

    void setSpeed(int _speed);
    




    StepperMotor* StepperArm = nullptr;


    
    int moveDistance = 0; // Update using main
    bool direction = false;

    private:


    int speed = StepperMotor::FAST;


    
 

    

};
