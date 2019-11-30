#include <Arduino.h>

#define REPORT_INTEVAL 1000

#include <ArduinoJson.h>

void setup() {
  Serial.begin(115200);
  Serial.println("start setup!");
  Serial.println("end setup!");
}

unsigned long prevReport = 0;

void addDebugReport(DynamicJsonDocument *doc, unsigned long currentMillis) {
    JsonObject debug = doc->createNestedObject("debug");
    debug["currentMillis"] = currentMillis;
    debug["state"] = "allGood";
}

void loop() {
  unsigned long currentMillis = millis();

  if ((unsigned long)(currentMillis - prevReport) >= (int)REPORT_INTEVAL) {
    const size_t capacity = 2*JSON_OBJECT_SIZE(2);
    DynamicJsonDocument doc(capacity);

    doc["name"] = "nestedJsonWithFuncViaSerial";
    addDebugReport(&doc, currentMillis);

    serializeJson(doc, Serial);
    Serial.println();
    prevReport = currentMillis;
  }
}
