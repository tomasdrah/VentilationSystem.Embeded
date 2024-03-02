//
// Created by tomasdrah on 02.03.2024.
//

#ifndef VENTILATIONSYSTEM_EMBEDED_ARD_LIQUIDCRYSTALDISPLAYI2C_H
#define VENTILATIONSYSTEM_EMBEDED_ARD_LIQUIDCRYSTALDISPLAYI2C_H

#include "Embedded/Fd/Bases/Comunication/General/TextSender.h"
#include <Arduino.h>
#include "LiquidCrystal_I2C.h"

namespace TdEmbeddedFd {

    class Ard_LiquidCrystalDisplayI2C:public TextSender {
    public:
        bool SendText(char *text, unsigned char length) override {
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print(text);
            return true;
        }

        bool TryToInitialize() {
            lcd.init();
            lcd.backlight();
            return true;
        }

    private:
        LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2); // Change to (0x27,20,4) for 20x4 LCD.

    };

} // TdEmbeddedFd

#endif //VENTILATIONSYSTEM_EMBEDED_ARD_LIQUIDCRYSTALDISPLAYI2C_H
