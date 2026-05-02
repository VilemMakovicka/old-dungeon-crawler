//
// Created by Vilém on 10/06/2025.
//

#include "Ability_PlayerHeal.h"

void Ability_PlayerHeal::activate(PlayerState* playerState, std::vector<Enemy*> enemies) {
    ConsoleManager::printLog("Activating ability \"" + m_name + "\"...");
    try {
        if (Random::getRandomBool(m_chanceToActivate)) {
            playerState->heal(m_amount);
            ConsoleManager::printLog("Ability \"" + m_name + "\" successfuly activated!");
        }
        else {
            ConsoleManager::printLog("Ability \"" + m_name + "\" failed!");
        }
    }
    catch (...) {
        ConsoleManager::printError("Could not activate ability \"" + m_name + "\".");
    }
}

/**
 *
 * @param name Jméno ability
 * @param chanceToActivate Percentuální šance na aktivování po výběru ability
 * @param amount O kolik se hráči zvýší životy po aktivaci ability
 */
Ability_PlayerHeal::Ability_PlayerHeal(std::string name, int chanceToActivate, int amount) :
EnemyAbility(name){
    m_chanceToActivate = chanceToActivate;
    m_amount = amount;
}

