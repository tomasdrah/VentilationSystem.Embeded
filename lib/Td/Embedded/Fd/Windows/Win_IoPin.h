//
// Created by drahonovsky on 25.02.2024.
//

#ifndef VENTILATIONSYSTEM_EMBEDDED_WIN_IOPIN_H
#define VENTILATIONSYSTEM_EMBEDDED_WIN_IOPIN_H

#include "Embedded/Fd/Headers/IoPin.h"

namespace TdEmbeddedFd {

    class Win_IoPin : public IoPin {
    public:

        Win_IoPin() {}

        PinState getState() override {
            return (analogValue > 50) ? PinState::On : PinState::Off;
        }

        void setState(PinState state) override {
            analogValue = (state == PinState::On) ? 100 : 0;
        }

        int getSettPwm() override {
            return pwmValue;
        }

        void setPwm(int pwm) override {
            if (pwm < 0) {
                pwmValue = 0;
            } else if (pwm > 100) {
                pwmValue = 100;
            } else {
                pwmValue = pwm;
            }
        }


    private:
        int analogValue = 0;
        int pwmValue = 0;
    };

} // TdEmbeddedFd

#endif //VENTILATIONSYSTEM_EMBEDDED_WIN_IOPIN_H
