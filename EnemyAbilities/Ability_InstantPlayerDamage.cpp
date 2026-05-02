//
// Created by Vilém on 10/06/2025.
//

#include "Ability_InstantPlayerDamage.h"

void Ability_InstantPlayerDamage::activate(PlayerState* playerState, std::vector<Enemy*> enemies) {
    if (Random::getRandomBool(m_chanceToActivate)) {
        playerState->damagePlayer(Random::getRandomInt(m_damageRange.x, m_damageRange.y));
    }
}

Ability_InstantPlayerDamage::Ability_InstantPlayerDamage(std::string name, int chanceToActivate, Vector2 damageRange) :
EnemyAbility(name){
    m_chanceToActivate = chanceToActivate;
    m_damageRange = damageRange;
}

