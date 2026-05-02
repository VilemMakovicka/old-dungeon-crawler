//
// Created by Vilém on 06/06/2025.
//

#ifndef BASICENEMY_H
#define BASICENEMY_H
#include "Enemy.h"
#include "../GameInstance.h"
#include "../Managers/ConsoleManager.h"
#include "../Managers/Random.h"


class BasicEnemy : public Enemy{
private:
    std::string m_name;
    std::string m_symbol;
    int m_health;
    float m_minimumDamage, m_maximumDamage;
public:
    BasicEnemy(nlohmann::json attributes);
    ~BasicEnemy();
    int getAttack() override;
    int getHealth() override;
    std::string getSymbol() override;
    std::string getName() override;
    void damage(int amount) override;
};



#endif //BASICENEMY_H
