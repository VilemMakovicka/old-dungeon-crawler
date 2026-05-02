//
// Created by Vilém on 06/06/2025.
//

#ifndef BASICENEMY_H
#define BASICENEMY_H
#include "Enemy.h"


class BasicEnemy : public Enemy{
private:
    std::string m_name;
    int m_health;
    float m_minimumDamage, m_maximumDamage;
public:
    BasicEnemy(std::string name, int health, int minimumDamage, int maximumDamage);
    ~BasicEnemy();
    int getAttack() override;
    int getHealth() override;
    std::string getName() override;
    void damage(int amount) override;
};



#endif //BASICENEMY_H
