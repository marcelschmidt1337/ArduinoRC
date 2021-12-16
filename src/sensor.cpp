#include "sensor.h"

void Sensor::Tick()
{
    if (!isTimerRunning)
    {
        return;
    }

    // Avoids overflows: https://www.norwegiancreations.com/2018/10/arduino-tutorial-avoiding-the-overflow-issue-when-using-millis-and-micros/
    if (millis() - timerStart >= period)
    {
        isTimerRunning = false;
        GetStateScheduled(true);
    }
};

void Sensor::UpdateState()
{
    GetStateScheduled(false);
};

String Sensor::ToString()
{
    return sensorStr[(int)state];
};

void Sensor::GetStateScheduled(bool isScheduled)
{
    digitalWrite(SENSOR_ENABLE, ON);
    bool isOpenSensorTriggered = helper::getBool(digitalRead(SENSOR_OPENED));
    bool isClosedSensorTriggered = helper::getBool(digitalRead(SENSOR_CLOSED));
    digitalWrite(SENSOR_ENABLE, OFF);

    if (isOpenSensorTriggered && !isClosedSensorTriggered)
    {
        state = State::Opened;
    }
    else if (!isOpenSensorTriggered && isClosedSensorTriggered)
    {
        state = State::Closed;
    }
    else if (isScheduled)
    {
        state = State::Stopped;
    }
    else
    {
        state = State::Moving;
        ScheduleStateCheck(DOOR_TIMEOUT);
    }
};

void Sensor::ScheduleStateCheck(unsigned long seconds)
{
    if (isTimerRunning)
    {
        return;
    }

    timerStart = millis();
    period = seconds;
    isTimerRunning = true;
};