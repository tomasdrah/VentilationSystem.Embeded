//
// Created by tomasdrah on 02.03.2024.
//

#ifndef VENTILATIONSYSTEM_EMBEDED_ARD_LIQUIDCRYSTALDISPLAYI2C_H
#define VENTILATIONSYSTEM_EMBEDED_ARD_LIQUIDCRYSTALDISPLAYI2C_H

#include "Embedded/Fd/Bases/Comunication/General/TextSender.h"
#include <Arduino.h>
#include "LiquidCrystal_I2C.h"

namespace TdEmbeddedFd {

    class Ard_LiquidCrystalDisplayI2C : public TextSender {
    public:
        Ard_LiquidCrystalDisplayI2C() {}

        explicit Ard_LiquidCrystalDisplayI2C(signed char lcdAddress) : LcdAddress(lcdAddress) {}

        Ard_LiquidCrystalDisplayI2C(signed char lcdAddress, const LiquidCrystal_I2C &lcd, signed char useLine)
                : LcdAddress(lcdAddress), lcd(lcd), UseLine(useLine) {}

        bool SendText(char *text, unsigned char length) override {
            lcd.clear();
            lcd.setCursor(UseLine, 0);
            lcd.print(text);
            return true;
        }

        bool TryToInitialize() {
            lcd.init();
            lcd.backlight();
            return true;
        }

    private:
        signed char LcdAddress = 0x27;
        LiquidCrystal_I2C lcd = LiquidCrystal_I2C(LcdAddress, 16, 2); // Change to (0x27,20,4) for 20x4 LCD.
        signed char UseLine = 0;
    };

} // TdEmbeddedFd

#endif //VENTILATIONSYSTEM_EMBEDED_ARD_LIQUIDCRYSTALDISPLAYI2C_H
