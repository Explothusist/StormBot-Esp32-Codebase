
#include "StormBot.h"

StormBot m_robot{ StormBot() }; // Bindings and init configured here

void setup() {

    // atmt::systemWait(10000);

    atmt::platform_println("Starting");

    m_robot.startLoop();

    // atmt::platform_println("Ending");
    
};

void loop() {

    m_robot.runLoop();

};
