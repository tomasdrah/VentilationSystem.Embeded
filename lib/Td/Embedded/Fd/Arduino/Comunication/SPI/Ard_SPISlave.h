//
// Created by tomasdrah on 03.03.2024.
//

#ifndef VENTILATIONSYSTEM_EMBEDED_ARD_SPISLAVE_H
#define VENTILATIONSYSTEM_EMBEDED_ARD_SPISLAVE_H

#include "Embedded/Fd/Bases/Comunication/SPI/SPISlave.h"

namespace TdEmbeddedFd {

    class Ard_SPISlave : public SPISlave {
    public:
        bool TryToInitializeSlave() override {
            // have to send on master in, *slave out*
            pinMode(MISO, OUTPUT);
            // turn on SPI in slave mode
            SPCR |= _BV(SPE);
            // turn on interrupts
            SPCR |= _BV(SPIE);

            return true;
        }

        void NewByteInterruptEvent() {
            byte c = SPDR;
            // add to buffer if room
            if (MessageLength < BufferSize and !MessageReadyToRead) {
                Buffer[MessageLength++] = (char) c;

                // example: newline means time to process buffer
                if (c == '\n') {
                    Buffer[MessageLength - 1] = 0;
                    MessageReadyToRead = true;
                }
            }
        }

        bool IsMessageReadyToRead() override {
            return MessageReadyToRead;
        }

        void SetMsgIsRead() override {
            MessageLength = 0;
            MessageReadyToRead = false;
        }

        unsigned char GetMaxBufferSize() override {
            return BufferSize;
        }

        unsigned char GetMessageLength() override {
            return MessageLength;
        }

        char *GetBuffer() override {
            return Buffer;
        }

    protected:

        static const unsigned char BufferSize = 100;
        volatile unsigned char MessageLength = 0;
        volatile bool MessageReadyToRead = false;
        char Buffer[BufferSize]{};
    };

} // TdEmbeddedFd

#endif //VENTILATIONSYSTEM_EMBEDED_ARD_SPISLAVE_H
