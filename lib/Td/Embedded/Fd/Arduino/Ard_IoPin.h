//
// Created by drahonovsky on 25.02.2024.
//

#ifndef VENTILATIONSYSTEM_EMBEDDED_ARD_IOPIN_H
#define VENTILATIONSYSTEM_EMBEDDED_ARD_IOPIN_H

#include "Embedded/Fd/Bases/IoPin.h"
#include <Arduino.h>

namespace TdEmbeddedFd {

    class Ard_IoPin : public IoPin {

    public:
        // Constructor
        Ard_IoPin(int pinNumber, char mode) : pinNumber(pinNumber) {
            // Setup Arduino pin mode here if necessary
            pinMode(pinNumber, mode);
        }

        PinState getState() override {
            // You might want to implement logic to determine the state based on the Arduino pin's actual state
            return (digitalRead(pinNumber) == HIGH) ? PinState::On : PinState::Off;
        }

        void setState(PinState state) override {
            // Set the state of the Arduino pin based on the provided PinState
            digitalWrite(pinNumber, (state == PinState::On) ? HIGH : LOW);
        }

        int getSettPwm() override {
            // For simplicity, assuming that the Arduino pin is configured for PWM
            // and analogWrite is used for setting PWM
            return analogRead(pinNumber);
        }

        void setPwm(int pwm) override {
            // Validate PWM value to be between 0 and 255 (Arduino's analogWrite range)
            pwmValue = mapValue(constrain(pwm, 0, 100), 0, 100, 0, 255);
            analogWrite(pinNumber, pwmValue);
        }


    private:
        int pinNumber;
        int pwmValue = 0;

        static int mapValue(int value, int fromLow, int fromHigh, int toLow, int toHigh) {
            return (value - fromLow) * (toHigh - toLow) / (fromHigh - fromLow) + toLow;
        }
    };

} // TdEmbeddedFd

#endif //VENTILATIONSYSTEM_EMBEDDED_ARD_IOPIN_H
