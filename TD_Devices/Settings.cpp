#include <Arduino.h>
#include "Embedded/Fd/Arduino/Displays/I2CLiquidCrystalDisplays/Ard_LiquidCrystalDisplayI2C.h"
#include "Embedded/Devices/I2CIntSettingWithDisplay/Device_I2CIntSettingWithDisplay.h"
#include <Adafruit_I2CDevice.h>
#include <Adafruit_SPIDevice.h>

#include "Embedded/Fd/Independent/Ind_Button.h"
#include "Embedded/Fd/Arduino/Ard_IoPin.h"
#include "Embedded/Fd/Arduino/Comunication/I2C/Ard_I2C.h"

static const int MyLoopTime = 100;

LiquidCrystal_I2C LCD_LiquidCrystal_I2C = LiquidCrystal_I2C(0x27, 16, 2);
TdEmbeddedFd::Ard_LiquidCrystalDisplayI2C lcd_line0 = TdEmbeddedFd::Ard_LiquidCrystalDisplayI2C(&LCD_LiquidCrystal_I2C,0);
TdEmbeddedFd::Ard_LiquidCrystalDisplayI2C lcd_line1 = TdEmbeddedFd::Ard_LiquidCrystalDisplayI2C(&LCD_LiquidCrystal_I2C,1);


static const int LongPressButtonDelay = 1000;
static const int LongPressButtonStep = 100;
TdEmbeddedFd::Ard_IoPin NextButtonPin = TdEmbeddedFd::Ard_IoPin(DD2, INPUT);
TdEmbeddedFd::Ind_Button NextButton = TdEmbeddedFd::Ind_Button(&NextButtonPin, MyLoopTime, LongPressButtonDelay, LongPressButtonStep);
TdEmbeddedFd::Ard_IoPin PreviousButtonPin = TdEmbeddedFd::Ard_IoPin(DD3, INPUT);
TdEmbeddedFd::Ind_Button PreviousButton = TdEmbeddedFd::Ind_Button(&PreviousButtonPin, MyLoopTime, LongPressButtonDelay, LongPressButtonStep);
TdEmbeddedFd::Ard_IoPin UpButtonPin = TdEmbeddedFd::Ard_IoPin(DD4, INPUT);
TdEmbeddedFd::Ind_Button UpButton = TdEmbeddedFd::Ind_Button(&UpButtonPin, MyLoopTime, LongPressButtonDelay, LongPressButtonStep);
TdEmbeddedFd::Ard_IoPin DownButtonPin = TdEmbeddedFd::Ard_IoPin(DD5, INPUT);
TdEmbeddedFd::Ind_Button DownButton = TdEmbeddedFd::Ind_Button(&DownButtonPin, MyLoopTime, LongPressButtonDelay, LongPressButtonStep);


TdEmbeddedFd::Device_I2CIntSettingWithDisplay settingWithDisplay = TdEmbeddedFd::Device_I2CIntSettingWithDisplay(&lcd_line0,&lcd_line1,&NextButton,&PreviousButton,&UpButton,&DownButton,3);


TdEmbeddedFd::Ard_I2C MyI2CSlave = TdEmbeddedFd::Ard_I2C(1000,10);

void setup() {
    Serial.begin(9600);
    lcd_line0.TryToInitialize();
    lcd_line1.TryToInitialize();
    settingWithDisplay.TryToTryToInitialize();
}


void loop() {
    NextButton.Update();
    PreviousButton.Update();
    UpButton.Update();
    DownButton.Update();

    settingWithDisplay.Update();

    delay(MyLoopTime);
}