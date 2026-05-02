//
// Created by alaf4 on 02.06.2025.
//

#include "BossRoom.h"

BossRoom::BossRoom(Vector2 positionOnMap, ForceGenerateState northDoor, ForceGenerateState southDoor, ForceGenerateState eastDoor, ForceGenerateState westDoor) :
Room(positionOnMap, northDoor, southDoor, eastDoor, westDoor) {
    std::clog << "Generating boss room..." << std::endl;
    try {
        gen_generateBoss();
    }
    catch (const char* msg){
        std::cerr << "Could generate this room." << std::endl;
        std::cerr << msg << std::endl;
    }
    std::clog << "Generating complete." << std::endl;
}

void BossRoom::gen_generateBoss() {
    // DODELAT

    Tile* BossTile = getRandomEmptyTiles(1)[0];
    setTileOnPosition(BossTile->getPosition(), new EnemyTile(BossTile->getPosition(), Enemy::getRandomEnemyOfType(EnemyType::BasicEnemy)));
}
