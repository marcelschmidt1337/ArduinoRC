#include "html.h"

String html::begin_html() 
{
    String str;
    str.reserve(1024);
    str = F("<!DOCTYPE html><html>\n"
            "<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">\n"
            "<link rel=\"icon\" href=\"data:,\">\n"
            "<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n"
            ".button { background-color: #195B6A; border: none; color: white; padding: 16px 40px;\n"
            "text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}\n"
            ".button2 {background-color: #77878A;}</style></head>\n"
            "<body>\n");

    return str;
};
String html::end_html()
{
    return "</body></html>\n\n";
};
String html::h1(String str)
{
    return "<h1>" + str + "</h1>\n";
};
String html::p(String str)
{
    return "<p>" + str + "</p>\n";
};
String html::button_get(String name, String link)
{
    return "<p><a href=\"" + link + "\"><button class=\"button\">" + name + "</button></a></p>\n";
};
String html::button_post(String buttonName, String key, String value, String requestUri)
{
    String str;
    str.reserve(512);
    str = ("<form action=\"" + requestUri + "\" method=\"POST\">\n" +
           "<button class=\"button\" name=\"" + key + "\" value=\"" + value + "\">" + buttonName + "</button>\n" +
           "</form>\n");
    return str;
};