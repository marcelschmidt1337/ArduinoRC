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

static const int REFRESH_SECONDS = 1;
static const unsigned long DOOR_TIMEOUT = 15;

#endif