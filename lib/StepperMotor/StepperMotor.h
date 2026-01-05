#pragma once
#include <Arduino.h>


class StepperMotor{

    public: 


        enum Speeds{
            FAST = 150,
            MEDIUM = 300,
            SLOW = 600,
            SUPERSLOW = 1000

        } speed;

        

        uint8_t enPin = 0, dirPin = 0, stepPin = 0;
        uint8_t MS1Pin = NULL, MS2Pin = NULL;

        StepperMotor(uint8_t _enPin, uint8_t _dirPin, uint8_t _stepPin, uint8_t _MS1Pin , uint8_t _MS2Pin);
        StepperMotor(uint8_t _enPin, uint8_t _dirPin, uint8_t _stepPin);

        void init();

        void setDirection(int dir);

        void setSpeed(int _speed);

        void setDistance(int _distance);

        void setCurrentDistance(int _currDistance);

        bool moveComplete(); // 

        void updateStepper(); // Run this command until moveComplete is true

        int16_t getCurrentDistance();
        int getToDistance();
        void home(int height);

        void invertDrive(bool _invert );

    private:
        int toDistance = 0;
        int currDistance = 0;
        bool invertDirection = false;
        
        bool countDown(bool state);
        int microsecondCountDown = 100;
        int stepRegister = 50;
        bool onOrOff = false;
        int currCount = 0;

        bool resetHome = false;

        


};


