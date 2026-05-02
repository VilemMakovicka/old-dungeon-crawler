//
// Created by Vilém on 11/06/2025.
//

#ifndef ABILITY_INSTANTCASTERDAMAGE_H
#define ABILITY_INSTANTCASTERDAMAGE_H
#include "EnemyAbility.h"


class Ability_InstantCasterDamage : EnemyAbility{
protected:
    int m_chanceToActivate;
    Vector2 m_damageRange;
public:
    Ability_InstantCasterDamage(std::string name, int chanceToActivate, Vector2 damageRange);
    void activate(PlayerState* playerState, std::vector<Enemy*> enemies) override;
};



#endif //ABILITY_INSTANTCASTERDAMAGE_H
