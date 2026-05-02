//
// Created by Vilém on 11/06/2025.
//

#include "Ability_InstantCasterDamage.h"

#include "../Enemies/Enemy.h"

void Ability_InstantCasterDamage::activate(PlayerState* playerState, std::vector<Enemy*> enemies) {
    /*
     *  Nedopsáno!!!!!!!!!!!!
     *
     */
}

Ability_InstantCasterDamage::Ability_InstantCasterDamage(std::string name, int chanceToActivate, Vector2 damageRange) :
EnemyAbility(name){
    m_chanceToActivate = chanceToActivate;
    m_damageRange = damageRange;
}
