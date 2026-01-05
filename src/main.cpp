#include "main.h"



Compressor* compressor = new Compressor(DcMotor(25,26,27)); // PWM1, PWM2, EN1, EN2
Vacuum* vacuumPump = new Vacuum(DcMotor(14,12,13)); // PWM1, PWM2, EN1, EN2
BeltMover* beltMover = new BeltMover(new StepperMotor(33,32,15)); // EN, DIR, STEP


void mapFunction(){
//  Serial.println("Mapping");
// Put ALL mapping from the remote here.. (Turn on compressor, vacuum pump, and stepper drive, etc here)
} 


void setup() {
  // put your setup code here, to run once:
  compressor->init();
  vacuumPump->init();
  beltMover->init();

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
  // put your main code here, to run repeatedly:
}
