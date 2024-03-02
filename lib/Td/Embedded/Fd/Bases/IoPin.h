//
// Created by drahonovsky on 25.02.2024.
//

#ifndef VENTILATIONSYSTEM_EMBEDDED_IOPIN_H
#define VENTILATIONSYSTEM_EMBEDDED_IOPIN_H

namespace TdEmbeddedFd {

    enum class PinState {
        On,
        Off
    };

    class IoPin {
    public:
        virtual PinState getState() = 0;

        // Set the state of the pin
        virtual void setState(PinState state) = 0;

        // Get current voltage
        virtual int getSettPwm() = 0;

        // value between 0 and 100
        virtual void setPwm(int pwm) = 0;

    };

} // TDEmbededFd

#endif //VENTILATIONSYSTEM_EMBEDDED_IOPIN_H
