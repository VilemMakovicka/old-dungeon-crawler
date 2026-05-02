//
// Created by adaze on 10.05.2025.
//

#include "DifficultyMenu.h"

int DifficultyMenu::printAndGetChoice() {
    int difficulty = printAndReturnChoiceMenu(
        "Choose Difficulty:\n"
        "\n"
        "1 - Easy\n"
        "2 - Medium\n"
        "3 - Hard",
        {1, 3}
    );
    return difficulty;
}