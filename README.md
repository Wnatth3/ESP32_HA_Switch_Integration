# ESP32 Home Assistant Switch Integration

This sketch integrates an ESP32 with Home Assistant via MQTT, allowing control and monitoring of three switches and their associated buttons.

## Prerequisites:
- Hardware:
    - ESP32 development board
    - Three push buttons (connected to GPIO 17, 16, 4)
    - Three LEDs (connected to GPIO 23, 19, 18)
- Arduino IDE or PlatformIO
- Libraries:
    - ArduinoHA
    - Button2
    - TickTwo
- MQTT broker (e.g., Mosquitto)
- Home Assistant instance
- "Secret.h" file with WiFi and MQTT credentials (see comments below)

## Features:
- Controls three independent LEDs via physical buttons and Home Assistant switches
- Real-time state synchronization between physical buttons and Home Assistant UI.
- Each button triggers a Home Assistant device trigger for automations
- MQTT-based communication with Home Assistant using ArduinoHA
- Device availability and Last Will support for robust integration
- Periodic availability checks to maintain Home Assistant status
- Easy configuration of WiFi and MQTT credentials via "Secret.h"