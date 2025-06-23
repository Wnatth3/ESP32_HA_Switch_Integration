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

#define ledPin    23
#define btnPin    17
#define haBtnName "LedBtn" // "LedBtn" is a unique Trigger name that will be used in Home Assistant to trigger automations.

#define ledPin1    19
#define btnPin1    16
#define haBtnName1 "LedBtn1"

#define ledPin2    18
#define btnPin2    4
#define haBtnName2 "LedBtn2"

WiFiClient client;
HADevice   device;
HAMqtt     mqtt(client, device);

Button2 ledBtn;
Button2 ledBtn1;
Button2 ledBtn2;

HASwitch ledSw("LedSw");    // "ledSw" is a unique ID as a part of MQTT topic that will be used to control the switch.
HASwitch ledSw1("LedSw1");  
HASwitch ledSw2("LedSw2");  

HADeviceTrigger toggleLedBtn(HADeviceTrigger::ButtonShortPressType, haBtnName);    // You have to add automation in Home Assistant to handle this trigger
HADeviceTrigger toggleLedBtn1(HADeviceTrigger::ButtonShortPressType, haBtnName1);  
HADeviceTrigger toggleLedBtn2(HADeviceTrigger::ButtonShortPressType, haBtnName2);  

void toggleLed(Button2& btn) {
    if (btn == ledBtn) {
        Serial.println("btn clicked");
        toggleLedBtn.trigger();
        digitalWrite(ledPin, !digitalRead(ledPin));
    } else if (btn == ledBtn1) {
        Serial.println("btn1 clicked");
        toggleLedBtn1.trigger();
        digitalWrite(ledPin1, !digitalRead(ledPin1));
    } else if (btn == ledBtn2) {
        Serial.println("btn2 clicked");
        toggleLedBtn2.trigger();
        digitalWrite(ledPin2, !digitalRead(ledPin2));
    }
}

void onSwitchCommand(bool state, HASwitch* sender) {
    if (sender == &ledSw) {
        digitalWrite(ledPin, (state ? HIGH : LOW));
    } else if (sender == &ledSw1) {
        digitalWrite(ledPin1, (state ? HIGH : LOW));
    } else if (sender == &ledSw2) {
        digitalWrite(ledPin2, (state ? HIGH : LOW));
    }

    sender->setState(state);  // report state back to the Home Assistant
}

void setup() {
    Serial.begin(115200);
    pinMode(ledPin, OUTPUT);
    digitalWrite(ledPin, LOW);
    pinMode(ledPin1, OUTPUT);
    digitalWrite(ledPin1, LOW);
    pinMode(ledPin2, OUTPUT);
    digitalWrite(ledPin2, LOW);

    ledBtn.begin(btnPin);
    ledBtn.setTapHandler(toggleLed);
    ledBtn1.begin(btnPin1);
    ledBtn1.setTapHandler(toggleLed);
    ledBtn2.begin(btnPin2);
    ledBtn2.setTapHandler(toggleLed);

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

    ledSw.setName("LED Switch");  // Switch name
    ledSw.onCommand(onSwitchCommand);
    ledSw1.setName("LED Switch1");  // Switch name
    ledSw1.onCommand(onSwitchCommand);
    ledSw2.setName("LED Switch2");  // Switch name
    ledSw2.onCommand(onSwitchCommand);

    mqtt.begin(mqttBrokerIp, mqttUser, mqttPassword);
}

void loop() {
    mqtt.loop();
    ledBtn.loop();
    ledBtn1.loop();
    ledBtn2.loop();
}