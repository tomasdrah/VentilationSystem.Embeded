//
// Created by drahonovsky on 25.02.2024.
//

#ifndef VENTILATIONSYSTEM_EMBEDDED_ARD_BMP280_H
#define VENTILATIONSYSTEM_EMBEDDED_ARD_BMP280_H

#include "Embedded/Fd/Bases/Thermometers/Thermometer.h"
#include <Wire.h>
#include "Adafruit_Sensor.h"
#include "Adafruit_BMP280.h"

namespace TdEmbeddedFd {

    class Ard_Bmp280 : public Thermometer {
    public:

        explicit Ard_Bmp280(Adafruit_BMP280 *bmp280) : bmp(bmp) {}

        explicit Ard_Bmp280(Adafruit_BMP280 *bmp280, int address) : address(address), bmp(bmp) {}


        float ReadTemperatureCelsius() override {
            return bmp->readTemperature();
        }

        bool TryToInitialize() override {
            return bmp->begin(address);
        }

    private:
        int address = 0x76;
        Adafruit_BMP280 *bmp;
    };

} // TdEmbeddedFd

#endif //VENTILATIONSYSTEM_EMBEDDED_ARD_BMP280_H
