//
// Created by Vilém on 06/06/2025.
//

#ifndef ENEMY_H
#define ENEMY_H

#include <iostream>

#include "../Enums/EnemyType.h"
#include "../Managers/JsonManager.h"
#include "../Managers/Random.h"


class Enemy {
protected:
    bool m_dead = false;
public:
    static Enemy* getRandomEnemyOfType(EnemyType type);
    virtual int getAttack() = 0;
    virtual int getHealth() = 0;
    bool isDead();
    virtual std::string getName() = 0;
    virtual void damage(int amount) = 0;
    ~Enemy() = default;
    Enemy() = default;
};



#endif //ENEMY_H
