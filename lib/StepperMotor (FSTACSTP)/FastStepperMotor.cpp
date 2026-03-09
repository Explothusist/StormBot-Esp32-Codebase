#include "FastStepperMotor.h"

// Construct a driver-based AccelStepper with optional microstep control pins.
FastStepperMotor::FastStepperMotor(uint8_t enPin_, uint8_t dirPin_, uint8_t stepPin_, uint8_t ms1Pin_, uint8_t ms2Pin_)
    : 
      enPin{enPin_},
      dirPin{dirPin_},
      stepPin{stepPin_},
      ms1Pin{ms1Pin_},
      ms2Pin{ms2Pin_} {}

// Convenience ctor when you don't care about microstep control pins.
FastStepperMotor::FastStepperMotor(uint8_t enPin_, uint8_t dirPin_, uint8_t stepPin_)
    : FastStepperMotor(enPin_, dirPin_, stepPin_, 0, 0) {}

void FastStepperMotor::init() {
    engine.init();
    engine.setExternalCallForPin(setExternalPin);
    stepper = engine.stepperConnectToPin(stepPin);
    
    if(stepper){
        stepper->setDirectionPin(dirPin);
        stepper->setEnablePin(enPin);
        stepper->setAutoEnable(true);

        stepper->setSpeedInUs(10000);
        stepper->setAcceleration(1000);
    }

}

bool FastStepperMotor::setExternalPin(uint8_t pin, uint8_t value) {
  // This example returns the previous value of the output.
  // Consequently, FastAccelStepper needs to call setExternalPin twice
  // in order to successfully change the output value.
  pin = pin & ~PIN_EXTERNAL_FLAG;
  pinMode(pin, OUTPUT);
  bool oldValue = digitalRead(pin);
  digitalWrite(pin, value);
  return oldValue;
}

void FastStepperMotor::invertDrive(bool invert) {

}

void FastStepperMotor::home(int height) {
  
}

void FastStepperMotor::setDirection(int dir) {

}

bool FastStepperMotor::moveComplete() {
    
    return 0;
}

void FastStepperMotor::move() {
   // stepper->move()
   stepper->forwardStep(false);
   stepper->backwardStep(false);
}

void FastStepperMotor::setSpeed(int microsecondsPerStep) {

}

int16_t FastStepperMotor::getCurrentDistance() {
    return 0;
}

void FastStepperMotor::setCurrentDistance(int currDistance) {



}

void FastStepperMotor::setDistance(int distance) {
    stepper->move(distance, false);
}

int FastStepperMotor::getToDistance() {
    return toDistance;
}


float FastStepperMotor::toStepsPerSecond(int microsecondsPerStep) const {
    return 0.0f;
}

void FastStepperMotor::applySpeed() {

}
