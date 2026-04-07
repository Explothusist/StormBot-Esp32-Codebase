
#include "StormBot.h"

#include "../Automat/automat.h"
#include "stormbot_type.h"

#include "Constants.h"
#include "main.h"
#ifdef STORMBOT_ESPNOW_CONTROLLER_
#include "esp_heap_caps.h"
#endif

StormBot::StormBot():
    atmt::TimedRobot(consts::robot::AutonomousLength),
    m_bot_cont{ new RobotContainer() } // Init for belt_mover, compressor and vacuum
{

};
StormBot::~StormBot() {
    delete m_bot_cont;
    m_bot_cont = nullptr;
};

void StormBot::environmentInit() {
    
    atmt::platform_println("Environment Init!");
    
    // Register all Subsystems
    registerSubsystem(m_bot_cont->m_belt_mover);
    registerSubsystem(m_bot_cont->m_compressor);
    registerSubsystem(m_bot_cont->m_vacuum);
    registerSubsystem(m_bot_cont->m_roboClaw);


    atmt::platform_println("Subsystems Registered!");
    // Add all Joysticks
    addJoystick(m_bot_cont->m_operator_controller);



    // Add SerialReaders
    addSerialReader(m_bot_cont->m_serial_reader);

    atmt::platform_println("Environment Init Complete!");

    // Add RobotDashboardServer
#ifdef STORMBOT_ROBOT_DASHBOARD_
    addRobotDashboard(m_bot_cont->m_dashboard);
#endif

    // Add Heartbeat Helpers
    addHeartbeatMaker(m_bot_cont->m_heartbeat_sender);

    m_bot_cont->configure_auto_bindings();
    atmt::platform_println("Auto bindings configured");

    // Configure bindings
    m_bot_cont->configure_bindings(); // Bind keys added here
};

void StormBot::robotInit() {

    
#ifdef STORMBOT_ESPNOW_CONTROLLER_
    if (!heap_caps_check_integrity_all(true)) {
        atmt::platform_println("Heap corruption detected before WiFi init");
        return;
    }

    if (WiFi.getMode() != WIFI_MODE_STA) {
        WiFi.mode(WIFI_MODE_STA);
    }

    int init_result = ESPNow.init();
    if (init_result != ESP_OK && init_result != ESP_ERR_ESPNOW_EXIST) {
        atmt::platform_println("Error initializing ESP-NOW");
        return;
    }

    WiFi.macAddress(macAddress); 
    //WiFi.setTxPower(WIFI_POWER_19dBm);
    if (ESPNow.reg_recv_cb(onReceive) != ESP_OK) {
        atmt::platform_println("Error registering ESP-NOW receive callback");
        return;
    }

    if (!esp_now_is_peer_exist(broadcastAddress)) {
        ESPNow.add_peer((uint8_t*)broadcastAddress, 0);
    }
#endif

    atmt::platform_print("Robot Init Complete\n");
    
    

    
    //m_bot_cont->m_belt_mover->setSpeed(900); // Stepper Speeds dec here
    //m_bot_cont->m_belt_mover->setDistance(1000); // Move 1000 steps forward as a test


   
    
};
void StormBot::robotPeriodic() {
    // atmt::platform_print("Robot Periodic...     ");

#ifdef STORMBOT_ESPNOW_CONTROLLER_
    uint8_t new_peer_mac[6];
    if (consumePendingPeer(new_peer_mac) && !esp_now_is_peer_exist(new_peer_mac)) {
        ESPNow.add_peer(new_peer_mac);
    }

    if(timeout > 0){ // WORKING HERE
        // mapFunction(); // Instead of mapFunction, update joystick state
       //  m_bot_cont->m_operator_controller->setRobotState(atmt::RobotState::Teleop);

        m_bot_cont->m_operator_controller->updateState(controlDataToJoystickState(lastControlPackage));
        

        timeout--;

       
        // delayMicroseconds(500); // Delay handled internally to atmt::TimedRobot
    }else {
        Serial.println("No response received, waiting...");
        waitingForResponse();
       //  m_bot_cont->m_operator_controller->setRobotState(atmt::RobotState::Disabled);
    }
#endif
};
void StormBot::robotExit() {
    atmt::platform_print("Robot Exit            ");
};

void StormBot::disabledInit() {
    atmt::platform_println("Disabled Init!");
};
void StormBot::disabledPeriodic() {
 //   atmt::platform_println("Disabled Periodic...");
};
void StormBot::disabledExit() {
    atmt::platform_println("Disabled Exit");
};

void StormBot::autonomousInit() {
    atmt::platform_println("Autonomous Init!");
};
void StormBot::autonomousPeriodic() {
 //   atmt::platform_println("Autonomous Periodic...");
};
void StormBot::autonomousExit() {
    atmt::platform_println("Autonomous Exit");
};

void StormBot::teleopInit() {
    atmt::platform_println("Teleop Init!");
};
void StormBot::teleopPeriodic() {
  //  atmt::platform_println("Teleop Periodic...");
};
void StormBot::teleopExit() {
    atmt::platform_println("Teleop Exit");
};