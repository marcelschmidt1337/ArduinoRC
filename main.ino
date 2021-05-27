#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <ESP8266WebServer.h>

#include "src/const.h"
#include "src/html.h"
#include "src/helper.h"


ESP8266WebServer server(80);
bool isLedEnabled = false;
bool isDoorOpened = false;

void renderHtml();
void redirectToRoot();
void handleApi();


void setup()
{
    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(D1, OUTPUT);

    digitalWrite(LED_BUILTIN, helper::getDigitalValue(isLedEnabled));
    digitalWrite(D1, helper::getDigitalValue(isDoorOpened));

    Serial.begin(115200);
    Serial.println();

    Serial.print("Setting soft-AP ... ");
    boolean result = WiFi.softAP(SSID, PW);
    if (result == true)
    {
        Serial.println("Ready");
        server.on("/", HTTP_GET, renderHtml);
        server.on("/api", HTTP_POST, handleApi);
        server.onNotFound(redirectToRoot);
        server.begin();
        Serial.println("HTTP server started");
    }
    else
    {
        Serial.println("Failed to start soft AP!");
        return;
    }

    if (result == true && MDNS.begin(DNS))
    {
        MDNS.addService("http", "tcp", 80);
        Serial.println("mDNS responder started, connect to: " + DNS + ".local");
    }
    else
    {
        Serial.println("Error setting up MDNS responder!");
        Serial.println("Connect to: " + WiFi.localIP().toString());
    }
}

void loop()
{
    server.handleClient();
    MDNS.update();
}

void renderHtml()
{
    String content;
    content.reserve(1024);

    String btnName = helper::getString(!isLedEnabled);
    btnName.toUpperCase();

    String doorBtnName = helper::getString(!isDoorOpened);
    doorBtnName.toUpperCase();

    content = html::begin_html() +
              html::h1("Remote Control") +
              html::p("LED: " + helper::getString(isLedEnabled)) +
              html::button_post(btnName, "led", helper::getString(!isLedEnabled), "/api") +
              html::p("Door: " + helper::getString(isDoorOpened)) +
              html::button_post(doorBtnName, "door", helper::getString(!isDoorOpened), "/api") +
              html::end_html();

    server.send(200, "text/html", content);
}

void redirectToRoot()
{
    server.sendHeader("Location","/");
    server.send(303);
}

void handleApi()
{
    if(server.hasArg("led"))
    {
        isLedEnabled = helper::getBool(server.arg("led"));
        digitalWrite(LED_BUILTIN, helper::getDigitalValue(isLedEnabled));
    }
    else if (server.hasArg("door"))
    {
        isDoorOpened = helper::getBool(server.arg("door"));
        digitalWrite(D1, helper::getDigitalValue(isDoorOpened));
    }
    redirectToRoot();
}