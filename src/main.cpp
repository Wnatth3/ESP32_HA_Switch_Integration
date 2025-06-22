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

#define ledPin1    18
#define btnPin1    22
#define haBtnName1 "LedBtn1"

Button2 ledBtn;
Button2 ledBtn1;

WiFiClient client;
HADevice   device;
HAMqtt     mqtt(client, device);

HASwitch ledSw("LedSw");  // "myledSw" is a unique ID as a part of MQTT topic that will be used to control the switch.
HASwitch ledSw1("LedSw1");  // "myledSw" is a unique ID as a part of MQTT topic that will be used to control the switch.

HADeviceTrigger toggleLedBtn(HADeviceTrigger::ButtonShortPressType, haBtnName);  // You have to add automation in Home Assistant to handle this trigger
HADeviceTrigger toggleLedBtn1(HADeviceTrigger::ButtonShortPressType, haBtnName1);  // You have to add automation in Home Assistant to handle this trigger

void toggleLed(Button2& btn) {
    Serial.println("tap");
    toggleLedBtn.trigger();
    digitalWrite(ledPin, !digitalRead(ledPin));  // Uncomment this line to toggle the LED while offline
}
void toggleLed1(Button2& btn) {
    Serial.println("tap1");
    toggleLedBtn1.trigger();
    digitalWrite(ledPin1, !digitalRead(ledPin1));  // Uncomment this line to toggle the LED while offline
}

void onSwitchCommand(bool state, HASwitch* sender) {
    digitalWrite(ledPin, (state ? HIGH : LOW));
    sender->setState(state);  // report state back to the Home Assistant
}
void onSwitchCommand1(bool state, HASwitch* sender) {
    digitalWrite(ledPin1, (state ? HIGH : LOW));
    sender->setState(state);  // report state back to the Home Assistant
}

void setup() {
    Serial.begin(115200);
    pinMode(ledPin, OUTPUT);
    digitalWrite(ledPin, LOW);
    pinMode(ledPin1, OUTPUT);
    digitalWrite(ledPin1, LOW);

    ledBtn.begin(btnPin);
    ledBtn.setTapHandler(toggleLed);
    ledBtn1.begin(btnPin1);
    ledBtn1.setTapHandler(toggleLed1);

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
    ledSw1.setName("LED Switch1");         // Switch name
    ledSw1.onCommand(onSwitchCommand1);

    mqtt.begin(mqttBrokerIp, mqttUser, mqttPassword);
}

void loop() {
    mqtt.loop();
    ledBtn.loop();
    ledBtn1.loop();
}