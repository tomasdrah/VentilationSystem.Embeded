#include<SPI.h>

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_I2CDevice.h>
#include <Adafruit_SPIDevice.h>

#include "Embedded/Fd/Bases/Comunication/SPI/SPIMaster.h"
#include "Embedded/Fd/Bases/Comunication/SPI/SPISlave.h"
#include "Embedded/Fd/Arduino/Comunication/SPI/Ard_SPIMaster.h"
#include "Embedded/Fd/Arduino/Comunication/SPI/Ard_SPISlave.h"
#include "Embedded/Fd/Arduino/Ard_IoPin.h"


//TdEmbeddedFd::Ard_SPIMaster MySpiMaster = TdEmbeddedFd::Ard_SPIMaster();
//TdEmbeddedFd::Ard_IoPin MySlaveSS1Pin = TdEmbeddedFd::Ard_IoPin(10, OUTPUT);

TdEmbeddedFd::Ard_SPISlave MySpiSlave = TdEmbeddedFd::Ard_SPISlave();
// SPI interrupt routine
ISR (SPI_STC_vect) {
    MySpiSlave.NewByteInterruptEvent();
}


void setup(void) {
    Serial.begin(9600);
    MySpiSlave.TryToInitialize();
}


void loop(void) {
    if (MySpiSlave.IsMessageReadyToRead()) {
        Serial.println(MySpiSlave.GetBuffer());
        MySpiSlave.SetMsgIsRead();
    }
    delay(50);

}