//
// Created by tomasdrah on 02.03.2024.
//

#ifndef VENTILATIONSYSTEM_EMBEDED_IND_BUTTON_H
#define VENTILATIONSYSTEM_EMBEDED_IND_BUTTON_H

#include "Embedded/Fd/Bases/LoopTimer.h"
#include "Embedded/Fd/Bases/Button.h"

namespace TdEmbeddedFd {

    class Ind_Button : public Button {
    public:
        Ind_Button(IoPin *pin, unsigned int loopTimeMs, unsigned int longPressAfterMs, unsigned int LongPressEachMs) : Pin(pin) {
            LongPressTimer = LoopTimer(loopTimeMs, longPressAfterMs);
            LongPressPeriodTimer = LoopTimer(loopTimeMs, LongPressEachMs);
        }

        void Update() override {
            PressedEventRaised = false;
            LongPressedContinuousEventRaised = false;

            if (IsPressed()) {
                // Check if button is pressed
                if (!InPressedPeriod) {
                    // Button got pressed
                    InPressedPeriod = true;
                    LongPressTimer.StartListeningForTheEvent();
                }
            } else {
                // Button is released
                if (InPressedPeriod) {
                    // Button got released
                    PressedEventRaised = true;
                    InPressedPeriod = false;
                    LongPressTimer.StopListeningForTheEvent();
                    LongPressPeriodTimer.StopListeningForTheEvent();
                }
            }

            if (InPressedPeriod) {
                bool PreviousLongPressState = LongPressTimer.IsContinuousEventRaised();
                LongPressTimer.Update();

                if (LongPressTimer.IsContinuousEventRaised()) {
                    if (!PreviousLongPressState) {
                        // First long term press event
                        LongPressedContinuousEventRaised = true;
                        LongPressPeriodTimer.StartListeningForTheEvent();
                    }
                    LongPressPeriodTimer.Update();
                    if (LongPressPeriodTimer.IsContinuousEventRaised()) {
                        LongPressedContinuousEventRaised = true;
                        LongPressPeriodTimer.ResetTheEvent();
                    }
                }
            }
        }

        bool IsPressedEvent() override {
            return PressedEventRaised;
        }

        bool IsLongPressedContinuousEvent() override {
            return LongPressedContinuousEventRaised;
        }

//    private:
        LoopTimer LongPressTimer = LoopTimer(100, 500);
        LoopTimer LongPressPeriodTimer = LoopTimer(100, 500);

        bool PressedEventRaised = false;
        bool LongPressedContinuousEventRaised = false;
        bool InPressedPeriod = false;

        IoPin *Pin;

        bool IsPressed() {
            return Pin->getState() == PinState::On;
        }
    };

} // TdEmbeddedFd

#endif //VENTILATIONSYSTEM_EMBEDED_IND_BUTTON_H
