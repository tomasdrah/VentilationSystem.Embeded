//
// Created by tomasdrah on 02.03.2024.
//

#ifndef VENTILATIONSYSTEM_EMBEDED_LOOPTIMER_H
#define VENTILATIONSYSTEM_EMBEDED_LOOPTIMER_H

namespace TdEmbeddedFd {

    class LoopTimer {
    public:
        LoopTimer(unsigned int mainLoopTakesMs, unsigned long raiseTheEventAfter)
                : MainLoopTakesMs(mainLoopTakesMs),
                  RaiseTheEventAfter(raiseTheEventAfter) {}

        bool IsContinuousEventRaised() {
            return EventRaised;
        }

        void ResetTheEvent() {
            EventRaised = false;
            ElapsedMillis = 0;
        }

        void StartListeningForTheEvent() {
            ListeningForEvent = true;
            ResetTheEvent();
        }

        void StopListeningForTheEvent() {
            ListeningForEvent = false;
            ResetTheEvent();
        }
        bool IsActive (){
            return ListeningForEvent;
        }

        void Update() {
            if (ListeningForEvent) {
                ElapsedMillis += MainLoopTakesMs;

                if (ElapsedMillis >= RaiseTheEventAfter) {
                    EventRaised = true;
                }
            }
        }

    private:
        unsigned int MainLoopTakesMs = 100;
        unsigned long RaiseTheEventAfter = 500;

        bool ListeningForEvent = false;
        bool EventRaised = false;
        unsigned long ElapsedMillis = 0;
    };

} // TdEmbeddedFd

#endif //VENTILATIONSYSTEM_EMBEDED_LOOPTIMER_H
