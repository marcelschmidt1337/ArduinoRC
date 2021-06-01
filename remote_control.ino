#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <ESP8266WebServer.h>

#include "src/dooraction.h"
#include "src/sensor.h"
#include "src/const.h"
#include "src/html.h"
#include "src/helper.h"

ESP8266WebServer server(80);
DoorAction doorAction;
SensorState desiredState = SensorState::Undefined;

void renderHtml();
void redirectToRoot();
void handleApi();
SensorState getDoorState();

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

    SensorState initialState = getDoorState();
    desiredState = initialState;
    doorAction.setAction(initialState);

    Serial.print("Setting soft-AP ... ");
    bool result = WiFi.softAP(SSID, PW);
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

    SensorState state = getDoorState();

    if (state != SensorState::Undefined)
    {
        doorAction.setAction(state);
    }

    String btnName = doorAction.toString();
    btnName.toUpperCase();

    content = html::begin_html() +
              html::h1("Remote Control") +
              html::p("Door: " + helper::getStateString(state)) +
              html::button_post(btnName, "door", doorAction.toString(), "/api") +
              html::end_html();

    if(state != desiredState)
    {
        server.sendHeader("Refresh", String(REFRESH_SECONDS));
    }

    server.send(200, "text/html", content);
}

void redirectToRoot()
{
    server.sendHeader("Location", "/");
    server.send(303);
}

void handleApi()
{
    // Tor geht auf -> stop -> geht zu
    // Tor geht zu -> kurz stop dann geht auf
    if (server.hasArg("door"))
    {
        digitalWrite(DOOR_CONTROL, ON);
        delay(100);
        digitalWrite(DOOR_CONTROL, OFF);

        doorAction.updateAction();
        desiredState = helper::getStateFromBtnAction(server.arg("door"));
    }
    redirectToRoot();
}

SensorState getDoorState()
{
    digitalWrite(SENSOR_ENABLE, ON);
    bool isOpenSensorTriggered = helper::getBool(digitalRead(SENSOR_OPENED));
    bool isClosedSensorTriggered = helper::getBool(digitalRead(SENSOR_CLOSED));
    digitalWrite(SENSOR_ENABLE, OFF);

    if (isOpenSensorTriggered && !isClosedSensorTriggered)
    {
        return SensorState::Opened;
    }
    else if (!isOpenSensorTriggered && isClosedSensorTriggered)
    {
        return SensorState::Closed;
    }
    else
    {
        return SensorState::Undefined;
    }
}