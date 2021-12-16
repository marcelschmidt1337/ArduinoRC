#ifndef HEADER_SENSOR
#define HEADER_SENSOR

#include "helper.h"
#include "const.h"
#include <WString.h>

class Sensor
{
public:
    enum State
    {
        Opened = 0,
        Closed = 1,
        Moving = 2,
        Stopped = 3
    };

    void Tick();
    void UpdateState();
    String ToString();

    State GetState()
    {
        return state;
    }

private:
    const String sensorStr[4]{"Opened", "Closed", "Moving...", "Stopped"};

    bool isTimerRunning = false;
    unsigned long timerStart = 0;
    unsigned long period = 0;

    State state;

    void GetStateScheduled(bool isScheduled);
    void ScheduleStateCheck(unsigned long seconds);
};

#endif