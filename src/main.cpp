#include <Arduino.h>
#include <WiFi.h>
#include <ArduinoHA.h>
#include <Button2.h>

/*
  To include with credentials. This is what you need to do:

  1. Create a file called "Secret.h" in the same folder.
  2. Place the following text in the file:

#define ssid         "your_ssid"                     // replace with your WiFi SSID
#define password     "your_password"                 // replace with your WiFi password
#define mqttBrokerIp IPAddress(your,mqtt,broker,ip)  // replace with your MQTT broker IP address
#define mqttUser     "your_mqtt_user"                // replace with your credentials
#define mqttPassword "your_mqtt_password"            // replace with your credentials

  3. Save.
*/
#include "Secret.h"

#define ledPin    LED_BUILTIN
#define btnPin    0
#define haBtnName "LedBtn"

Button2 ledBtn;

WiFiClient client;
HADevice   device;
HAMqtt     mqtt(client, device);

HASwitch ledSw("LedSw");  // "myledSw" is a unique ID as a part of MQTT topic that will be used to control the switch.

HADeviceTrigger toggleLedBtn(HADeviceTrigger::ButtonShortPressType, haBtnName);  // You have to add automation in Home Assistant to handle this trigger

void toggleLed(Button2& btn) {
    Serial.println("tap");
    toggleLedBtn.trigger();
    digitalWrite(ledPin, !digitalRead(ledPin));  // Uncomment this line to toggle the LED while offline
}

void onSwitchCommand(bool state, HASwitch* sender) {
    digitalWrite(ledPin, (state ? HIGH : LOW));
    sender->setState(state);  // report state back to the Home Assistant
}

void setup() {
    Serial.begin(115200);
    pinMode(ledPin, OUTPUT);
    digitalWrite(ledPin, LOW);

    ledBtn.begin(btnPin);
    ledBtn.setTapHandler(toggleLed);

    byte mac[6];
    WiFi.macAddress(mac);
    device.setUniqueId(mac, sizeof(mac));
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    device.setName("My ESP32");          // Device name
    device.setSoftwareVersion("1.0.0");  // Device software version
    ledSw.setName("LED Switch");         // Switch name
    ledSw.onCommand(onSwitchCommand);

    mqtt.begin(mqttBrokerIp, mqttUser, mqttPassword);
}

void loop() {
    mqtt.loop();
    ledBtn.loop();
}
