#include <Arduino.h>
#include "Embedded/Fd/Windows/WinIoPin.h"

TdEmbeddedFd::WinIoPin _pin = TdEmbeddedFd::WinIoPin();

TdEmbeddedFd::PinState testGetState(TdEmbeddedFd::IoPin *pin) {
    return pin->getState();
}


void setup() {
    pinMode(LED_BUILTIN, OUTPUT);
    Serial.begin(9600);
    _pin.setState(TdEmbeddedFd::PinState::On);
    Serial.println((testGetState(&_pin) == TdEmbeddedFd::PinState::On) ? "On" : "Off");
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