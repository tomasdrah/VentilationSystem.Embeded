//
// Created by drahonovsky on 25.02.2024.
//

#ifndef VENTILATIONSYSTEM_EMBEDDED_I2C_H
#define VENTILATIONSYSTEM_EMBEDDED_I2C_H


namespace TdEmbeddedFd {

    class I2C {
    public:
        explicit I2C(int timeoutMs) : timeoutMs(timeoutMs) {}


        virtual bool TryToInitializeAsMaster() = 0;

        virtual bool TryToInitializeAsSlave(unsigned char deviceAddress) = 0;


        virtual void BeginTransmission(unsigned char deviceAddress) = 0;

        virtual void EndTransmission() = 0;

        // returns available byte amount
        virtual unsigned char RequestData(unsigned char deviceAddress, unsigned char byteSize) = 0;

        // inside receive event or after begin transmission
        virtual void Write(unsigned char byte) = 0;

        // inside receive event or after begin transmission
        virtual void Write(unsigned char *bytes, unsigned char length) = 0;


        virtual void OnReceiveEvent(void (*callback)(int)) = 0;

        virtual unsigned char AvailableBytes() = 0;

        virtual unsigned char ReadNextByte() = 0;
        virtual unsigned char PeekNextByte() = 0;

    protected:
        int timeoutMs = 3000;
    };

} // TdEmbeddedFd

#endif //VENTILATIONSYSTEM_EMBEDDED_I2C_H
