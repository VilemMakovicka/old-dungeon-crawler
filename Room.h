//
// Created by Vilém on 10/05/2025.
//

#ifndef ROOM_H
#define ROOM_H

#include "TileTypes/StaticTile.h"
#include "Managers/Vector2.h"
#include "TileTypes/Tile.h"
#include <iostream>
#include <vector>
#include "TileTypes/InteractableTile.h"
#include "TileTypes/DoorTile.h"
#include <math.h>
#include "Enums/ForceGenerateState.h"
#include <random>
#include <algorithm>
#include "Managers/Random.h"
#include <vector>
#include "TileTypes/WallTile.h"

class Room {
protected:
    static Vector2 s_roomSize;

    Vector2 m_positionOnMap;
    std::vector<std::vector<Tile*>> m_tiles;

    void generateRoom();
    void gen_generateBase();
    void gen_generateWalls();
    void gen_generateDoors();
    bool positionIsOnEdge(Vector2 position);
    ForceGenerateState m_forceNorthDoor;
    ForceGenerateState m_forceSouthDoor;
    ForceGenerateState m_forceEastDoor;
    ForceGenerateState m_forceWestDoor;
    bool m_northDoor;
    bool m_southDoor;
    bool m_eastDoor;
    bool m_westDoor;

    std::vector<Tile*> getAllEmptyTiles();
    std::vector<Tile*> getRandomEmptyTiles(unsigned int amount);
public:
    Room(Vector2 positionOnMap, ForceGenerateState northDoor, ForceGenerateState southDoor, ForceGenerateState eastDoor, ForceGenerateState westDoor);
    Room(Room& copy);
    virtual ~Room();

    Vector2 getPositionOnMap();
    std::string getTilesAsString();
    Tile* getTileOnPosition(Vector2 position);
    virtual std::string getMinimapSymbol();
    virtual ForegroundConsoleColor getMinimapForegroundColor();
    virtual BackgroundConsoleColor getMinimapBackgroundColor();
    std::vector<std::string> getBoxView();
    void print();
    void setTileOnPosition(Vector2 position, Tile *newTile);
    std::vector<InteractableTile*> getInteractableTiles();
    void dropDeadEnemyLoot();
    bool hasNorthDoor();
    bool hasSouthDoor();
    bool hasEastDoor();
    bool hasWestDoor();
};



#endif //ROOM_H
