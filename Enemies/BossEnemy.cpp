//
// Created by Vilém on 06/06/2025.
//

#include "BossEnemy.h"

BossEnemy::BossEnemy() : Enemy() {

}

BossEnemy::~BossEnemy() {

}

int BossEnemy::getAttack() {
    return 0;
}

int BossEnemy::getHealth() {
    return 0;
}

std::string BossEnemy::getName() {
    return "";
}

void BossEnemy::damage(int amount) {

}
