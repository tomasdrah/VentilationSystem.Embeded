//
// Created by tomasdrah on 03.03.2024.
//

#ifndef VENTILATIONSYSTEM_EMBEDED_SPIMASTER_H
#define VENTILATIONSYSTEM_EMBEDED_SPIMASTER_H

#include "Embedded/Fd/Bases/IoPin.h"

namespace TdEmbeddedFd {

    class SPITransactionSettings {
    public:
        explicit SPITransactionSettings(unsigned long clock) : Clock(clock) {}

        unsigned long Clock;
    };

    class SPIMaster {
    public:
        virtual bool TryToInitialize() = 0;

        virtual bool TryToInitialize(SPITransactionSettings settings) = 0;

        virtual void BeginTransaction(SPITransactionSettings settings) = 0;


        virtual void StartCommunicationWithSlave(IoPin *pin) = 0;

        virtual void StopCommunicationWithSlave(IoPin *pin) = 0;

        // Must be inside communication window.
        virtual void TransferByte(unsigned char data) = 0;

        virtual void SendConstText(IoPin *pin, const char *data) = 0;
    };

} // TdEmbeddedFd

#endif //VENTILATIONSYSTEM_EMBEDED_SPIMASTER_H
