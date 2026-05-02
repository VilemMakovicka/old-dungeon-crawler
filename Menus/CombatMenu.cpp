//
// Created by Vilém on 06/06/2025.
//

#include "CombatMenu.h"

void CombatMenu::printVisuals() {
    std::vector<std::vector<std::string>> boxViews;

    int maximumAbilityCount = 0;
    for (auto enemy : m_enemies) {
        if (int count = enemy->getAbilityNames().size() > maximumAbilityCount)
            maximumAbilityCount = count;
    }

    for (int i = 0; i < m_enemies.size(); i++) {
        int boxviewWidth = int(57 / m_enemies.size());
        int boxviewHeight = 2;

        if (maximumAbilityCount > 0)
            boxviewHeight += 1;

        if (i == m_enemies.size() - 1) boxviewWidth += 57%m_enemies.size();

        std::vector<std::string> lines{
            StringExtensions::centerString( m_enemies[i]->getName(), boxviewWidth - 2),
            StringExtensions::centerString("Health: "+ std::to_string(m_enemies[i]->getHealth())+" HP", boxviewWidth - 2),
            StringExtensions::centerString("Next Attack: "+ std::to_string(m_enemies[i]->getAttack())+" DMG", boxviewWidth - 2)
        };

        boxviewHeight += lines.size();

        if (m_enemies[i]->getAbilityNames().size() > 0) {
            lines.push_back(StringExtensions::colorizeString(StringExtensions::centerString("Abilities", boxviewWidth - 2, "-"), ConsoleColor::getForegroundConsoleColor(JsonManager::UIElements["color_themes"]["enemy_status"]["frame"])));
            for (std::string line : m_enemies[i]->getAbilityNames()) {
                lines.push_back(StringExtensions::centerString(line, boxviewWidth - 2));
            }
        }

        boxviewHeight += maximumAbilityCount;

        boxViews.push_back(StringExtensions::createCutoffBoxView(
            lines,
            "Enemy " + std::to_string(i+1),
            boxviewWidth,
            boxviewHeight,
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

    ConsoleManager::printLog("Enemy count: " + std::to_string(m_enemies.size()));

    for (auto enemy: m_enemies) {
        ConsoleManager::printLog("Ability count: " + std::to_string(enemy->getAbilityNames().size()));
    }
}


int CombatMenu::printAndGetChoice() {
    bool escape = false;
    while (m_playerState->GetHealth() > 0 && !escape) {
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

        if (m_playerState->getWeapon() == nullptr)
            m_enemies[choice]->damage(0);
        else {
            m_enemies[choice]->damage(m_playerState->getWeapon()->getDamage());
        }

        for (Enemy* enemy : m_enemies) {
            if (enemy->isDead()) {
                m_enemies.erase(find(m_enemies.begin(), m_enemies.end(), enemy));
            }
        }

        for (Enemy* enemy : m_enemies) {
            enemy->activateRandomAbility(m_playerState, m_enemies);
            m_playerState->damagePlayer(enemy->getAttack());
        }
    }

    return 0;
}

CombatMenu::CombatMenu(PlayerState *playerState, std::vector<Enemy *> enemies) {
    m_playerState = playerState;
    m_enemies = enemies;
}
