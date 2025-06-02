
#include <WiFi.h>
#include <ArduinoHA.h>
#include <Button2.h>

#define ledPin   LED_BUILTIN
#define btnPin   0
#define haBtnName "LedBtn"

Button2 ledBtn;

#define ssid     "your_ssid"  // replace with your WiFi SSID
#define password "your_password"  // replace with your WiFi password

#define mqttBrokerIp IPAddress(192, 168, 1, 0)  // replace with your MQTT broker IP address
#define mqttUser     "your_mqtt_user"  // replace with your credentials
#define mqttPassword "your_mqtt_password"  // replace with your credentials

WiFiClient client;
HADevice   device;
HAMqtt     mqtt(client, device);

HADeviceTrigger toggleLedBtn(HADeviceTrigger::ButtonShortPressType, haBtnName);

void tap(Button2& btn) {
    Serial.println("tap");
    toggleLedBtn.trigger();
    digitalWrite(ledPin, !digitalRead(ledPin));  // Uncomment this line to toggle the LED while offline
}

HASwitch ledSw("myLedSw");  // "myledSw" is a part of MQTT topic that will be used to control the switch

void onSwitchCommand(bool state, HASwitch* sender) {
    digitalWrite(ledPin, (state ? HIGH : LOW));
    sender->setState(state);  // report state back to the Home Assistant
}

void setup() {
    Serial.begin(115200);
    pinMode(ledPin, OUTPUT);
    digitalWrite(ledPin, LOW);

    ledBtn.begin(btnPin);
    ledBtn.setTapHandler(tap);

    byte mac[6];
    WiFi.macAddress(mac);
    device.setUniqueId(mac, sizeof(mac));
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    // handle switch state
    ledSw.setName("My LED");  // Device name
    ledSw.onCommand(onSwitchCommand);

    mqtt.begin(mqttBrokerIp, mqttUser, mqttPassword);
}

void loop() {
    mqtt.loop();
    ledBtn.loop();
}
