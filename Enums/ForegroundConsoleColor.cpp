//
// Created by Vilém on 07/06/2025.
//

#include "ForegroundConsoleColor.h"

ForegroundConsoleColor ConsoleColor::getForegroundConsoleColor(std::string text) {
    if (text == "Default") return ForegroundConsoleColor::Default;
    if (text == "White") return ForegroundConsoleColor::White;
    if (text == "Black") return ForegroundConsoleColor::Black;
    if (text == "Red") return ForegroundConsoleColor::Red;
    if (text == "Green") return ForegroundConsoleColor::Green;
    if (text == "Blue") return ForegroundConsoleColor::Blue;
    if (text == "Cyan") return ForegroundConsoleColor::Cyan;
    if (text == "Magenta") return ForegroundConsoleColor::Magenta;
    if (text == "Yellow") return ForegroundConsoleColor::Yellow;
    if (text == "Bright_White") return ForegroundConsoleColor::Bright_White;
    if (text == "Bright_Black") return ForegroundConsoleColor::Bright_Black;
    if (text == "Bright_Red") return ForegroundConsoleColor::Bright_Red;
    if (text == "Bright_Green") return ForegroundConsoleColor::Bright_Green;
    if (text == "Bright_Blue") return ForegroundConsoleColor::Bright_Blue;
    if (text == "Bright_Cyan") return ForegroundConsoleColor::Bright_Cyan;
    if (text == "Bright_Magenta") return ForegroundConsoleColor::Bright_Magenta;
    if (text == "Bright_Yellow") return ForegroundConsoleColor::Bright_Yellow;
    return ForegroundConsoleColor::Bright_White;
}

BackgroundConsoleColor ConsoleColor::getBackgroundConsoleColor(std::string text) {
    if (text == "Default") return BackgroundConsoleColor::Default;
    if (text == "White") return BackgroundConsoleColor::White;
    if (text == "Black") return BackgroundConsoleColor::Black;
    if (text == "Red") return BackgroundConsoleColor::Red;
    if (text == "Green") return BackgroundConsoleColor::Green;
    if (text == "Blue") return BackgroundConsoleColor::Blue;
    if (text == "Cyan") return BackgroundConsoleColor::Cyan;
    if (text == "Magenta") return BackgroundConsoleColor::Magenta;
    if (text == "Yellow") return BackgroundConsoleColor::Yellow;
    if (text == "Bright_White") return BackgroundConsoleColor::Bright_White;
    if (text == "Bright_Black") return BackgroundConsoleColor::Bright_Black;
    if (text == "Bright_Red") return BackgroundConsoleColor::Bright_Red;
    if (text == "Bright_Green") return BackgroundConsoleColor::Bright_Green;
    if (text == "Bright_Blue") return BackgroundConsoleColor::Bright_Blue;
    if (text == "Bright_Cyan") return BackgroundConsoleColor::Bright_Cyan;
    if (text == "Bright_Magenta") return BackgroundConsoleColor::Bright_Magenta;
    if (text == "Bright_Yellow") return BackgroundConsoleColor::Bright_Yellow;
    return BackgroundConsoleColor::Bright_White;
}