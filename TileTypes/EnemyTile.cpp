//
// Created by tmpat on 11.05.2025.
//

#include "EnemyTile.h"

EnemyTile::EnemyTile(Vector2 position, Enemy* enemy) :
InteractableTile(JsonManager::allTiles["enemy"]["string"], JsonManager::toString(JsonManager::allTiles["enemy"]["interaction_description"]) + enemy->getName(), TileInteractionType::Fight, position){
    m_enemy = enemy;
}

EnemyTile::~EnemyTile() {
    //delete m_enemy;
}

Enemy *EnemyTile::getEnemy() {
    return m_enemy;
}

EnemyTile *EnemyTile::clone() const {
    return new EnemyTile(*this);
}