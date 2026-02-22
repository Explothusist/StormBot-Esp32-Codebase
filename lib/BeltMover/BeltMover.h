#pragma once
#include <StepperMotor.h>


class BeltMover {

    public:

    BeltMover(StepperMotor* _StepperArm );

    void init();


    bool update();

    void setSpeed(int _speed);
    

    void moveLeft(int _moveDistance);
    void moveRight(int _moveDistance);

    StepperMotor* StepperArm = nullptr;


    
    int lastMoveDistance = 0; // Last commanded distance
    bool direction = false;

    private:


    int speed = StepperMotor::FAST;


    
 

    

};
