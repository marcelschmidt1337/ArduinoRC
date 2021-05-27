#ifndef HEADER_HTML
#define HEADER_HTML

#include <WString.h>

class html {
    public:
    static String begin_html();
    static String end_html();
    static String h1(String str);
    static String p(String str);
    static String button_get(String name, String link);
    static String button_post(String buttonName, String key, String value, String requestUri);
    static String redirect(String uri);
};
#endif