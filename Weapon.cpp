//
// Created by adaze on 09.05.2025.
//

#include "Weapon.h"


float Weapon::getDamage() {
    return m_damage;
}

std::string Weapon::getName() {
    return m_name;
}

std::string Weapon::toString() {
    return m_name + " ( " + StringExtensions::truncateFloat(m_damage, 0) + "DMG )";
}

Weapon::Weapon(std::string name, float damage) {
    m_name = name;
    m_damage = damage;
}

Weapon *Weapon::getRandomWeaponByType(std::string type) {
    auto data = JsonManager::weaponData;

    int chosenIndex = Random::getRandomInt(0, data[type].size() - 1);
    auto chosenWeapon = data[type][chosenIndex];

    int damageMinimum = chosenWeapon["damage_range"][0];
    int damageMaximum = chosenWeapon["damage_range"][1];
    std::string chosenName = chosenWeapon["name"];
    int chosenDamage = Random::getRandomInt(damageMinimum, damageMaximum);

    return new Weapon(chosenName, chosenDamage);
}
