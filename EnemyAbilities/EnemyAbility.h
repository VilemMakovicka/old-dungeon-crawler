//
// Created by Vilém on 10/06/2025.
//

#ifndef ENEMYABILITY_H
#define ENEMYABILITY_H

#include <iostream>
#include <nlohmann/json.hpp>
#include "../Managers/ConsoleManager.h"
#include "../Managers/Vector2.h"
#include "../Managers/Random.h"

#include "../PlayerState.h"

class Enemy;

class EnemyAbility {
protected:
    std::string m_name;
public:
    EnemyAbility(std::string name);

    virtual ~EnemyAbility() = default;
    virtual void activate(PlayerState* playerState, std::vector<Enemy*> enemies) = 0;
    static EnemyAbility* getEnemyAbility(nlohmann::json data);
    std::string getName();
};



#endif //ENEMYABILITY_H
