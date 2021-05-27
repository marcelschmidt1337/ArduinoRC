#!/bin/bash

if ! command -v arduino-cli &> /dev/null
then
    echo "Installing arduino-cli..."
    curl -fsSL https://raw.githubusercontent.com/arduino/arduino-cli/master/install.sh | BINDIR=. sh
    sudo mv arduino-cli /usr/local/bin/
fi

echo "Installing esp8266 board..."
arduino-cli core update-index --additional-urls http://arduino.esp8266.com/stable/package_esp8266com_index.json
arduino-cli core install esp8266:esp8266

echo "Installing library dependecies..."
arduino-cli lib install "Arduino Uno WiFi Dev Ed Library"

echo "Done!"
exit 0