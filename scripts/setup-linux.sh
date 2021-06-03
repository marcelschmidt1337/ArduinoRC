#!/bin/bash

if ! command -v code &> /dev/null
then
    echo "Error: VScode not found!"
    exit 1
fi

if ! command -v arduino-cli &> /dev/null
then
    echo "Installing arduino-cli..."
    curl -fsSL https://raw.githubusercontent.com/arduino/arduino-cli/master/install.sh | BINDIR=. sh
    sudo mv arduino-cli /usr/local/bin/
fi

source shared.sh

code ..
exit 0