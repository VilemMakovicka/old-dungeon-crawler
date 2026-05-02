//
// Created by adaze on 10.05.2025.
//

#include "DifficultyMenu.h"
#include "../Managers/StringExtensions.h"
#include "../Managers/JsonManager.h"

int DifficultyMenu::printAndGetChoice() {
    ConsoleManager::clear();

    ConsoleManager::printBoxView(
    {
        "1 - Easy",
        "2 - Medium",
        "3 - Hard"
    },
    "Choose difficulty",
    57,
    ConsoleColor::getForegroundConsoleColor(JsonManager::UIElements["color_themes"]["difficulty_menu"]["frame"]),
    ConsoleColor::getForegroundConsoleColor(JsonManager::UIElements["color_themes"]["difficulty_menu"]["headings"]));
    int difficulty = printAndReturnChoiceMenu(
        "",
        {1, 3}
    );
    return difficulty;
}
