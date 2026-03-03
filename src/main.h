

#include <Arduino.h>

#include <WiFi.h>
#include "EspNowEZ.h"
#include <esp_now.h>
#include <esp_system.h>
#include "esp_wifi.h"

 #include "../Automat/automat.h"


const uint8_t broadcastAddress[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
int timeout = 0;
bool receivedRemoteSignal = false; 

const char id[20] = "STORM";

// Renamed for clarity
struct __attribute__((packed)) ControlData {
    uint8_t macHandshake[6];
    uint8_t Direction[2]; // 0,1,2,3 FWD, BWD, Left, Right

    uint8_t DcMax[2] = {255,255};
    uint8_t DcMin[2] = {0,0};
    uint8_t dcMagnitude[2] = {0,0}; //Should be between 0 and 100
    bool objectArm[6]; // For escs, arm them, for servos, set to zero degrees? or fixable value
    bool objectRun[6]; 
    float escSpeed = .25; 

    bool connectCheck = false;
};


atmt::JoystickState controlDataToJoystickState(ControlData data) {
    atmt::JoystickState state;
    // Please help me write this function, ControlData struct is confusing
    return state;
};


Container message;
uint8_t macAddress[6];
//Message msg;
ControlData lastControlPackage; // Renamed for clarity


bool waitingForResponse(){

 

  //message.store(msg); 
  //message.printBytes();
  int result = esp_now_send(broadcastAddress, (uint8_t*) &id, sizeof(id) );
  //int result = ESPNow.broadcastMessage(message);
  //result == ESP_OK ? digitalWrite(LED1, !digitalRead(LED1)) : digitalWrite(LED1, LOW);

  result == ESP_OK ? Serial.println("Sent successfully"): Serial.printf("Print failure %02x", ESP_OK);

  Serial.println("Result Status: " + String(result));
  delay(250);


  return(true);

}

void onReceive(const esp_now_recv_info *mac_info, const uint8_t *incomingData, int len) {
  const uint8_t *recv_info = mac_info->src_addr;
  
  if (len == sizeof(ControlData)) {
   // Serial.println("Data received from remote!"); 
    memcpy(&lastControlPackage, incomingData, sizeof(ControlData));

    if (!esp_now_is_peer_exist(lastControlPackage.macHandshake)) {
  //  Serial.println("Adding peer");
    ESPNow.add_peer(lastControlPackage.macHandshake);
    }
    

    timeout = 1000;

    if (lastControlPackage.macHandshake[5] == macAddress[5]
      && lastControlPackage.macHandshake[4] == macAddress[4]
      && lastControlPackage.macHandshake[3] == macAddress[3]
      ) {
        
    }

  } else {
    Serial.println(len);
  }


}
