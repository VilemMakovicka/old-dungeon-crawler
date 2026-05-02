//
// Created by Vilém on 06/06/2025.
//

#include "BossEnemy.h"

BossEnemy::BossEnemy(nlohmann::json attributes) : Enemy() {
    m_name = attributes["name"];
    m_health = static_cast<int>(attributes["health"]) * GameInstance::s_currentGameDifficulty;
    m_minimumDamage = static_cast<int>(attributes["damage_range"][0]) * GameInstance::s_currentGameDifficulty;
    m_maximumDamage = static_cast<int>(attributes["damage_range"][1]) * GameInstance::s_currentGameDifficulty;

    try { m_lootTable = attributes["loot"]; }
    catch (...) { ConsoleManager::printError("Could not load loot table for " + m_name); }
    try { m_symbol = attributes["symbol"]; }
    catch (...) {
        ConsoleManager::printError("Could not load symbol for " + m_name);
        m_symbol = JsonManager::toString(JsonManager::allTiles["enemy"]["string"]);
    }

    for (nlohmann::json ability : attributes["abilities"]) {
        m_abilities.push_back(EnemyAbility::getEnemyAbility(ability));
    }
}

BossEnemy::~BossEnemy() {

}

std::string BossEnemy::getSymbol() {
    return m_symbol;
}


int BossEnemy::getAttack() {
    return Random::getRandomInt(m_minimumDamage, m_maximumDamage);
}

int BossEnemy::getHealth() {
    return m_health;
}

std::string BossEnemy::getName() {
    return m_name;
}

void BossEnemy::damage(int amount) {
    if (m_health - amount < 0) {
        m_health = 0;
        m_dead = true;
    }

    m_health -= amount;
}
