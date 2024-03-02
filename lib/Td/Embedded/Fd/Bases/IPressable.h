//
// Created by tomasdrah on 02.03.2024.
//

#ifndef VENTILATIONSYSTEM_EMBEDED_IPRESSABLE_H
#define VENTILATIONSYSTEM_EMBEDED_IPRESSABLE_H

namespace TdEmbeddedFd {

    class IPressable {
    public:
        virtual bool IsPressedEvent() = 0;

        virtual bool IsLongPressedContinuousEvent() = 0;
    };

} // TdEmbeddedFd

#endif //VENTILATIONSYSTEM_EMBEDED_IPRESSABLE_H
