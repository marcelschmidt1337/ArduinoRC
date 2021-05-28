#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <ESP8266WebServer.h>

#include "src/state.h"
#include "src/const.h"
#include "src/html.h"
#include "src/helper.h"

ESP8266WebServer server(80);

void renderHtml();
void redirectToRoot();
void handleApi();

DoorState getDoorState();

void setup()
{
    Serial.begin(115200);
    Serial.println();

    pinMode(DOOR_CONTROL, OUTPUT);
    pinMode(SENSOR_OPENED, INPUT_PULLUP);
    pinMode(SENSOR_CLOSED, INPUT_PULLUP);
    pinMode(SENSOR_ENABLE, OUTPUT);

    digitalWrite(DOOR_CONTROL, OFF);
    digitalWrite(SENSOR_ENABLE, OFF);

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

    DoorState state = getDoorState();

    String btnName = helper::getBtnActionString(state);
    btnName.toUpperCase();

    content = html::begin_html() +
              html::h1("Remote Control") +
              html::p("Door: " + helper::getStateString(state)) +
              html::button_post(btnName, "door", helper::getBtnActionString(state), "/api") +
              html::end_html();

    server.send(200, "text/html", content);
}

void redirectToRoot()
{
    server.sendHeader("Location", "/");
    server.send(303);
}

void handleApi()
{
    if (server.hasArg("door"))
    {
        digitalWrite(DOOR_CONTROL, ON);
        delay(100);
        digitalWrite(DOOR_CONTROL, OFF);
    }
    redirectToRoot();
}

DoorState getDoorState()
{
    digitalWrite(SENSOR_ENABLE, ON);
    bool isOpenSensorTriggered = helper::getBool(digitalRead(SENSOR_OPENED));
    bool isClosedSensorTriggered = helper::getBool(digitalRead(SENSOR_CLOSED));
    digitalWrite(SENSOR_ENABLE, OFF);

    if (isOpenSensorTriggered && !isClosedSensorTriggered)
    {
        return DoorState::Opened;
    }
    else if (!isOpenSensorTriggered && isClosedSensorTriggered)
    {
        return DoorState::Closed;
    }
    else
    {
        return DoorState::Undefined;
    }
}