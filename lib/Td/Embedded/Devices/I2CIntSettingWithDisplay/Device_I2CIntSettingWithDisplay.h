//
// Created by tomasdrah on 02.03.2024.
//

#ifndef VENTILATIONSYSTEM_EMBEDED_DEVICE_I2CINTSETTINGWITHDISPLAY_H
#define VENTILATIONSYSTEM_EMBEDED_DEVICE_I2CINTSETTINGWITHDISPLAY_H

#include "Embedded/Fd/Bases/Comunication/General/TextSender.h"
#include "Embedded/Fd/Bases/IoPin.h"
#include "Embedded/Fd/Bases/IPressable.h"

namespace TdEmbeddedFd {


    class Setting {
    public:
        signed char value;
    };


    class Device_I2CIntSettingWithDisplay {
    public:

        Device_I2CIntSettingWithDisplay(
                TextSender *textSenderSettingName,
                TextSender *textSenderSettingValue,
                IPressable *nextButton,
                IPressable *previousButton,
                IPressable *upButton,
                IPressable *downButton,
                signed char settingsSize
        ) : TextSender_SettingName(textSenderSettingName),
            TextSender_SettingValue(textSenderSettingValue),
            NextButton(nextButton),
            PreviousButton(previousButton),
            UpButton(upButton),
            DownButton(downButton) {
            if (settingsSize > MaxSettingsSize)
                settingsSize = MaxSettingsSize;
            SettingsSize = settingsSize;
        }

        bool TryToTryToInitialize() {
            RefreshDisplayedSetting();
            return true;
        }

        void Update() {
            CheckNextSetting();
            CheckPreviousSetting();
            CheckRaiseValue();
            CheckLowerValue();
        }

        signed char GetSetting(signed char settingId) {
            if (settingId >= 0 && settingId < SettingsSize) {
                return Settings[settingId].value;
            }
            return -1;
        }

        void SetSetting(signed char settingId, signed char value) {
            if (settingId < SettingsSize) {
                Settings[settingId].value = value;
                RefreshDisplayedSettingIfMatching(settingId);
            }
        }

    private:
        static const signed char MaxSettingsSize = 10;
        Setting Settings[MaxSettingsSize]{};
        signed char SettingsSize = 10;

        signed char CurrentlyDisplayedSetting = 0;

        TextSender *TextSender_SettingName;
        TextSender *TextSender_SettingValue;
        IPressable *NextButton;
        IPressable *PreviousButton;
        IPressable *UpButton;
        IPressable *DownButton;

        void RefreshDisplayedSettingIfMatching(signed char settingId) {
            if (settingId == CurrentlyDisplayedSetting) {
                DisplaySetting(settingId);
            }
        }

        void RefreshDisplayedSetting() {
            DisplaySetting(CurrentlyDisplayedSetting);
        }


        void DisplaySetting(signed char settingId) {
            if (settingId < SettingsSize) {
                TextSender_SettingName->SendTextFromInt(settingId);
                TextSender_SettingValue->SendTextFromInt(Settings[settingId].value);
            }
        }

        void CheckNextSetting() {
            if (NextButton->IsPressedEvent()) {
                CurrentlyDisplayedSetting++;
                if (CurrentlyDisplayedSetting >= SettingsSize) {
                    CurrentlyDisplayedSetting = 0;
                }
                RefreshDisplayedSetting();
            }
        }

        void CheckPreviousSetting() {
            if (PreviousButton->IsPressedEvent()) {
                CurrentlyDisplayedSetting--;
                if (CurrentlyDisplayedSetting < 0) {
                    CurrentlyDisplayedSetting = (signed char) (SettingsSize - 1);
                }
                RefreshDisplayedSetting();
            }
        }

        void CheckRaiseValue() {
            if (UpButton->IsPressedEvent()) {
                ChangeSettingValueBy(1);
                RefreshDisplayedSetting();
            }
            if (UpButton->IsLongPressedContinuousEvent()) {
                ChangeSettingValueBy(1);
                RefreshDisplayedSetting();
            }
        }

        void CheckLowerValue() {
            if (DownButton->IsPressedEvent()) {
                ChangeSettingValueBy(-1);
                RefreshDisplayedSetting();
            }
            if (DownButton->IsLongPressedContinuousEvent()) {
                ChangeSettingValueBy(-1);
                RefreshDisplayedSetting();
            }
        }

        void ChangeSettingValueBy(signed char byValue) {
            int newValue = Settings[CurrentlyDisplayedSetting].value + byValue;
            if (newValue > 127)
                newValue = 127;
            if (newValue < 0)
                newValue = 0;
            Settings[CurrentlyDisplayedSetting].value = (signed char) newValue;
        }

    };

} // TdEmbeddedFd

#endif //VENTILATIONSYSTEM_EMBEDED_DEVICE_I2CINTSETTINGWITHDISPLAY_H
