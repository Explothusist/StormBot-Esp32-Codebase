#include "main.h"
#include "StormBot.h"

StormBot* m_robot{ new StormBot() };

void setup() {
  // put your setup code here, to run once:
  // Actually, put code in StormBot's various init, periodic, and exit functions
  m_robot->startLoop();
}

void loop() {
  // put your main code here, to run repeatedly:
  // Actually, put code in StormBot's various init, periodic, and exit functions
  m_robot->runLoop(); // Esp32-specific
}
