//
// Created by alaf4 on 11.05.2025.
//

#ifndef PLAYERSTATE_H
#define PLAYERSTATE_H

#include "Managers/Vector2.h"
#include "Weapon.h"

class PlayerState {
private:
    int m_maximumHealth;
    int m_health;
    Weapon* m_currentWeapon;
    Vector2 m_positionOnMap;
public:
    PlayerState();
    ~PlayerState();
    void damagePlayer(int damage);
    void heal(unsigned int amount);
    int GetHealth();
    std::string getHealthAsString();
    std::string getHealthVisualized();
    std::string getWeaponStatus();
    std::vector<std::string> getBoxView(int width, int height);
    Vector2 GetPositionOnMap();
    std::string getPositionOnMapAsString();
    void travel(Vector2 direction);
    std::string toString();
    void print();
    void setWeapon(Weapon* newWeapon);
    Weapon* getWeapon();
};


#endif //PLAYERSTATE_H
