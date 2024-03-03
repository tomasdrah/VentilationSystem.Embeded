
#include <arduino.h>
#include <Wire.h>
#include <Adafruit_I2CDevice.h>
#include <Adafruit_SPIDevice.h>

#include "Embedded/Fd/Arduino/Comunication/I2C/Ard_I2C.h"
#include "Embedded/Fd/Arduino/Ard_IoPin.h"
#include "Embedded/Fd/Bases/LoopTimer.h"


static const int MainLoopTime = 100;

TdEmbeddedFd::Ard_IoPin MyFanPwmControl = TdEmbeddedFd::Ard_IoPin(DD3, OUTPUT);

static const int MainFanTachometerPin = DD2;
volatile unsigned long pulseCount = 0;
void countPulses() {
    pulseCount++;
}

TdEmbeddedFd::LoopTimer pulseTimer = TdEmbeddedFd::LoopTimer(MainLoopTime, 1000);


void setup() {
    Serial.begin(9600);
    pulseTimer.StartListeningForTheEvent();
    pinMode(MainFanTachometerPin, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(MainFanTachometerPin), countPulses, FALLING);
}


void loop() {

    pulseTimer.Update();

    if (pulseTimer.IsContinuousEventRaised()) {
        pulseTimer.ResetTheEvent();
        double fanSpeed = (double) pulseCount * 60.0 / 2.0;  // Convert pulses per second to RPM
        Serial.print("Fan Speed: ");
        Serial.println(fanSpeed);
        pulseCount = 0;
    }


    MyFanPwmControl.setPwm(30);
//    Serial.println(30);
//    delay(5000);
//    MyFanPwmControl.setPwm(50);
//    Serial.println(50);
//    delay(5000);
//    MyFanPwmControl.setPwm(100);
//    Serial.println(100);
//    delay(5000);

    delay(MainLoopTime);
}

//const byte ledPin = 13;
//const byte interruptPin = 2;
//volatile byte state = LOW;
//
//void blink() {
//    state = !state;
//}
//
//void setup() {
//    pinMode(ledPin, OUTPUT);
//    pinMode(interruptPin, INPUT_PULLUP);
//    attachInterrupt(digitalPinToInterrupt(interruptPin), blink, CHANGE);
//}
//
//void loop() {
//    digitalWrite(ledPin, state);
//}

