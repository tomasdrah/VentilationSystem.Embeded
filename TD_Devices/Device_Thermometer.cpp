#include <Arduino.h>
#include "Embedded/Fd/Arduino/Displays/I2CLiquidCrystalDisplays/Ard_LiquidCrystalDisplayI2C.h"
#include "Embedded/Devices/I2CIntSettingWithDisplay/Device_I2CIntSettingWithDisplay.h"
#include <Adafruit_I2CDevice.h>
#include <Adafruit_SPIDevice.h>

#include "Embedded/Fd/Independent/Ind_Button.h"
#include "Embedded/Fd/Arduino/Ard_IoPin.h"
#include "Embedded/Fd/Arduino/Comunication/I2C/Ard_I2C.h"
#include "Embedded/Fd/Arduino/Thermometers/Ard_Bmp280.h"

static const int MyLoopTime = 100;


TdEmbeddedFd::Ard_Bmp280 MainThermometer = TdEmbeddedFd::Ard_Bmp280();
float MainThermometerPreviousTemperature = 30.0f;
bool DoReadMainThermometerPreviousTemperature = true;

TdEmbeddedFd::Ard_I2C I2C_Slave = TdEmbeddedFd::Ard_I2C(1000, 9);


void floatToBytes(float floatValue, byte *byteArray) {
    memcpy(byteArray, &floatValue, sizeof(float));
}

float bytesToFloat(byte *byteArray) {
    float floatValue;
    memcpy(&floatValue, byteArray, sizeof(float));
    return floatValue;
}

void I2CRequestEvent() {
//    float originalFloat = 35.14;

    unsigned char floatBytes[sizeof(float)];
    floatToBytes(MainThermometerPreviousTemperature, floatBytes);
    I2C_Slave.Write(floatBytes, sizeof(float));
    DoReadMainThermometerPreviousTemperature = true;
}


void setup() {
    Serial.begin(9600);

    MainThermometer.TryToInitialize();

    I2C_Slave.TryToInitialize();
    I2C_Slave.RegisterOnRequestEvent(I2CRequestEvent);
}


void loop() {
    if (DoReadMainThermometerPreviousTemperature) {
        MainThermometerPreviousTemperature = MainThermometer.ReadTemperatureCelsius();
        DoReadMainThermometerPreviousTemperature = false;
    }


    delay(MyLoopTime);
}