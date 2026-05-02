//
// Created by adaze on 12.05.2025.
//

#ifndef DUNGEONROOM_H
#define DUNGEONROOM_H
#include "Room.h"
#include "TileTypes/EnemyTile.h"
#include "TileTypes/WeaponTile.h"


class DungeonRoom : public Room {
    private:
    void generateRoom();
    void gen_generateWeapons();
    void gen_generateEnemies();
    public:
    DungeonRoom(Vector2 positionOnMap, ForceGenerateState northDoor, ForceGenerateState southDoor, ForceGenerateState eastDoor, ForceGenerateState westDoor);
    std::string getMinimapSymbol() override;
    ForegroundConsoleColor getMinimapForegroundColor() override;
    BackgroundConsoleColor getMinimapBackgroundColor() override;
};



#endif //DUNGEONROOM_H
