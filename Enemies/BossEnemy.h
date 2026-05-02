//
// Created by Vilém on 06/06/2025.
//

#ifndef BOSSENEMY_H
#define BOSSENEMY_H
#include "Enemy.h"


class BossEnemy : public Enemy{
private:
public:
    BossEnemy();
    ~BossEnemy();
    int getAttack() override;
    int getHealth() override;
    std::string getName() override;
    void damage(int amount) override;
};



#endif //BOSSENEMY_H
