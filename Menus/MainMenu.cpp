//
// Created by tmpat on 09.05.2025.
//

#include "MainMenu.h"

#include "LoreMenu.h"
#include "../Managers/JsonManager.h"

int MainMenu::printAndGetChoice() {


    int applicationState = 0;
    while(applicationState != 1 && applicationState != 2) {
        ConsoleManager::clear();

        ConsoleManager::printBoxView(
        {
            "1 - Play",
            "2 - Exit",
            "3 - The LOOOORE"
        },
        "Dungeon Crawler",
        57,
        ConsoleColor::getForegroundConsoleColor(JsonManager::UIElements["color_themes"]["main_menu"]["frame"]),
        ConsoleColor::getForegroundConsoleColor(JsonManager::UIElements["color_themes"]["main_menu"]["headings"]));

        applicationState = printAndReturnChoiceMenu(
        "",
        {1, 3}
        );
        if(applicationState == 3 ){
            LoreMenu* loremenu = new LoreMenu();
            loremenu->printAndGetChoice();
        };
    };

    if (applicationState == 2) { return 0; }

    return applicationState;
}