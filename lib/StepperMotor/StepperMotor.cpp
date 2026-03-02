#include "StepperMotor.h"

StepperMotor::StepperMotor(uint8_t _enPin, uint8_t _dirPin, uint8_t _stepPin, uint8_t _MS1Pin, uint8_t _MS2Pin):
    stepper{ AccelStepper::DRIVER, _stepPin, _dirPin },
    enPin{ _enPin },
    dirPin{ _dirPin },
    stepPin{ _stepPin },
    MS1Pin{ _MS1Pin },
    MS2Pin{ _MS2Pin }
{

}

// Changed to delegating constructor
StepperMotor::StepperMotor(uint8_t _enPin, uint8_t _dirPin, uint8_t _stepPin):
    StepperMotor(_enPin, _dirPin, _stepPin, 0, 0)
{

}

void StepperMotor::init() {
    pinMode(enPin, OUTPUT);
    digitalWrite(enPin, HIGH); 

    if (MS1Pin) {
        pinMode(MS1Pin, OUTPUT);
        digitalWrite(MS1Pin, LOW);
    }
    if (MS2Pin) {
        pinMode(MS2Pin, OUTPUT);
        digitalWrite(MS2Pin, LOW);
    }

    stepper.setEnablePin(enPin);
    stepper.setPinsInverted(invertDirection, false, true);
    stepper.enableOutputs();
    applySpeed();
}

void StepperMotor::invertDrive(bool _invert) {
    invertDirection = _invert;
    stepper.setPinsInverted(invertDirection, false, true);
    applySpeed();
}

void StepperMotor::home(int height) {
    resetHome = true;
    setDirection(invertDirection ? 1 : 0);
    setDistance(height);
}

void StepperMotor::setDirection(int dir) {
    directionSign = dir ? 1 : -1;
    stepper.setSpeed(directionSign * speedStepsPerSecond);
}

bool StepperMotor::moveComplete() {
    bool done = (stepper.distanceToGo() == 0);
    if (done && resetHome) {
        resetHome = false;
        stepper.setCurrentPosition(0);
    }
    return done;
}

void StepperMotor::setSpeed(int _speed) {
    speedSetting = _speed;
    applySpeed();
}

int16_t StepperMotor::getCurrentDistance() {
    return static_cast<int16_t>(stepper.currentPosition());
}

void StepperMotor::setCurrentDistance(int _currDistance) {
    stepper.setCurrentPosition(_currDistance);
}

void StepperMotor::setDistance(int _distance) {
    toDistance = _distance;
    hasTarget = true;
    stepper.move(directionSign * _distance);
}

int StepperMotor::getToDistance() {
    return toDistance;
}

void StepperMotor::updateStepper() {
    if (hasTarget) {
        stepper.run();
        if (stepper.distanceToGo() == 0) {
            hasTarget = false;
        }
        return;
    }

    stepper.runSpeed();
}

float StepperMotor::toStepsPerSecond(int microsecondsPerStep) const {
    if (microsecondsPerStep <= 0) {
        return 0.0f;
    }
    return 1000000.0f / static_cast<float>(microsecondsPerStep);
}

void StepperMotor::applySpeed() {
    speedStepsPerSecond = toStepsPerSecond(speedSetting);
    stepper.setMaxSpeed(speedStepsPerSecond);
    stepper.setAcceleration(speedStepsPerSecond * 2.0f);
    stepper.setSpeed(directionSign * speedStepsPerSecond);
}
