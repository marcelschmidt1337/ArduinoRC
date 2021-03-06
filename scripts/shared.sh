URLS="http://arduino.esp8266.com/stable/package_esp8266com_index.json"

echo "Installing esp8266 board..."
arduino-cli core update-index --additional-urls $URLS
arduino-cli core install esp8266:esp8266 --additional-urls $URLS

echo "Installing library dependencies..."
arduino-cli lib install "Arduino Uno WiFi Dev Ed Library"

echo "Creating VScode settings..."
mkdir -p ../.vscode
cat > ../.vscode/settings.json << EOL
{
    "arduino.additionalUrls": "${URLS}",
    "arduino.path": "$(dirname $(which arduino-cli))",
    "arduino.useArduinoCli": true,
    "arduino.commandPath": "arduino-cli",
}
EOL

echo "Creating Arduino extension settings..."
cat > ../.vscode/arduino.json << EOL
{
    "sketch": "remote_control.ino",
    "board": "esp8266:esp8266:nodemcuv2",
    "output": "build"
}
EOL

echo "Install VScode Arduino extension..."
code --install-extension vsciot-vscode.vscode-arduino


echo "Done!"