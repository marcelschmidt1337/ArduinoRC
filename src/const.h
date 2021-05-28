#ifndef HEADER_CONST
#define HEADER_CONST

#define DOOR_CONTROL  D1
#define SENSOR_OPENED D6
#define SENSOR_CLOSED D7
#define SENSOR_ENABLE D5

#define ON  LOW
#define OFF HIGH

static const String DNS  = "garage";
static const String SSID = "ESPsoftAP_01";
static const String PW   = "pass-to-soft-AP";

namespace btnAction
{
    const static String Open  = "open";
    const static String Close = "close";
    const static String Stop  = "stop";
};

#endif