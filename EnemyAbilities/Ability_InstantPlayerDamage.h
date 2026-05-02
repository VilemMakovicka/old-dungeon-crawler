//
// Created by Vilém on 10/06/2025.
//

#ifndef ABILITY_INSTANTPLAYERDAMAGE_H
#define ABILITY_INSTANTPLAYERDAMAGE_H
#include "EnemyAbility.h"


class Ability_InstantPlayerDamage : public EnemyAbility{
protected:
    int m_chanceToActivate;
    Vector2 m_damageRange;
public:
    Ability_InstantPlayerDamage(std::string name, int chanceToActivate, Vector2 damageRange);
    void activate(PlayerState* playerState, std::vector<Enemy*> enemies) override;
};



#endif //ABILITY_INSTANTPLAYERDAMAGE_H
