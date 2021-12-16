#include "dooraction.h"

void DoorAction::setAction(String action)
{
    doorAction = (Action)actionStr->indexOf(action);
};

void DoorAction::setAction(Sensor::State state)
{
    switch (state)
    {
    case Sensor::State::Opened:
        doorAction = Action::Close;
        break;
    case Sensor::State::Closed:
        doorAction = Action::Open;
        break;
    case Sensor::State::Moving:
        doorAction = Action::Stop;
        break;
    case Sensor::State::Stopped:
        doorAction = Action::Close;

    default:
        doorAction = Action::Unknown;
    }
};

void DoorAction::updateAction()
{
    int nextIndex = ((int)doorAction + 1) % actionStr->length() - 1;
    doorAction = (Action)nextIndex;
};

String DoorAction::toString()
{
    return doorAction == Action::Unknown ? "" : actionStr[(int)doorAction];
};

Sensor::State DoorAction::getDesiredSensorState()
{
    switch (doorAction)
    {
    case Action::Open:
        return Sensor::State::Opened;
    case Action::Stop:
        return Sensor::State::Closed;
    case Action::Close:
        return Sensor::State::Closed;

    default:
        return Sensor::State::Stopped;
    }
};