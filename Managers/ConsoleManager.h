//
// Created by Vilém on 06/06/2025.
//

#ifndef CONSOLEMANAGER_H
#define CONSOLEMANAGER_H

#include <iostream>
#include <string>

#include "../Enums/ForegroundConsoleColor.h"
#include <windows.h>
#include <fcntl.h>
#include <vector>


class ConsoleManager {
public:
    static void print(std::string text, ForegroundConsoleColor foregroundColor = ForegroundConsoleColor::Bright_White, BackgroundConsoleColor backgroundColor = BackgroundConsoleColor::Default);
    static void printAndEscape(std::string text, ForegroundConsoleColor foregroundColor = ForegroundConsoleColor::Bright_White, BackgroundConsoleColor backgroundColor = BackgroundConsoleColor::Default);
    static void printBoxView(std::vector<std::string> lines, std::string title, int width, ForegroundConsoleColor edgeForegroundColor = ForegroundConsoleColor::Blue, ForegroundConsoleColor titleForegroundColor = ForegroundConsoleColor::Bright_White);
    static void clear();
    static void fixAnsiProblems();
    static void printLog(std::string message);
    static void printError(std::string message);
};


#endif //CONSOLEMANAGER_H
