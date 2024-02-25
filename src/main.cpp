#include <Arduino.h>
#include "Embedded/Fd/Windows/Win_IoPin.h"
#include "Embedded/Fd/Arduino/Ard_IoPin.h"

TdEmbeddedFd::Win_IoPin _Wpin = TdEmbeddedFd::Win_IoPin();
TdEmbeddedFd::Ard_IoPin _Apin = TdEmbeddedFd::Ard_IoPin(LED_BUILTIN, OUTPUT );
TdEmbeddedFd::Ard_IoPin _A_analog_pin = TdEmbeddedFd::Ard_IoPin(A0, INPUT );

TdEmbeddedFd::PinState testGetState(TdEmbeddedFd::IoPin *pin) {
    return pin->getState();
}


void setup() {
    pinMode(LED_BUILTIN, OUTPUT);
    Serial.begin(9600);

    _Wpin.setState(TdEmbeddedFd::PinState::On);
    Serial.println((testGetState(&_Wpin) == TdEmbeddedFd::PinState::On) ? "On" : "Off");

    _Apin.setState(TdEmbeddedFd::PinState::On);
    Serial.println((testGetState(&_Apin) == TdEmbeddedFd::PinState::On) ? "On" : "Off");
    _Apin.setState(TdEmbeddedFd::PinState::Off);
    Serial.println((testGetState(&_Apin) == TdEmbeddedFd::PinState::On) ? "On" : "Off");
}


void loop() {
    int sensorValue = 0;

    digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
    delay(2000);
    sensorValue = _A_analog_pin.getSettPwm();
    Serial.println(sensorValue);

    digitalWrite(LED_BUILTIN, LOW);   // turn the LED off by making the voltage LOW
    delay(1000);
    sensorValue = _A_analog_pin.getSettPwm();
    Serial.println(sensorValue);
}