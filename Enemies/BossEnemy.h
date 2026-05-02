//
// Created by Vilém on 06/06/2025.
//

#ifndef BOSSENEMY_H
#define BOSSENEMY_H
#include "Enemy.h"
#include "../GameInstance.h"
#include "../Managers/ConsoleManager.h"
#include "../Managers/Random.h"


class BossEnemy : public Enemy{
private:
    std::string m_name;
    std::string m_symbol;
    int m_health;
    float m_minimumDamage, m_maximumDamage;
public:
    BossEnemy(nlohmann::json attributes);
    ~BossEnemy();
    int getAttack() override;
    int getHealth() override;
    std::string getSymbol() override;
    std::string getName() override;
    void damage(int amount) override;
};



#endif //BOSSENEMY_H
