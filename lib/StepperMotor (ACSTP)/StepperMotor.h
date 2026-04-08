#pragma once
#include <Arduino.h>
#include <AccelStepper.h>

#include "Constants.h"

/*

class StepperMotor {


    public:
        // Moved to Constants
        // enum Speeds : uint32_t {
        //     FAST = 150,
        //     MEDIUM = 300,
        //     SLOW = 600,
        //     SUPERSLOW = 1000
        // } speed;

        StepperMotor(uint8_t enPin, uint8_t dirPin, uint8_t stepPin, uint8_t ms1Pin, uint8_t ms2Pin);
        StepperMotor(uint8_t enPin, uint8_t dirPin, uint8_t stepPin);

        // Must be called once at startup after construction.
        void init();

        // dir != 0 => forward, dir == 0 => backward (relative to wiring).
        void setDirection(int dir);

        // Speed in MICROSECONDS PER STEP.
        // Example: 150 = very fast, 650 = medium, 1000 = slow.
        void setSpeed(int microsecondsPerStep);

        // Relative move in steps (sign comes from setDirection()).
        void setDistance(int distance);

        void setCurrentDistance(int currDistance);

        // True when there is no remaining distance to go.
        bool moveComplete();

        // Call as often as possible to advance motion.
        void updateStepper();

        int16_t getCurrentDistance();
        int getToDistance();
        void home(int height);

        // Invert logical direction (useful if wiring is flipped).
        void invertDrive(bool invert);

    void move();

    private:
        AccelStepper stepper;

        uint8_t enPin = 0;
        uint8_t dirPin = 0;
        uint8_t stepPin = 0;
        uint8_t ms1Pin = 0;
        uint8_t ms2Pin  = 0;

        int toDistance = 0;
        bool invertDirection = false;
        bool resetHome = false;
        bool hasTarget = false;

        int speedSettingUs = consts::slide::MEDIUM; // microseconds per step
        int directionSign = 1;
        float speedStepsPerSecond = 0.0f;

        float toStepsPerSecond(int microsecondsPerStep) const;
        void applySpeed();
};


*/