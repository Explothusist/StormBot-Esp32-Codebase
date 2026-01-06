#pragma once

#include <Arduino.h>
#include <DcMotor.h>
#include "../src/Automat/Subsystem.h"

class Compressor : public atmt::Subsystem {
    public:
    Compressor(DcMotor _compressorDriver);


    void init() override;
    void periodic() override;

    void setSpeed(int speed); // 0 to 255

    void enableCompressor(); // TODO

    private:

    int speed = 0;

    DcMotor* compressorDriver = nullptr;

};