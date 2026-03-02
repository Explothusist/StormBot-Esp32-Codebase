#pragma once

#include <Arduino.h>
#include <DcMotor.h>

#include "Automat/Subsystem.h"

class Compressor : public atmt::Subsystem {
    public:
    // Compressor(DcMotor _compressorDriver); // Making DCMotor internal
    Compressor(int _pwmPin1,int _pwmPin2 , int _enPin1, int _enPin2);
    Compressor(int _pwmPin1,int _pwmPin2);


    void init() override;
    void periodic() override;

    void setSpeed(int speed); // 0 to 255

    void enableCompressor(); // TODO

    private:

    int speed = 0;

    DcMotor* compressorDriver = nullptr;

};