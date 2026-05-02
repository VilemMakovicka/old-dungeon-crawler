//
// Created by Vilém on 06/06/2025.
//

#ifndef ENEMY_H
#define ENEMY_H

#include <iostream>

#include "../Enums/EnemyType.h"
#include "../Managers/JsonManager.h"
#include "../Managers/Random.h"
#include "../TileTypes/Tile.h"
#include "../Weapon.h"
#include "../EnemyAbilities/EnemyAbility.h"


class Enemy {
protected:
    bool m_dead = false;
    std::vector<std::string> m_lootTable;
    std::string m_symbol;
    std::vector<EnemyAbility*> m_abilities;
public:
    static Enemy* getRandomEnemyOfType(EnemyType type);
    virtual int getAttack() = 0;
    virtual int getHealth() = 0;
    virtual std::string getName() = 0;
    std::vector<std::string> getLootTable();
    std::string getRandomLoot();
    virtual std::string getSymbol();
    Tile* getRandomLootAsTile(Vector2 position);
    bool isDead();
    virtual void damage(int amount) = 0;
    void attack(PlayerState* playerState, std::vector<Enemy*> enemies);
    std::vector<std::string> getAbilityNames();
    void activateRandomAbility(PlayerState* playerState, std::vector<Enemy*> enemies);
    ~Enemy() = default;
    Enemy() = default;
};



#endif //ENEMY_H
