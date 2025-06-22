# ESP32 Home Assistant Switch Integration

This sketch connects an ESP32 to WiFi and integrates it with Home Assistant via MQTT.
It exposes a switch entity and a button trigger for automations.

## Prerequisites:
- ESP32 board
- Arduino IDE with ESP32 board support
- Libraries:
    - WiFi.h
    - ArduinoHA
    - Button2
- MQTT broker (e.g., Mosquitto)
- Home Assistant instance

## Features:
- Connects ESP32 to WiFi and MQTT broker
- Exposes a switch entity controllable from Home Assistant
- Reports switch state changes to Home Assistant
- Button press on ESP32 triggers a Home Assistant automation event
- Local LED control via button and Home Assistant
