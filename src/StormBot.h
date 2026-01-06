#pragma once

#include "Automat/automat.h"
#include "RobotContainer.h"
#include <Arduino.h>
#include "BeltMover.h"
#include "Compressor.h"
#include "Vacuum.h"
#include <WiFi.h>
#include "EspNowEZ.h"
#include <esp_now.h>
#include <esp_system.h>
#include "esp_wifi.h"

const uint8_t broadcastAddress[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
int timeout = 0;
bool receivedRemoteSignal = false; 

const char id[20] = "STORM";

struct __attribute__((packed)) sendData{
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


Container message;
uint8_t macAddress[6];
//Message msg;
sendData sD;
bool waitingForResponse(){

 

  //message.store(msg); 
  //message.printBytes();
  int result = esp_now_send(broadcastAddress, (uint8_t*) &id, sizeof(id) );
  //int result = ESPNow.broadcastMessage(message);
  //result == ESP_OK ? digitalWrite(LED1, !digitalRead(LED1)) : digitalWrite(LED1, LOW);

  result == ESP_OK ? Serial.println("Sent successfully"): Serial.printf("Print failure %02x", ESP_OK);


  delay(250);


  return(true);

}

void onReceive(const esp_now_recv_info *mac_info, const uint8_t *incomingData, int len) {
  const uint8_t *recv_info = mac_info->src_addr;
  
  if (len == sizeof(sendData)) {
   // Serial.println("Data received from remote!"); 
    memcpy(&sD, incomingData, sizeof(sendData));

    if (!esp_now_is_peer_exist(sD.macHandshake)) {
  //  Serial.println("Adding peer");
    ESPNow.add_peer(sD.macHandshake);
    }
    

    timeout = 1000;

    if(sD.macHandshake[5] == macAddress[5] && sD.macHandshake[4] == macAddress[4] && sD.macHandshake[3] == macAddress[3] ){
    }

  } else {
    Serial.println(len);
  }


}

class StormBot : public atmt::TimedRobot {
    public:
        StormBot();
        ~StormBot();

        void robotInit() override;
        void robotPeriodic() override;
        void robotExit() override;
        
        void disabledInit() override;
        void disabledPeriodic() override;
        void disabledExit() override;
        
        void autonomousInit() override;
        void autonomousPeriodic() override;
        void autonomousExit() override;
        
        void teleopInit() override;
        void teleopPeriodic() override;
        void teleopExit() override;

    private:
        RobotContainer* m_bot_cont;
};
