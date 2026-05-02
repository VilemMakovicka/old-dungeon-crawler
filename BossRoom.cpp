//
// Created by alaf4 on 02.06.2025.
//

#include "BossRoom.h"

BossRoom::BossRoom(Vector2 positionOnMap, ForceGenerateState northDoor, ForceGenerateState southDoor, ForceGenerateState eastDoor, ForceGenerateState westDoor) :
Room(positionOnMap, northDoor, southDoor, eastDoor, westDoor) {
    ConsoleManager::printLog("Generating boss room...");
    try {
        gen_generateBoss();
        ConsoleManager::printLog("Generating complete.");
    }
    catch (...){
        ConsoleManager::printError("Could not generate contents of this boss room!");
    }
}

void BossRoom::gen_generateBoss() {
    setTileOnPosition(
        {4, 4},
        new EnemyTile({4, 4},
            Enemy::getRandomEnemyOfType(EnemyType::Boss)
        )
    );
}

