# ESP32 Home Assistant Switch Integration

This sketch integrates an ESP32 with Home Assistant via MQTT, allowing control and monitoring of three switches (relays/LEDs) and their corresponding physical buttons.

## Prerequisites

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
- "Secret.h" file with your WiFi and MQTT credentials (see code comments for format)

## Features

- Controls three independent switches (relays/LEDs) via Home Assistant and physical buttons.
- Real-time state synchronization between physical buttons and Home Assistant UI.
- MQTT-based communication for reliable integration with Home Assistant.
- Button presses trigger Home Assistant automations using device triggers.
- Switch state synchronization between ESP32 and Home Assistant.
- Device availability reporting and Last Will support.
- Configurable relay logic (active high/low).
- Modular and easily extendable for more switches/buttons.