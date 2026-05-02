//
// Created by Vilém on 10/05/2025.
//

#ifndef STRINGEXTENSIONS_H
#define STRINGEXTENSIONS_H

#include <iostream>
#include <string>
#include <windows.h>
#include <regex>
#include <codecvt>


#include "../Enums/ForegroundConsoleColor.h"

class StringExtensions {
public:
    static std::string truncateFloat(float value, unsigned int decimalPlaces);
    static std::wstring stringToWideString(std::string text);
    static std::string colorizeString(std::string text, ForegroundConsoleColor foregroundColor, BackgroundConsoleColor backgroundColor = BackgroundConsoleColor::Default);
    //static std::string colorizeString(std::string text, int foregroundColor, int backgroundColor = -1);
    static std::string startColor(ForegroundConsoleColor foregroundColor, BackgroundConsoleColor backgroundColor = BackgroundConsoleColor::Default);
    static std::string endColor();
    static std::string centerString(std::string text, int width, std::string fillingString = " ");
    static std::string alignStringLeft(std::string text, int width, char fillingCharacter = ' ');
    static std::string cutoffString(std::string text, int width);
    static std::string repeatString(std::string text, int amount);
    static std::vector<std::string> createBoxView(std::vector<std::string> lines, std::string title, int width, ForegroundConsoleColor edgeForegroundColor, ForegroundConsoleColor titleForegroundColor);
    static std::string list2String(std::vector<std::string> lines);
    static std::string chainBoxViews(std::vector<std::vector<std::string>> boxViews);
    static bool isEmpty(std::string text);
};



#endif //STRINGEXTENSIONS_H
