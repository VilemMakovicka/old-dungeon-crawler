//
// Created by Vilém on 06/06/2025.
//

#include "CombatMenu.h"

void CombatMenu::printVisuals() {
    std::vector<std::vector<std::string>> boxViews;

    for (int i = 0; i < m_enemies.size(); i++) {
        int boxviewSize = int(57 / m_enemies.size());

        if (i == m_enemies.size() - 1) boxviewSize += 57%m_enemies.size();

        std::vector<std::string> lines{
            StringExtensions::centerString(m_enemies[i]->getName(), boxviewSize - 2),
            StringExtensions::centerString(std::to_string(m_enemies[i]->getHealth()), boxviewSize - 2)
        };
        boxViews.push_back(StringExtensions::createBoxView(
            lines,
            "Enemy " + std::to_string(i),
            boxviewSize,
            ConsoleColor::getForegroundConsoleColor(JsonManager::UIElements["color_themes"]["enemy_status"]["frame"]),
            ConsoleColor::getForegroundConsoleColor(JsonManager::UIElements["color_themes"]["enemy_status"]["headings"])
            ));
    }

    ConsoleManager::printAndEscape(StringExtensions::chainBoxViews(boxViews));

    std::vector<std::string> lines{
        StringExtensions::centerString("Health " + m_playerState->getHealthAsString(), 55),
        StringExtensions::centerString(m_playerState->getHealthVisualized(), 55),
        "",
        StringExtensions::centerString("Your weapon", 55),
        StringExtensions::centerString(m_playerState->getWeaponStatus(), 55),
    };
    ConsoleManager::printBoxView(
        lines,
        "Your status",
        57,
        ConsoleColor::getForegroundConsoleColor(JsonManager::UIElements["color_themes"]["player_status"]["frame"]),
        ConsoleColor::getForegroundConsoleColor(JsonManager::UIElements["color_themes"]["player_status"]["headings"])
        );
}


int CombatMenu::printAndGetChoice() {
    bool escape = false;
    while (m_playerState->GetHealth() > 0 && escape == false) {
        if (m_enemies.size() <= 0) return 0;

        ConsoleManager::clear();
        printVisuals();

        int choiceCount = m_enemies.size() + 1;

        std::string choices;
        for (int i = 0; i < m_enemies.size(); i++) {
            choices += std::to_string(i + 1) + " - Fight with " + m_enemies[i]->getName() + "\n";
        }
        choices += std::to_string(choiceCount) + " - Escape";

        int choice = printAndReturnChoiceMenu(
            choices,
            {1, choiceCount}
        ) - 1;

        if (choice == m_enemies.size()) {
            ConsoleManager::printLog("Player chose to escape, returning...");
            return 0;
        }

        m_enemies[choice]->damage(m_playerState->getWeapon()->getDamage());

        for (Enemy* enemy : m_enemies) {
            if (enemy->isDead()) {
                m_enemies.erase(find(m_enemies.begin(), m_enemies.end(), enemy));
            }
        }

        for (Enemy* enemy : m_enemies) {
            m_playerState->damagePlayer(enemy->getAttack());
        }
    }

    return 0;
}

CombatMenu::CombatMenu(PlayerState *playerState, std::vector<Enemy *> enemies) {
    m_playerState = playerState;
    m_enemies = enemies;
}
