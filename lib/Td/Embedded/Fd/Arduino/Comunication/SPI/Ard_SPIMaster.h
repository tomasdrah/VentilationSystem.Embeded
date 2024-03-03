//
// Created by tomasdrah on 03.03.2024.
//

#ifndef VENTILATIONSYSTEM_EMBEDED_ARD_SPIMASTER_H
#define VENTILATIONSYSTEM_EMBEDED_ARD_SPIMASTER_H

#include "Embedded/Fd/Bases/Comunication/SPI/SPIMaster.h"
#include "Embedded/Fd/Bases/IoPin.h"

namespace TdEmbeddedFd {

    class Ard_SPIMaster : public SPIMaster {
    public:
        bool TryToInitialize() override {
            SPIClass::begin();
            return true;
        }

        bool TryToInitialize(SPITransactionSettings settings) override {
            SPIClass::begin();
            BeginTransaction(settings);
            return true;
        }

        void BeginTransaction(SPITransactionSettings settings) override {
            SPISettings MySPISettings = SPISettings(settings.Clock, MSBFIRST, SPI_MODE0);
            SPIClass::beginTransaction(MySPISettings);
        }


        void StartCommunicationWithSlave(IoPin *pin) override {
            pin->setState(PinState::Off);
        }

        void StopCommunicationWithSlave(IoPin *pin) override {
            pin->setState(PinState::On);
        }

        void TransferByte(unsigned char data) override {
            SPIClass::transfer(data);
        }

        void SendConstText(IoPin *pin, const char *data) override {
            StartCommunicationWithSlave(pin);

            char c;
            for (const char *p = data; (c = *p); p++)
                TransferByte(c);

            StopCommunicationWithSlave(pin);
        }

    };

} // TdEmbeddedFd

#endif //VENTILATIONSYSTEM_EMBEDED_ARD_SPIMASTER_H
