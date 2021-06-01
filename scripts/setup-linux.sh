#!/bin/bash

URLS="http://arduino.esp8266.com/stable/package_esp8266com_index.json"

if ! command -v arduino-cli &> /dev/null
then
    echo "Installing arduino-cli..."
    curl -fsSL https://raw.githubusercontent.com/arduino/arduino-cli/master/install.sh | BINDIR=. sh
    sudo mv arduino-cli /usr/local/bin/
fi

echo "Installing esp8266 board..."
arduino-cli core update-index --additional-urls $URLS
arduino-cli core install esp8266:esp8266 --additional-urls $URLS

echo "Installing library dependecies..."
arduino-cli lib install "Arduino Uno WiFi Dev Ed Library"

echo ""
echo "1. Install the Arduino extension for VScode"
echo "2. Add the following lines to your VScode settings.json:"
echo -e "\e[1;31m"
echo "\"arduino.additionalUrls\": \"${URLS}\"",
echo "\"arduino.path\": \"$(dirname $(which arduino-cli))\","
echo "\"arduino.useArduinoCli\": true,"
echo "\"arduino.commandPath\": \"arduino-cli\","
echo -e "\e[1;m"
echo "Done!"
exit 0