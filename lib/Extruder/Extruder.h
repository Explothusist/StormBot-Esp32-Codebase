
#pragma once

//#include <FastStepperMotor.h>
#include "DcMotor.h"
#include "Constants.h"
#include "../Automat/command_based/Subsystem.h"


class Extruder : public atmt::Subsystem {

    public:

    // Extruder(StepperMotor* _StepperArm ); // Made StepperArm internal
    Extruder(uint8_t PWM1, uint8_t PWM2);
    Extruder(Extruder& belt);
    ~Extruder(); // Now Extruder owns StepperMotor and has to delete it

    void init() override;
    void systemPeriodic() override;
    void disabledPeriodic() override;
    void autonomousPeriodic() override;
    void teleopPeriodic() override;


    void setSpeed(int _speed);
    

    void stop();
    // StepperMotor* StepperArm = nullptr; // Moved to private


    
    int lastMoveDistance = 0; // Last commanded distance
    bool direction = false;

    private:

    //FastStepperMotor* StepperArm = nullptr;

    DcMotor* m_dcMotor = nullptr;


    int speed = 0; // Start disabled to avoid driving hardware during boot


    
 

    

};
