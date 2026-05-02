//
// Created by adaze on 10.05.2025.
//

#ifndef MAP_H
#define MAP_H
#include "Managers/Vector2.h"
#include "Room.h"
#include "DungeonRoom.h"
#include "HallRoom.h"

class Map {
private:
    std::vector<Room*> m_rooms;
    Room* generateRoomOnPosition(Vector2 position);
public:
    Map();
    Map(Map& copy);
    ~Map();
    Room* getRoom(Vector2 roomPosition);
};



#endif //MAP_H
