//
// Created by tomasdrah on 02.03.2024.
//

#ifndef VENTILATIONSYSTEM_EMBEDED_TEXTSENDER_H
#define VENTILATIONSYSTEM_EMBEDED_TEXTSENDER_H

namespace TdEmbeddedFd {

    class TextSender {
    public:
        virtual bool SendText(char *text, unsigned char length) = 0;

        bool SendTextConst(const char *str) {
            return SendText((char *) str, strlen(str));
        }

        bool SendTextFromInt(int number) {
            itoa(number, StringBuffer, 10);
            bool result = SendText(StringBuffer, StringBufferLength);
            CleanUpTheBuffer();
            return result;
        }

        bool SendTextFromFloat(float number) {
            dtostrf(number, 7, 3, StringBuffer);
            bool result = SendText(StringBuffer, StringBufferLength);
            CleanUpTheBuffer();
            return result;
        }


    protected:
        static const unsigned char StringBufferLength = 20;
        char StringBuffer[StringBufferLength]{};

        void CleanUpTheBuffer() {
            for (char &i: StringBuffer) {
                i = '\0';
            }
        }


    };

} // TdEmbeddedFd

#endif //VENTILATIONSYSTEM_EMBEDED_TEXTSENDER_H
