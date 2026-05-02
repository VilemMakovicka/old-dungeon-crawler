//
// Created by alaf4 on 09.05.2025.
//

#include "DeathMenu.h"

#include "GameInstance.h"

int DeathMenu::printAndGetChoice() {
    if (GameInstance::s_savedGameState == nullptr) {
        int applicationState = printAndReturnChoiceMenu(
        "You Died\n"
        "\n"
        "1 - New Game\n"
        "2 - Exit Game\n",
        {1, 2}
        );
        if (applicationState == 2) { return 0; }

        return applicationState;
    }

    GameInstance::s_savedGameState->GetPlayerState()->getWeapon();

    int applicationState = printAndReturnChoiceMenu(
        "You Died\n"
        "\n"
        "1 - New Game\n"
        "2 - Load last save\n"
        "3 - Exit Game",
        {1, 3}
    );
    if (applicationState == 3) { return 0; }

    return applicationState;
}
