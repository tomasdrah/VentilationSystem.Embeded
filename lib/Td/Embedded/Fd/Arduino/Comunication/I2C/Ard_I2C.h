//
// Created by drahonovsky on 25.02.2024.
//

#ifndef VENTILATIONSYSTEM_EMBEDDED_ARD_I2C_H
#define VENTILATIONSYSTEM_EMBEDDED_ARD_I2C_H

#include <Wire.h>
#include "Embedded/Fd/Bases/Comunication/I2C/I2C.h"

namespace TdEmbeddedFd {

    class Ard_I2C:public I2C {
        bool TryToInitializeAsMaster() override {
            Wire.begin();
            return true;
        }

        bool TryToInitializeAsSlave(unsigned char deviceAddress) override {
            Wire.begin(deviceAddress);
            return true;
        }

        void BeginTransmission(unsigned char deviceAddress) override {
            Wire.beginTransmission(deviceAddress);
        }

        void EndTransmission() override {
            Wire.endTransmission();
        }

        unsigned char RequestData(unsigned char deviceAddress, unsigned char byteSize) override {
            return Wire.requestFrom(deviceAddress, byteSize);
        }

        void Write(unsigned char byte) override {
            Wire.write(byte);
        }

        void Write(unsigned char *bytes, unsigned char length) override {
            Wire.write(bytes,length);
        }

        void OnReceiveEvent(void (*callback)(int)) override {
            Wire.onReceive(callback);
        }

        unsigned char AvailableBytes() override {
            return Wire.available();
        }

        unsigned char ReadNextByte() override {
            return Wire.read();
        }
        unsigned char PeekNextByte() override {
            return Wire.peek();
        }
    };

} // TdEmbeddedFd

#endif //VENTILATIONSYSTEM_EMBEDDED_ARD_I2C_H
