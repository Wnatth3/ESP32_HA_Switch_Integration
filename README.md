# ESP32 Home Assistant Switch Integration

This sketch integrates an ESP32 with Home Assistant via MQTT, allowing control and monitoring of three switches and their associated buttons.

## Prerequisites

- **Hardware:**
    - ESP32 development board
    - Three push buttons (connected to GPIO 17, 16, 4)
    - Three LEDs (connected to GPIO 23, 19, 18)
    - Appropriate resistors and wiring

- **Software:**
    - [Arduino IDE](https://www.arduino.cc/en/software) or PlatformIO
    - ESP32 board support installed in Arduino IDE
    - Required libraries:
        - [ArduinoHA](https://github.com/dawidchyrzynski/arduino-home-assistant)
        - [Button2](https://github.com/LennartHennigs/Button2)
        - WiFi (included with ESP32 core)
        - Arduino core for ESP32

- **Configuration:**
    - Create a `Secret.h` file in the `src` directory with your WiFi and MQTT credentials as described in the code comments.

## Features

- Connects ESP32 to WiFi and MQTT broker for Home Assistant integration.
- Controls three independent LEDs via Home Assistant switches.
- Each LED can also be toggled by a physical button.
- Button presses are reported to Home Assistant as device triggers for automations.
- Real-time state synchronization between physical buttons and Home Assistant UI.
- Easily extendable for more switches/buttons.