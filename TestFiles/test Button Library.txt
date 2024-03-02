#include <Arduino.h>
#include "Embedded/Fd/Arduino/Displays/I2CLiquidCrystalDisplays/Ard_LiquidCrystalDisplayI2C.h"
#include "Embedded/Devices/I2CIntSettingWithDisplay/Device_I2CIntSettingWithDisplay.h"
#include <Adafruit_I2CDevice.h>
#include <Adafruit_SPIDevice.h>

#include "Embedded/Fd/Independent/Ind_Button.h"
#include "Embedded/Fd/Arduino/Ard_IoPin.h"
static const int MyLoopTime = 100;
TdEmbeddedFd::Ard_LiquidCrystalDisplayI2C lcd = TdEmbeddedFd::Ard_LiquidCrystalDisplayI2C(); // Change to (0x27,20,4) for 20x4 LCD.

TdEmbeddedFd::Ard_IoPin MyButtonPin = TdEmbeddedFd::Ard_IoPin(DD2, INPUT);
TdEmbeddedFd::Ind_Button MyButton = TdEmbeddedFd::Ind_Button(&MyButtonPin, MyLoopTime, 500, 500);


void setup() {
    Serial.begin(9600);
    lcd.TryToInitialize();
}

int LoopCounter = 0;

void loop() {
//    Serial.println((MyButtonPin.getState() == TdEmbeddedFd::PinState::On) ? "Pin On" : "Pin Off");
//    Serial.println((MyButton.LongPressTimer.IsActive()) ? "Active" : "Inactive");
//    Serial.println((MyButton.LongPressTimer.IsContinuousEventRaised()) ? "Raised" : "Not raised");
//    Serial.println((MyButton.LongPressPeriodTimer.IsActive()) ? "Period Active" : "Period Inactive");
//    Serial.println((MyButton.LongPressPeriodTimer.IsContinuousEventRaised()) ? "Period raised" : "Period not raised");

    MyButton.Update();
    if (MyButton.IsPressedEvent()) {
        lcd.SendTextConst("Clicked");
        LoopCounter = 0;
    } else if (MyButton.IsLongPressedContinuousEvent()) {
        lcd.SendTextConst("LongClick");
        LoopCounter = 0;
    } else {
        lcd.SendTextFromInt(LoopCounter);
        LoopCounter += 1;
    }

    delay(MyLoopTime);
}