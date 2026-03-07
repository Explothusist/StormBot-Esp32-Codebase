
#pragma once

#include <StepperMotor.h>

#include "Constants.h"
#include "../Automat/command_based/Subsystem.h"


class BeltMover : public atmt::Subsystem {

    public:

    // BeltMover(StepperMotor* _StepperArm ); // Made StepperArm internal
    BeltMover(uint8_t _enPin, uint8_t _dirPin, uint8_t _stepPin, uint8_t _MS1Pin, uint8_t _MS2Pin);
    BeltMover(uint8_t _enPin, uint8_t _dirPin, uint8_t _stepPin);
    ~BeltMover(); // Now BeltMover owns StepperMotor and has to delete it

    void init() override;
    void periodic() override;


    void setDirection(int dir); // Added wrappers around StepperMotor methods for outside use (see Stormot.robotInit())
    void setDistance(int distance);

    bool update();

    void setSpeed(int _speed);
    
    bool moveComplete();

    void moveLeft(int _moveDistance);
    void moveRight(int _moveDistance);

    // StepperMotor* StepperArm = nullptr; // Moved to private


    
    int lastMoveDistance = 0; // Last commanded distance
    bool direction = false;

    private:

    StepperMotor* StepperArm = nullptr;


    int speed =  150;// StepperSpeeds::FAST;


    
 

    

};
