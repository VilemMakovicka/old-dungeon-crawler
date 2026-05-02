//
// Created by tmpat on 11.05.2025.
//

#include "EnemyTile.h"

EnemyTile::EnemyTile(Vector2 position, Enemy* enemy) :
InteractableTile(
    enemy->getSymbol(),
    JsonManager::toString(JsonManager::allTiles["enemy"]["interaction_description"]) + enemy->getName(),
    TileInteractionType::Fight,
    position,
    ConsoleColor::getForegroundConsoleColor(JsonManager::allTiles["enemy"]["color_foreground"]),
    ConsoleColor::getBackgroundConsoleColor(JsonManager::allTiles["enemy"]["color_background"])
    ){
    m_enemy = enemy;
    ConsoleManager::printLog("Symbol: "+enemy->getSymbol());
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