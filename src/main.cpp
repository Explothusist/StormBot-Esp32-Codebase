

//int LoadEN = 48; int LoadSTEP = 45; int LoadDIR = 46;

//  int BuildEN = 34, BuildSTEP = 33, BuildDIR = 47;

// constexpr uint8_t BELT_EN_PIN = 34; // Moved to Constants
// constexpr uint8_t BELT_DIR_PIN = 47;
// constexpr uint8_t BELT_STEP_PIN = 33;

// StepperMotor stepperArm(BELT_EN_PIN, BELT_DIR_PIN, BELT_STEP_PIN); // Moved to RobotContainer








// See BeltCommand and RobotContainer.configureBindings
// void mapFunction(){

//   switch(sD.Direction[0]){
//     case 0: // Stop
 
//     break;
//     case 1: // Forward
//        Serial.println("Moving forward with magnitude: ");
//         stepperArm.setDirection(1);
//       if (stepperArm.moveComplete()) {
//         stepperArm.setDistance(1000); // Move 1000 steps forward as a test
//       }

//     break;
//     case 2: // Backward
//        Serial.println("Moving backward with magnitude: ");
//       stepperArm.setDirection(0);
//       if (stepperArm.moveComplete()) {
//         stepperArm.setDistance(-1000); // Move 1000 steps backward as a test
//       }

//     break;
//     case 3: // Left

//     break;
//     case 4: // Right

//     break;
//     default:

//     break;

//   };

// }

#include "StormBot.h"

StormBot m_robot{ StormBot() }; // Bindings and init configured here

void setup() {
    atmt::platform_println("Starting");

  


    m_robot.startLoop();

    atmt::platform_println("Ending");

  // put your setup code here, to run once:

  
  // Moved to StormBot.robotInit()
//   Serial.begin(115200);
//   Serial.println("Starting up...");

  // Initialize belt mover
//   stepperArm.init(); // Called by atmt::TimedRobot because it is a registered subsystem

  // Moved to StormBot.robotInit()
//   stepperArm.setSpeed(StepperMotor::MEDIUM);
//   stepperArm.setDirection(1); // Set initial direction to forward
//   stepperArm.setDistance(1000); // Move 1000 steps forward as a test

  // Moved to StormBot.robotInit()
//   WiFi.mode(WIFI_MODE_STA);
//   WiFi.disconnect();
//   ESPNow.init();
//   WiFi.macAddress(macAddress); 
//   WiFi.setTxPower(WIFI_POWER_19dBm);
//   ESPNow.reg_recv_cb(onReceive);

  // Moved to StormBot.robotInit()
   // Initialize ESP-NOW
//   if (esp_now_init() != ESP_OK) {
//    Serial.println("Error initializing ESP-NOW");
//     return;
//   }
//   ESPNow.add_peer((uint8_t*)broadcastAddress,0);

}

void loop() {
    //m_robot.robotPeriodic();
    //m_robot.robotInternal(); 
    // Moved to StormBot.robotPeriodic
//   if(timeout > 0){

//     mapFunction();
//     timeout--;
//     delayMicroseconds(500);
//   }
//   else{
//    Serial.println("No response received, waiting...");

//     waitingForResponse();
//   }

}
