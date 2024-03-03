
#include <arduino.h>
#include <Wire.h>
#include <Adafruit_I2CDevice.h>
#include <Adafruit_SPIDevice.h>

#include "Embedded/Fd/Arduino/Comunication/I2C/Ard_I2C.h"

TdEmbeddedFd::Ard_I2C I2C_Slave = TdEmbeddedFd::Ard_I2C(1000, 8);

void requestEvent() {
    I2C_Slave.WriteTextConst("hello ");
}

void setup() {
    I2C_Slave.TryToInitialize();
    I2C_Slave.RegisterOnRequestEvent(requestEvent);
}


void loop() {
    delay(100);
}
