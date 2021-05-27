#ifndef HEADER_HELPER
#define HEADER_HELPER

namespace helper
{
    const static String getString(bool value)
    {
        return value ? "on" : "off";
    };

    const static bool getBool(String value)
    {
        return value == "on" ? true : false;
    };

    const static uint8_t getDigitalValue(bool value)
    {
        return value ? LOW : HIGH;
    };
};
#endif