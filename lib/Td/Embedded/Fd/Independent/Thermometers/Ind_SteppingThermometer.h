//
// Created by drahonovsky on 25.02.2024.
//

#ifndef VENTILATIONSYSTEM_EMBEDDED_WIN_STEPPINGTHERMOMETER_H
#define VENTILATIONSYSTEM_EMBEDDED_WIN_STEPPINGTHERMOMETER_H

#include "Embedded/Fd/Bases/Thermometers/Thermometer.h"

namespace TdEmbeddedFd {

    class Ind_SteppingThermometer : Thermometer {
    public:
        explicit Ind_SteppingThermometer(
                float currentTemp=40,
                float minTemp=30,
                float maxTemp=50,
                float stepSize=1,
                bool direction= true) : currentTemp(currentTemp),
                                  minTemp(minTemp),
                                  maxTemp(maxTemp),
                                  stepSize(stepSize),
                                  direction(direction) {}

        float ReadTemperatureCelsius() override {
            if (direction) {
                currentTemp += stepSize;
                if (currentTemp >= maxTemp) {
                    currentTemp = maxTemp;
                    direction = false;  // Change direction
                }
            } else {
                currentTemp -= stepSize;
                if (currentTemp <= minTemp) {
                    currentTemp = minTemp;
                    direction = true;  // Change direction
                }
            }

            return currentTemp;
        }

        bool TryToInitialize() override {
            return true;
        }

    private:
        float currentTemp;  // Current temperature
        float minTemp;      // Minimum temperature
        float maxTemp;      // Maximum temperature
        float stepSize;     // Step size for temperature change
        bool direction;     // Direction of temperature change (true for increasing, false for decreasing)

    };

} // TdEmbeddedFd

#endif //VENTILATIONSYSTEM_EMBEDDED_WIN_STEPPINGTHERMOMETER_H
