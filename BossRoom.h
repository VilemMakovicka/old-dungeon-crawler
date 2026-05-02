//
// Created by alaf4 on 02.06.2025.
//

#ifndef BOSSROOM_H
#define BOSSROOM_H

#include "Room.h"
#include "TileTypes/EnemyTile.h"

class BossRoom : public Room {
private:
    void generateRoom();
    void gen_generateBoss();
public:
    BossRoom(Vector2 positionOnMap, ForceGenerateState northDoor, ForceGenerateState southDoor, ForceGenerateState eastDoor, ForceGenerateState westDoor);
};




#endif //BOSSROOM_H
