#pragma once

#include <Arduino.h>
#include <DcMotor.h>

class Compressor {
    public:
    Compressor(DcMotor _compressorDriver);


    void init();

    void setSpeed(int speed); // 0 to 255

    void enableCompressor(); // TODO

    private:

    int speed = 0;

    DcMotor* compressorDriver = nullptr;

};