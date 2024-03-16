//
// Created by tomasdrah on 03.03.2024.
//

#ifndef VENTILATIONSYSTEM_EMBEDED_ARD_SPIMASTER_H
#define VENTILATIONSYSTEM_EMBEDED_ARD_SPIMASTER_H

#include "Embedded/Fd/Bases/Comunication/SPI/SPIMaster.h"
#include "Embedded/Fd/Bases/IoPin.h"
#include<SPI.h>

namespace TdEmbeddedFd {

    class Ard_SPIMaster : public SPIMaster {
    public:
        bool TryToInitializeMaster() override {
            SPIClass::begin();
            return true;
        }

        bool TryToInitializeMaster(SPITransactionSettings settings) override {
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

        unsigned char TransferByte(unsigned char data) override {
            return SPIClass::transfer(data);
        }

        void SendConstText(IoPin *pin, const char *data) override {
            StartCommunicationWithSlave(pin);

            char c;
            for (const char *p = data; (c = *p); p++) {
                char resp = (char) TransferByte(c);
                Serial.print(resp);
            }
            Serial.println();


            StopCommunicationWithSlave(pin);
        }

    };

} // TdEmbeddedFd

#endif //VENTILATIONSYSTEM_EMBEDED_ARD_SPIMASTER_H
