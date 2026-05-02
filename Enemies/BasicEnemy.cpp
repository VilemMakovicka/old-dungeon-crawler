//
// Created by Vilém on 06/06/2025.
//

#include "BasicEnemy.h"

#include "../Managers/Random.h"


BasicEnemy::BasicEnemy(std::string name, int health, int minimumDamage, int maximumDamage) : Enemy() {
    m_name = name;
    m_health = health;
    m_minimumDamage = minimumDamage;
    m_maximumDamage = maximumDamage;
}

BasicEnemy::~BasicEnemy() {

}

int BasicEnemy::getAttack() {
    return Random::getRandomInt(m_minimumDamage, m_maximumDamage);
}

int BasicEnemy::getHealth() {
    return m_health;
}

std::string BasicEnemy::getName() {
    return m_name;
}

void BasicEnemy::damage(int amount) {
    if (m_health - amount < 0) {
        m_health = 0;
        m_dead = true;
    }

    m_health -= amount;
}

