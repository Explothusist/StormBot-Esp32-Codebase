
#include "StormBot.h"

#include "Automat/automat.h"

StormBot::StormBot():
    atmt::TimedRobot(30.0), // Seconds
    m_bot_cont{ new RobotContainer() }
{
    // Register all Subsystems
    registerSubsystem(m_bot_cont->m_compressor);
    registerSubsystem(m_bot_cont->m_beltMover);
    registerSubsystem(m_bot_cont->m_vacuumPump);
    registerSubsystem(m_bot_cont->m_motor);

    // Add all Joysticks
    addJoystick(m_bot_cont->m_operator_controller);

    // Configure bindings
    m_bot_cont->configure_bindings();
};
StormBot::~StormBot() {
    delete m_bot_cont;
    m_bot_cont = nullptr;
};

void StormBot::robotInit() {
    atmt::platform_print("Robot Init!");

    // compressor->init(); // Run automatically because they are registered subsystems
    // vacuumPump->init();
    // beltMover->init();

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
};
void StormBot::robotPeriodic() {
    atmt::platform_print("Robot Periodic...");
};
void StormBot::robotExit() {
    atmt::platform_print("Robot Exit");
};

void StormBot::disabledInit() {
    atmt::platform_print("Disabled Init!");
};
void StormBot::disabledPeriodic() {
    atmt::platform_print("Disabled Periodic...");
};
void StormBot::disabledExit() {
    atmt::platform_print("Disabled Exit");
};

void StormBot::autonomousInit() {
    atmt::platform_print("Autonomous Init!");
};
void StormBot::autonomousPeriodic() {
    atmt::platform_print("Autonomous Periodic...");
};
void StormBot::autonomousExit() {
    atmt::platform_print("Autonomous Exit");
};

void StormBot::teleopInit() {
    atmt::platform_print("Teleop Init!");
};
void StormBot::teleopPeriodic() {
    atmt::platform_print("Teleop Periodic...");
};
void StormBot::teleopExit() {
    atmt::platform_print("Teleop Exit");
};