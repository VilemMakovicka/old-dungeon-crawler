//
// Created by tmpat on 09.05.2025.
//

#include "MainMenu.h"

int MainMenu::printAndGetChoice() {
    ConsoleManager::clear();
    int applicationState = printAndReturnChoiceMenu(
        "Dungeon Crawler\n"
        "\n"
        "1 - Play\n"
        "2 - Exit",
        {1, 2}
    );
    if (applicationState == 2) { return 0; }

    return applicationState;
}
