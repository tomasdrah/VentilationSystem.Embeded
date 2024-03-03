//
// Created by tomasdrah on 03.03.2024.
//

#ifndef VENTILATIONSYSTEM_EMBEDED_SPISLAVE_H
#define VENTILATIONSYSTEM_EMBEDED_SPISLAVE_H

namespace TdEmbeddedFd {

    class SPISlave {
    public:
        virtual bool TryToInitializeSlave() = 0;

        virtual bool IsMessageReadyToRead() = 0;

        virtual void SetMsgIsRead() = 0;

        virtual unsigned char GetMaxBufferSize() = 0;

        virtual unsigned char GetMessageLength() = 0;

        virtual char *GetBuffer() = 0;

    };

} // TdEmbeddedFd

#endif //VENTILATIONSYSTEM_EMBEDED_SPISLAVE_H
