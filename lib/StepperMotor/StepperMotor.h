#pragma once
#include <Arduino.h>
#include <AccelStepper.h>

#include "Constants.h"



class StepperMotor {
    /*
        enum StepperSpeeds {
        FAST = 150,
        MEDIUM = 300,
        SLOW = 600,
        SUPERSLOW = 1000
    } StepSpeeds;
    */

    public:
        // Moved to Constants
        // enum Speeds : uint32_t {
        //     FAST = 150,
        //     MEDIUM = 300,
        //     SLOW = 600,
        //     SUPERSLOW = 1000
        // } speed;

        StepperMotor(uint8_t _enPin, uint8_t _dirPin, uint8_t _stepPin, uint8_t _MS1Pin, uint8_t _MS2Pin);
        StepperMotor(uint8_t _enPin, uint8_t _dirPin, uint8_t _stepPin);

        void init();

        void setDirection(int dir);
        void setSpeed(int _speed);
        void setDistance(int _distance);
        void setCurrentDistance(int _currDistance);

        bool moveComplete();
        void updateStepper();

        int16_t getCurrentDistance();
        int getToDistance();
        void home(int height);

        void invertDrive(bool _invert);

    private:
        AccelStepper stepper;

        uint8_t enPin = 0;
        uint8_t dirPin = 0;
        uint8_t stepPin = 0;
        uint8_t MS1Pin = 0;
        uint8_t MS2Pin = 0;

        int toDistance = 0;
        bool invertDirection = false;
        bool resetHome = false;
        bool hasTarget = false;

        int speedSetting = 650; //StepperSpeeds::MEDIUM;
        int directionSign = 1;
        float speedStepsPerSecond = 0.0f;

        float toStepsPerSecond(int microsecondsPerStep) const;
        void applySpeed();
};


