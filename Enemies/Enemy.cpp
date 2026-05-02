//
// Created by Vilém on 06/06/2025.
//

#include "Enemy.h"
#include "BasicEnemy.h"
#include "BossEnemy.h"
#include "../Managers/ConsoleManager.h"
#include "../Managers/StringExtensions.h"
#include "../TileTypes/WeaponTile.h"

bool Enemy::isDead() {
    return m_dead;
}

std::vector<std::string> Enemy::getLootTable() {
    return m_lootTable;
}

std::string Enemy::getSymbol() {
    return m_symbol;
}


std::string Enemy::getRandomLoot() {
    if (m_lootTable.size() <= 0) { return "none";}

    int randomIndex = Random::getRandomInt(0, m_lootTable.size() - 1);
    return m_lootTable[randomIndex];
}

Tile *Enemy::getRandomLootAsTile(Vector2 position) {
    std::string lootID = getRandomLoot();
    if (lootID == "none") { return nullptr; }

    std::vector<std::string> itemPath = StringExtensions::split(lootID, "/");

    try {
        std::string itemType = itemPath[0];
        if (itemType == "weapons") {
            std::string weaponType = itemPath[1];
            nlohmann::json itemList = JsonManager::weaponData[weaponType];

            std::string itemID = itemPath[2];
            nlohmann::json itemData;
            ConsoleManager::printLog("Searching for an item with the id \"" + itemID + "\"");
            for (auto item : itemList) {
                ConsoleManager::printLog(item["name"]);
                if (item.contains("weapon_id") && item["weapon_id"] == itemPath[2]) {
                    itemData = item;
                    ConsoleManager::printLog("Item found! Dropping loot now.");
                }
            }

            std::string weaponName = itemData["name"];
            Vector2 damageRange = {itemData["damage_range"][0], itemData["damage_range"][1]};
            return new WeaponTile(new Weapon(weaponName, damageRange), position);
        }
        else {
            throw;
        }
    }
    catch (...){
        ConsoleManager::printError("Loot with id \"" + lootID + "\" not found. Check Enemies.json for any mistakes.");
        return nullptr;
    }
}

std::vector<std::string> Enemy::getAbilityNames() {
    std::vector<std::string> abilities;
    try {

        for (auto ability : m_abilities) {
            abilities.push_back(ability->getName());
        }

    }
    catch (...) {
        ConsoleManager::printError("Could not read ability names");
    }
    return abilities;
}

Enemy* Enemy::getRandomEnemyOfType(const EnemyType type) {
    auto data = JsonManager::enemyData;

    switch (type) {
        case EnemyType::Basic: {

            const int selectedIndex = Random::getRandomInt(0, data["monster"].size() - 1);
            const auto selectedEnemy = data["monster"][selectedIndex];

            return new BasicEnemy(selectedEnemy);
        }
        case EnemyType::Boss: {
            const int selectedIndex = Random::getRandomInt(0, data["boss"].size() - 1);
            const auto selectedEnemy = data["boss"][selectedIndex];

            return new BossEnemy(selectedEnemy);
        }
        default:
            return nullptr;
    }
}

void Enemy::attack(PlayerState* playerState, std::vector<Enemy*> enemies) {
    playerState->damagePlayer(getAttack());
}

void Enemy::activateRandomAbility(PlayerState* playerState, std::vector<Enemy*> enemies) {
    ConsoleManager::printLog("Finding a random ability to cast...");
    try {
        if (m_abilities.size() <= 0) {
            ConsoleManager::printError("This enemy has no abilites to cast!");
            return;
        }
        int abilityIndex = Random::getRandomInt(0, m_abilities.size() - 1);
        m_abilities[abilityIndex]->activate(playerState, enemies);
    }
    catch (...) {
        ConsoleManager::printLog("Could not cast a random ability.");
    }
}


