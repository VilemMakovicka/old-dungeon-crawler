//
// Created by Vilém on 09/05/2025.
//

#include "Menu.h"

int Menu::printAndReturnChoiceMenu(std::string menuContents, Vector2 choiceRange) {
    int choice = -1;

    while (choice < choiceRange.x || choice > choiceRange.y) {
        //std::cout << menuContents << std::endl;
        ConsoleManager::printAndEscape(menuContents);
        choice = InputManager::getInt();
    }
    return choice;
}

Menu::Menu() {

}