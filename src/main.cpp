#include <Arduino.h>

#include <Wire.h>
#include "Adafruit_Sensor.h"
#include "Adafruit_BMP280.h"



#include "Embedded/Fd/Windows/Win_IoPin.h"
#include "Embedded/Fd/Arduino/Ard_IoPin.h"
#include "Embedded/Fd/Windows/Thermometers/Win_SteppingThermometer.h"

TdEmbeddedFd::Win_IoPin W_pin = TdEmbeddedFd::Win_IoPin();
TdEmbeddedFd::Ard_IoPin A_pin = TdEmbeddedFd::Ard_IoPin(LED_BUILTIN, OUTPUT );
TdEmbeddedFd::Ard_IoPin A_analog_pin = TdEmbeddedFd::Ard_IoPin(A0, INPUT );

TdEmbeddedFd::Win_SteppingThermometer w_thermometer = TdEmbeddedFd::Win_SteppingThermometer();

TdEmbeddedFd::PinState testGetState(TdEmbeddedFd::IoPin *pin) {
    return pin->getState();
}


void setup() {
    pinMode(LED_BUILTIN, OUTPUT);
    Serial.begin(9600);

    W_pin.setState(TdEmbeddedFd::PinState::On);
    Serial.println((testGetState(&W_pin) == TdEmbeddedFd::PinState::On) ? "On" : "Off");

    A_pin.setState(TdEmbeddedFd::PinState::On);
    Serial.println((testGetState(&A_pin) == TdEmbeddedFd::PinState::On) ? "On" : "Off");
    A_pin.setState(TdEmbeddedFd::PinState::Off);
    Serial.println((testGetState(&A_pin) == TdEmbeddedFd::PinState::On) ? "On" : "Off");

    w_thermometer.TryToInitialize();
}


void loop() {
    int sensorValue = 0;

    digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
    delay(1000);
    sensorValue = A_analog_pin.getSettPwm();
    Serial.println(sensorValue);

    Serial.print("Temperature: ");
    Serial.print(w_thermometer.ReadTemperatureCelsius());
    Serial.println(" celsius.");


    digitalWrite(LED_BUILTIN, LOW);   // turn the LED off by making the voltage LOW
    delay(1000);
    sensorValue = A_analog_pin.getSettPwm();
    Serial.println(sensorValue);

    Serial.print("Temperature: ");
    Serial.print(w_thermometer.ReadTemperatureCelsius());
    Serial.println(" celsius.");

}