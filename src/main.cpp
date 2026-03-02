#include "main.h"
#include "StepperMotor.h"
//int LoadEN = 48; int LoadSTEP = 45; int LoadDIR = 46;

//  int BuildEN = 34, BuildSTEP = 33, BuildDIR = 47;

constexpr uint8_t BELT_EN_PIN = 34;
constexpr uint8_t BELT_DIR_PIN = 47;
constexpr uint8_t BELT_STEP_PIN = 33;

StepperMotor stepperArm(BELT_EN_PIN, BELT_DIR_PIN, BELT_STEP_PIN);









void mapFunction(){

  switch(sD.Direction[0]){
    case 0: // Stop
 
    break;
    case 1: // Forward
       Serial.println("Moving forward with magnitude: ");
        stepperArm.setDirection(1);
      if (stepperArm.moveComplete()) {
        stepperArm.setDistance(1000); // Move 1000 steps forward as a test
      }

    break;
    case 2: // Backward
       Serial.println("Moving backward with magnitude: ");
      stepperArm.setDirection(0);
      if (stepperArm.moveComplete()) {
        stepperArm.setDistance(-1000); // Move 1000 steps backward as a test
      }

    break;
    case 3: // Left

    break;
    case 4: // Right

    break;
    default:

    break;

  };

}


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Starting up...");
  // Initialize belt mover
  stepperArm.init();
  stepperArm.setSpeed(StepperMotor::MEDIUM);
  stepperArm.setDirection(1); // Set initial direction to forward
  stepperArm.setDistance(1000); // Move 1000 steps forward as a test

  WiFi.mode(WIFI_MODE_STA);
  WiFi.disconnect();
  ESPNow.init();
  WiFi.macAddress(macAddress); 
  WiFi.setTxPower(WIFI_POWER_19dBm);
  ESPNow.reg_recv_cb(onReceive);

   // Initialize ESP-NOW
  if (esp_now_init() != ESP_OK) {
   Serial.println("Error initializing ESP-NOW");
    return;
  }
  ESPNow.add_peer((uint8_t*)broadcastAddress,0); 


}

void loop() {
  stepperArm.updateStepper();

  if(timeout > 0){

    mapFunction();
    timeout--;
    delayMicroseconds(500);
  }
  else{
   Serial.println("No response received, waiting...");

    waitingForResponse();
  }

}
