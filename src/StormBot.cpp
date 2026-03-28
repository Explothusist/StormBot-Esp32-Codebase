
#include "StormBot.h"

#include "../Automat/automat.h"

#include "Constants.h"
#include "main.h"

StormBot::StormBot():
    atmt::TimedRobot(consts::robot::AutonomousLength),
    m_bot_cont{ new RobotContainer() } // Init for belt_mover, compressor and vacuum
{
    // Register all Subsystems
    registerSubsystem(m_bot_cont->m_belt_mover);
    registerSubsystem(m_bot_cont->m_compressor);
    registerSubsystem(m_bot_cont->m_vacuum);
    registerSubsystem(m_bot_cont->m_roboClaw);

    // Add all Joysticks
    addJoystick(m_bot_cont->m_operator_controller);



    // Add SerialReaders
    addSerialReader(m_bot_cont->m_serial_reader);

    // Add RobotDashboardServer
    addRobotDashboard(m_bot_cont->m_dashboard);

    // Configure bindings
    m_bot_cont->configure_bindings(); // Bind keys added here
};
StormBot::~StormBot() {
    delete m_bot_cont;
    m_bot_cont = nullptr;
};

void StormBot::robotInit() {

    #ifdef AUTOMAT_ESP32_
       Serial.begin(115200);
        WiFi.mode(WIFI_MODE_STA);
        WiFi.disconnect();
        ESPNow.init();
        WiFi.macAddress(macAddress); 
        WiFi.setTxPower(WIFI_POWER_19dBm);
        ESPNow.reg_recv_cb(onReceive);
        
        if (esp_now_init() != ESP_OK) {
            Serial.println("Error initializing ESP-NOW");
            return;
        }
        ESPNow.add_peer((uint8_t*)broadcastAddress,0); 
    #endif

    atmt::platform_print("Robot Init!           ");
    
    
    Serial.println("Starting up...");
    
    m_bot_cont->m_belt_mover->setSpeed(900); // Stepper Speeds dec here
    m_bot_cont->m_belt_mover->setDistance(1000); // Move 1000 steps forward as a test


   
    
};
void StormBot::robotPeriodic() {
    //atmt::platform_print("Robot Periodic...     ");

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