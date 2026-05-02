//
// Created by Vilém on 10/06/2025.
//

#ifndef ABILITY_PLAYERHEAL_H
#define ABILITY_PLAYERHEAL_H
#include "EnemyAbility.h"

class Ability_PlayerHeal : public EnemyAbility{
protected:
    int m_chanceToActivate;
    int m_amount;
public:
    Ability_PlayerHeal(std::string name, int chanceToActivate, int amount);
    void activate(PlayerState* playerState, std::vector<Enemy*> enemies) override;
};


#endif //ABILITY_PLAYERHEAL_H
