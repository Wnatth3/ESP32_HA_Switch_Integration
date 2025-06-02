
#include <WiFi.h>
#include <ArduinoHA.h>
// #include <Button2.h>

#define ledPin LED_BUILTIN
// #define btnPin   0
// #define btnAName "btnA"

// Button2 button;

#define ssid     "IXORA"
#define password "Dark1331"

#define BROKER_ADDR     IPAddress(192, 168, 0, 81)
#define BROKER_USERNAME "mqttuser"  // replace with your credentials
#define BROKER_PASSWORD "Berry1911"

WiFiClient client;
HADevice   device;
HAMqtt     mqtt(client, device);

// HADeviceTrigger toggleBtnA(HADeviceTrigger::ButtonShortPressType, btnAName);

// void tap(Button2& btn) {
//     Serial.println("tap");
//     toggleBtnA.trigger();
//     digitalWrite(ledPin, !digitalRead(ledPin));
// }

HASwitch ledSw("myLedSw");

void onSwitchCommand(bool state, HASwitch* sender) {
    digitalWrite(ledPin, (state ? HIGH : LOW));
    sender->setState(state);  // report state back to the Home Assistant
}

void setup() {
    Serial.begin(115200);
    pinMode(ledPin, OUTPUT);
    digitalWrite(ledPin, LOW);

    // button.begin(btnPin);
    // button.setTapHandler(tap);

    byte mac[6];
    WiFi.macAddress(mac);
    device.setUniqueId(mac, sizeof(mac));
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    // // optional device's details
    // device.setName("myESP32");
    // device.setSoftwareVersion("1.0.0");

    // handle switch state
    ledSw.setName("My LED"); // Device name
    ledSw.onCommand(onSwitchCommand);

    mqtt.begin(BROKER_ADDR, BROKER_USERNAME, BROKER_PASSWORD);
}

void loop() {
    mqtt.loop();
    // button.loop();
}
