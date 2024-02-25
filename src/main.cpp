#include <Arduino.h>

void setup() {
    pinMode(LED_BUILTIN, OUTPUT);
    Serial.begin(9600);
}

void loop() {
    int sensorValue = 0;

    digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
    delay(2000);
    sensorValue = analogRead(A0);
    Serial.println(sensorValue);

    digitalWrite(LED_BUILTIN, LOW);   // turn the LED off by making the voltage LOW
    delay(1000);
    sensorValue = analogRead(A0);
    Serial.println(sensorValue);
}