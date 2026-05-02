//
// Created by Vilém on 06/06/2025.
//

#ifndef CONSOLECOLOR_H
#define CONSOLECOLOR_H

#endif //CONSOLECOLOR_H

#pragma once

#include <iostream>

enum class ForegroundConsoleColor {
    Default = 0,
    Black = 30,
    Red = 31,
    Green = 32,
    Yellow = 33,
    Blue = 34,
    Magenta = 35,
    Cyan = 36,
    White = 37,
    Bright_Black = 90,
    Bright_Red = 91,
    Bright_Green = 92,
    Bright_Yellow = 93,
    Bright_Blue = 94,
    Bright_Magenta = 95,
    Bright_Cyan = 96,
    Bright_White = 97,
};

enum class BackgroundConsoleColor {
    Default = 0,
    Black = 40,
    Red = 41,
    Green = 42,
    Yellow = 43,
    Blue = 44,
    Magenta = 45,
    Cyan = 46,
    White = 47,
    Bright_Black = 100,
    Bright_Red = 101,
    Bright_Green = 102,
    Bright_Yellow = 103,
    Bright_Blue = 104,
    Bright_Magenta = 105,
    Bright_Cyan = 106,
    Bright_White = 107,
};

class ConsoleColor {
public:
    static ForegroundConsoleColor getForegroundConsoleColor(std::string text);
    static BackgroundConsoleColor getBackgroundConsoleColor(std::string text);
};