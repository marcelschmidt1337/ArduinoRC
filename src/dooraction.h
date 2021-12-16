#ifndef HEADER_DOOR
#define HEADER_DOOR

#include "sensor.h"
#include <WString.h>

class DoorAction
{
public:
    enum Action
    {
        Unknown = -1,
        Open = 0,
        Stop = 1,
        Close = 2
    };

    void setAction(String action);
    void setAction(Sensor::State state);
    void updateAction();
    String toString();
    Sensor::State getDesiredSensorState();

private:
    const String actionStr[3]{"open", "stop", "close"};
    Action doorAction = Action::Unknown;
};

#endif