#include <Arduino.h>
#include "Embedded/Fd/Windows/WinIoPin.h"
#include "Embedded/Fd/Arduino/ArdIoPin.h"

TdEmbeddedFd::WinIoPin _Wpin = TdEmbeddedFd::WinIoPin();
TdEmbeddedFd::ArdIoPin _Apin = TdEmbeddedFd::ArdIoPin(LED_BUILTIN,OUTPUT );
TdEmbeddedFd::ArdIoPin _A_analog_pin = TdEmbeddedFd::ArdIoPin(A0,INPUT );

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