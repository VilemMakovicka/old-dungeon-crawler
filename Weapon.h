//
// Created by adaze on 09.05.2025.
//

#ifndef WEAPON_H
#define WEAPON_H

#include <iostream>
#include <bits/chrono.h>
#include <cmath>
#include "Managers/StringExtensions.h"
#include "Managers/JsonManager.h"
#include "Managers/Random.h"

class Weapon {
private:
    std::string m_name;
    float m_damage;
public:
    Weapon(std::string name, float damage);
    float getDamage();
    std::string getName();
    std::string toString();
    static Weapon* getRandomWeaponByType(std::string type);
};



#endif //WEAPON_H
