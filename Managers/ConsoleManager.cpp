//
// Created by Vilém on 06/06/2025.
//

#include "ConsoleManager.h"
#include "StringExtensions.h"

void ConsoleManager::EnableUTF8andANSI() {
#ifdef _WIN32
    // Get the handle to the standard output
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut == INVALID_HANDLE_VALUE) {
        std::cerr << "Error: Unable to get stdout handle.\n";
    }

    DWORD dwMode = 0;
    if (!GetConsoleMode(hOut, &dwMode)) {
        std::cerr << "Error: Unable to get console mode.\n";
    }

    // Add ENABLE_VIRTUAL_TERMINAL_PROCESSING flag
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    if (!SetConsoleMode(hOut, dwMode)) {
        std::cerr << "Error: Unable to set console mode. ANSI may not be supported on this system.\n";
    }

    // Set console output to UTF-8
    SetConsoleOutputCP(CP_UTF8);
    _setmode(_fileno(stdout), _O_U8TEXT);
#endif
}

void ConsoleManager::clear() {
    std::wcout << std::endl;
    system("cls");
}

void ConsoleManager::printError(std::string message) {
    //printAndEscape(message, ForegroundConsoleColor::Bright_Red);
}

void ConsoleManager::printLog(std::string message) {
    //printAndEscape(message, ForegroundConsoleColor::Bright_Cyan);
}

void ConsoleManager::printBoxView(std::vector<std::string> lines, std::string title, int width, ForegroundConsoleColor edgeForegroundColor, ForegroundConsoleColor titleForegroundColor) {
    printAndEscape(StringExtensions::list2String(StringExtensions::createBoxView(lines, title, width, edgeForegroundColor, titleForegroundColor)));
}

void ConsoleManager::print(std::string text, ForegroundConsoleColor foregroundColor, BackgroundConsoleColor backgroundColor) {
    std::string printedString = StringExtensions::colorizeString(text, foregroundColor, backgroundColor);
    std::wcout << StringExtensions::stringToWideString(printedString);
}

void ConsoleManager::printAndEscape(std::string text, ForegroundConsoleColor foregroundColor, BackgroundConsoleColor backgroundColor) {
    print(text + "\n", foregroundColor, backgroundColor);
}

void ConsoleManager::printAndEscape(std::vector<std::string> lineList, ForegroundConsoleColor foregroundColor, BackgroundConsoleColor backgroundColor) {
    print(StringExtensions::list2String(lineList) + "\n", foregroundColor, backgroundColor);
}
