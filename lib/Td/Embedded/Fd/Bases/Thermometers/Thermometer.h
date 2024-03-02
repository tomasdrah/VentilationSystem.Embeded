//
// Created by drahonovsky on 25.02.2024.
//

#ifndef VENTILATIONSYSTEM_EMBEDDED_THERMOMETER_H
#define VENTILATIONSYSTEM_EMBEDDED_THERMOMETER_H

namespace TdEmbeddedFd {

    class Thermometer {
    public:
        virtual float ReadTemperatureCelsius() = 0;
        virtual bool TryToInitialize() = 0;
    };

} // TdEmbeddedFd

#endif //VENTILATIONSYSTEM_EMBEDDED_THERMOMETER_H
