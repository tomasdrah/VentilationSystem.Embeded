//
// Created by tomasdrah on 02.03.2024.
//

#ifndef VENTILATIONSYSTEM_EMBEDED_BUTTON_H
#define VENTILATIONSYSTEM_EMBEDED_BUTTON_H

#include "Embedded/Fd/Bases/IPressable.h"

namespace TdEmbeddedFd {


    class Button : public IPressable {
    public:
        virtual void Update() = 0;
    };

} // TdEmbeddedFd

#endif //VENTILATIONSYSTEM_EMBEDED_BUTTON_H
