#pragma once

#include <Arduino.h>
#include <DcMotor.h>

#include "../Automat/command_based/Subsystem.h"
#include <Constants.h>
class Vacuum : public atmt::Subsystem {
    public:
    // Vacuum(DcMotor _vacuumDriver); // Made DCMotor internal
    Vacuum(int _pwmPin1,int _pwmPin2 , int _enPin1, int _enPin2);
    Vacuum(int _pwmPin1,int _pwmPin2);


    void init() override;
    void systemPeriodic() override;
    void disabledPeriodic() override;
    void autonomousPeriodic() override;
    void teleopPeriodic() override;
    

    void setSpeed(int speed); // 0 to 255

    void enableVacuum(); // TODO

    void disableVacuum(); // TODO

    
    bool getState(); 

    void setState(bool _state); // Maybe not needed, but we will see
    private:

    int speed = consts::vacuum::speed;

    bool state = false;

    DcMotor* vacuumDriver = nullptr;

};