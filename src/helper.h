#ifndef HEADER_HELPER
#define HEADER_HELPER

#include "state.h"

namespace helper
{
    const static String getBtnActionString(const DoorState& value)
    {
        switch (value)
        {
        case DoorState::Closed:
            return btnAction::Open;
        case DoorState::Opened:
            return btnAction::Close;

        default:
            return btnAction::Stop;
        }
    };

    const static String getStateString(const DoorState& value)
    {
        switch (value)
        {
        case DoorState::Closed:
            return "Closed";
        case DoorState::Opened:
            return "Opened";

        default:
            return "Moving...";
        }
    };

    const static bool getBool(int value)
    {
        return value == ON ? true : false;
    };
};
#endif