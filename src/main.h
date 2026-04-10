
#include "stormbot_type.h"
#ifdef STORMBOT_ESPNOW_CONTROLLER_
#include <Arduino.h>

#include <WiFi.h>
#include "EspNowEZ.h"
#include <esp_now.h>
#include <esp_system.h>
#include "esp_wifi.h"

 #include "../Automat/automat.h"


const uint8_t broadcastAddress[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
int timeout = 0;
bool beat_joystick_heart = false;
bool receivedRemoteSignal = false; 
volatile bool pendingPeerAdd = false;
uint8_t pendingPeerMac[6] = {0, 0, 0, 0, 0, 0};

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





Container message;
uint8_t macAddress[6];
//Message msg;
ControlData lastControlPackage; // Renamed for clarity

bool consumePendingPeer(uint8_t outMac[6]) {
  if (!pendingPeerAdd) {
    return false;
  }

  noInterrupts();
  memcpy(outMac, pendingPeerMac, 6);
  pendingPeerAdd = false;
  interrupts();
  return true;
}

typedef enum {
  EspNow_Released = 0,
  EspNow_Pressed = 1
} EspNowButtonState;

typedef enum {
  EspNow_Center = 0,
  EspNow_Up = 1,
  EspNow_Down = 2,
  EspNow_Left = 3,
  EspNow_Right = 4
} EspNowAxisState;

atmt::ButtonEvent getButtonEvent(bool esp_now_state) {
    // EspNowButtonState state = static_cast<EspNowButtonState>(esp_now_state);
    EspNowButtonState state;
    if (esp_now_state) {
        state = EspNow_Released;
    } else {
        state = EspNow_Pressed;
    }

    switch (state) {
        case EspNow_Released:
            return atmt::ButtonReleased;
        case EspNow_Pressed:
            return atmt::ButtonPressed;
        
        default:
            return atmt::ButtonReleased;
    }
};
void setJoystickAxis(int esp_now_direction, double &axis_x, double &axis_y) {
    EspNowAxisState direction = static_cast<EspNowAxisState>(esp_now_direction);
    switch (direction) {
        case EspNow_Center:
            axis_x = 50;
            axis_y = 50;
            return;
        case EspNow_Up:
            axis_x = 50;
            axis_y = 100;
            return;
        case EspNow_Down:
            axis_x = 50;
            axis_y = 0;
            return;
        case EspNow_Left:
            axis_x = 0;
            axis_y = 50;
            return;
        case EspNow_Right:
            axis_x = 100;
            axis_y = 50;
            return;
        
        default:
            axis_x = 50;
            axis_y = 50;
            return;
    }
};

atmt::JoystickState controlDataToJoystickState(ControlData data) {
    atmt::JoystickState state;

    state.axis_range[0] = 0;
    state.axis_range[1] = 100;

    state.buttons[atmt::LeftButton] = getButtonEvent(lastControlPackage.objectArm[0]);
    state.buttons[atmt::RightButton] = getButtonEvent(lastControlPackage.objectArm[2]);
    state.buttons[atmt::AButton] = getButtonEvent(lastControlPackage.objectRun[0]);
    state.buttons[atmt::BButton] = getButtonEvent(lastControlPackage.objectRun[2]);

    setJoystickAxis(lastControlPackage.Direction[0], state.axes[atmt::LXAxis], state.axes[atmt::LYAxis]);
    setJoystickAxis(lastControlPackage.Direction[1], state.axes[atmt::RXAxis], state.axes[atmt::RYAxis]);

    /* Ancient */
    // state.buttons[atmt::LeftButton] = lastControlPackage.objectArm[0]; // Left Bottom Button - Grabber   Vaccum Pumps
    // state.buttons[atmt::RightButton] = lastControlPackage.objectArm[2];
    // state.buttons[atmt::AButton] = lastControlPackage.objectRun[0];
    // state.buttons[atmt::BButton] = lastControlPackage.objectRun[2];

    /* Merely Old */
    // if (lastControlPackage.objectArm[0] == EspNow_Pressed) {
    //     state.buttons[atmt::LeftButton] = atmt::ButtonPressed;
    // }else {
    //     state.buttons[atmt::LeftButton] = atmt::ButtonReleased;
    // }
    // if (lastControlPackage.objectArm[2] == EspNow_Pressed) {
    //     state.buttons[atmt::RightButton] = atmt::ButtonPressed;
    // }else {
    //     state.buttons[atmt::RightButton] = atmt::ButtonReleased;
    // }
    // if (lastControlPackage.objectRun[0] == EspNow_Pressed) {
    //     state.buttons[atmt::AButton] = atmt::ButtonPressed;
    // }else {
    //     state.buttons[atmt::AButton] = atmt::ButtonReleased;
    // }
    // if (lastControlPackage.objectRun[2] == EspNow_Pressed) {
    //     state.buttons[atmt::BButton] = atmt::ButtonPressed;
    // }else {
    //     state.buttons[atmt::BButton] = atmt::ButtonReleased;
    // }

    /* Dawn of Time */
    // The job that these lines tried to do is done correctly by the lines below
    // // Left Axis
    // state.axes[atmt::LeftStick] = lastControlPackage.Direction[0];
    // state.axes[atmt::RightStick] = lastControlPackage.Direction[1];
    
    /* Ancient */
    // if (!lastControlPackage.Direction[0]){ // Middle
    //     state.axes[atmt::LXAxis] = 50;
    //     state.axes[atmt::LYAxis] = 50;
    // }
    // else if (lastControlPackage.Direction[0] > 0 && lastControlPackage.Direction[0] <= 2){ // Forward or Backward
    //     state.axes[atmt::LYAxis] = lastControlPackage.Direction[0] == 1 ? 100 : 0 ;
    //     state.axes[atmt::LXAxis] = 50;
    // }
    // else if (lastControlPackage.Direction[0] > 2){ // Left or Right
    //     state.axes[atmt::LXAxis] = lastControlPackage.Direction[0] == 3 ? 100 : 0 ;
    //     state.axes[atmt::LYAxis] = 50;
    // }
    // if (!lastControlPackage.Direction[1]){ // Middle
    //     state.axes[atmt::RXAxis] = 50;
    //     state.axes[atmt::RYAxis] = 50;
    // }
    // else if (lastControlPackage.Direction[1] > 0 && lastControlPackage.Direction[1] <= 2){ // Forward or Backward
    //     state.axes[atmt::RYAxis] = lastControlPackage.Direction[1] == 1 ? 100 : 0 ;
    //     state.axes[atmt::RXAxis] = 50;
    // }
    // else if (lastControlPackage.Direction[1] > 2){ // Left or Right
    //     state.axes[atmt::RXAxis] = lastControlPackage.Direction[1] == 3 ? 100 : 0 ;
    //     state.axes[atmt::RYAxis] = 50;
    // }

    return state;
};

bool waitingForResponse(){

 

  //message.store(msg); 
  //message.printBytes();
  int result = esp_now_send(broadcastAddress, (uint8_t*) &id, sizeof(id) );
  //int result = ESPNow.broadcastMessage(message);
  //result == ESP_OK ? digitalWrite(LED1, !digitalRead(LED1)) : digitalWrite(LED1, LOW);

  result == ESP_OK ? Serial.println("Sent successfully"): Serial.printf("Print failure %02x", ESP_OK);

  Serial.println("Result Status: " + String(result));
//   delay(250);


  return(true);

}

// void onReceive(const esp_now_recv_info *mac_info, const uint8_t *incomingData, int len) {
void onReceive(const uint8_t *mac_info, const uint8_t *incomingData, int len) {
  // const uint8_t *recv_info = mac_info->src_addr;
  
  if (len == sizeof(ControlData)) {
    //Serial.println("Data received from remote!"); 
    ESPNow.remoteConnected = true;
    memcpy(&lastControlPackage, incomingData, sizeof(ControlData));
    memcpy(pendingPeerMac, lastControlPackage.macHandshake, 6);
    pendingPeerAdd = true;
    

    timeout = 300;
    beat_joystick_heart = true;

    if (lastControlPackage.macHandshake[5] == macAddress[5]
      && lastControlPackage.macHandshake[4] == macAddress[4]
      && lastControlPackage.macHandshake[3] == macAddress[3]
      ) {
        
    }
  }


}
#endif
