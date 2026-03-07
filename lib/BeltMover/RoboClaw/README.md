# RoboClaw UART Helper (ESP32 / Arduino)

This small helper wraps the BasicMicro RoboClaw packet-serial protocol over a `HardwareSerial` port.

It does **not** hard-code any command table. You pass the command byte and data bytes according to the official RoboClaw documentation.

## Typical Wiring (ESP32)

- Use one of the ESP32 UARTs (e.g. `Serial2`).
- Connect:
  - ESP32 TX (e.g. GPIO17) → RoboClaw S1 signal
  - ESP32 RX (e.g. GPIO16) → RoboClaw S2 signal
  - Common GND between ESP32 and RoboClaw
- In Motion Studio, set **Control Mode** to *Packet Serial*, choose a **baud rate** and **packet address** (e.g. 38400 baud, address 0x80).

## Basic Use

```cpp
#include <Arduino.h>
#include "RoboClawUART.h"

// Example pins; adjust to your board
static constexpr int ROBOCLAW_RX_PIN = 16;  // ESP32 RX (into S2)
static constexpr int ROBOCLAW_TX_PIN = 17;  // ESP32 TX (from S1)

RoboClawUART roboclaw(Serial2, 0x80);  // 0x80 = default address from Motion Studio

void setup() {
  Serial.begin(115200);

  // Configure the UART used for RoboClaw
  Serial2.begin(38400, SERIAL_8N1, ROBOCLAW_RX_PIN, ROBOCLAW_TX_PIN);

  // Example: send a command with one data byte
  // You must look up the correct command values in the RoboClaw manual.
  const uint8_t command = 0x00;  // e.g. M1 forward (verify in docs!)
  uint8_t speed = 64;            // 0-127 as defined by the chosen command

  roboclaw.sendCommand(command, &speed, 1);
}

void loop() {
}
```

## Notes

- `sendCommand` automatically prefixes packets with the configured address and appends a CRC-16-CCITT checksum.
- Use `sendCommandWithResponse` if you need to read a fixed-length reply; parse it according to the RoboClaw documentation.
- For the full list of commands and argument formats, refer to BasicMicro's official RoboClaw manual and examples.
