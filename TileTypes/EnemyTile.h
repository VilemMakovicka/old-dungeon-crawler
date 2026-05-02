//
// Created by tmpat on 11.05.2025.
//

#ifndef ENEMYTILE_H
#define ENEMYTILE_H

#include "InteractableTile.h"
#include "Tile.h"
#include "../Enemies/Enemy.h"

class EnemyTile : public InteractableTile {
    Enemy* m_enemy;
public:
    EnemyTile(Vector2 position, Enemy* enemy);
    ~EnemyTile();
    Enemy* getEnemy();
    EnemyTile *clone() const override;
};



#endif //ENEMYTILE_H

