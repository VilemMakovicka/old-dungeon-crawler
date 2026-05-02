//
// Created by Vilém on 06/06/2025.
//

#include "Enemy.h"
#include "BasicEnemy.h"
#include "BossEnemy.h"

bool Enemy::isDead() {
    return m_dead;
}


Enemy* Enemy::getRandomEnemyOfType(const EnemyType type) {

    switch (type) {
        case EnemyType::BasicEnemy: {
            auto data = JsonManager::getJsonData("../JSON/Enemies.json");

            int selectedIndex = Random::getRandomInt(0, data["monster"].size() - 1);
            auto selectedEnemy = data["monster"][selectedIndex];

            return new BasicEnemy(
                JsonManager::toString(selectedEnemy["name"]),
                selectedEnemy["health"],
                selectedEnemy["damage_range"][0],
                selectedEnemy["damage_range"][1]
            );
            break;
        }
        case EnemyType::BossEnemy:
            return nullptr;
            break;
        default:
            return nullptr;
            break;
    }

    return nullptr;
}
