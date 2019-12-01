#include <Arduino.h>

#define REPORT_INTEVAL 1000

#include <ArduinoJson.h>

void setup() {
  Serial.begin(115200);
  Serial.println("start setup!");
  Serial.println("end setup!");
}

unsigned long prevReport = 0;

void loop() {
  unsigned long currentMillis = millis();

  if ((unsigned long)(currentMillis - prevReport) >= (int)REPORT_INTEVAL) {
    const size_t capacity = JSON_OBJECT_SIZE(3);
    DynamicJsonDocument doc(capacity);

    doc["message"] = "hello world";
    doc["currentMillis"] = currentMillis;
    doc["alive?"] = true;

    serializeJson(doc, Serial);
    Serial.println();
    prevReport = currentMillis;
  }
}
