#!/bin/zsh

if ! command -v brew &> /dev/null
then
    echo "Error: Homebrew not found!"
    exit 1
fi

if ! command -v code &> /dev/null
then
    echo "Installing Visual Studio Code..."
    brew install visual-studio-code
fi

if ! command -v arduino-cli &> /dev/null
then
    echo "Installing arduino-cli..."
    brew install arduino-cli
fi

source shared.sh

code ..
exit 0