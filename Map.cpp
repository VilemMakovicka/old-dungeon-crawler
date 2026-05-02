//
// Created by adaze on 10.05.2025.
//

#include "Map.h"

#include "Managers/ConsoleManager.h"

Map::Map() {
    Room* starterRoom = new Room({0, 0}, ForceGenerateState::ForceGenerate, ForceGenerateState::ForceGenerate, ForceGenerateState::ForceGenerate, ForceGenerateState::ForceGenerate);
    starterRoom->setTileOnPosition({2, 2}, WeaponTile::getBasicSwordTile({2, 2}));
    m_rooms.push_back(starterRoom);
}

Map::Map(Map& copy) {
    for (Room* room : copy.m_rooms) {
        m_rooms.push_back(new Room(*room));
    }
    //std::clog << "Copying map " << "[ Number of explored rooms: " << std::to_string(m_rooms.size()) << " ]..." << std::endl;
}

Map::~Map() {
    ConsoleManager::printLog("Unloading " + std::to_string(m_rooms.size()) + (m_rooms.size() == 1 ? " Room." : " Rooms."));
    for (Room* room : m_rooms) {
        delete room;
    }
}

Room* Map::generateRoomOnPosition(Vector2 position) {
    //std::clog << "Generating room..." << std::endl;

    ForceGenerateState forceNorthDoor = ForceGenerateState::None;
    ForceGenerateState forceSouthDoor = ForceGenerateState::None;
    ForceGenerateState forceEastDoor = ForceGenerateState::None;
    ForceGenerateState forceWestDoor = ForceGenerateState::None;

    for (Room* room : m_rooms) {
        if (room->getPositionOnMap() == position + Vector2::up) {
            forceNorthDoor = room->hasSouthDoor() ? ForceGenerateState::ForceGenerate : ForceGenerateState::ForceRemove;
        }
        if (room->getPositionOnMap() == position + Vector2::right) {
            forceEastDoor = room->hasWestDoor() ? ForceGenerateState::ForceGenerate : ForceGenerateState::ForceRemove;
        }
        if (room->getPositionOnMap() == position + Vector2::left) {
            forceWestDoor = room->hasEastDoor() ? ForceGenerateState::ForceGenerate : ForceGenerateState::ForceRemove;
        }
        if (room->getPositionOnMap() == position + Vector2::down) {
            forceSouthDoor = room->hasNorthDoor() ? ForceGenerateState::ForceGenerate : ForceGenerateState::ForceRemove;
        }
    }

    Room* newRoom = nullptr;

    std::clog << "Picking room type..." << std::endl;

    if (Random::getRandomBool(50)) {
        newRoom = new DungeonRoom(position, forceNorthDoor, forceSouthDoor, forceEastDoor, forceWestDoor);
    }
    else {
        newRoom = new HallRoom(position, forceNorthDoor, forceSouthDoor, forceEastDoor, forceWestDoor);
    }

    std::clog << "Picked room type." << std::endl;
    m_rooms.push_back(newRoom);
    return newRoom;
}


Room* Map::getRoom(Vector2 roomPosition) {
    for (Room* room : m_rooms) {
        if (room->getPositionOnMap() == roomPosition) {
            return room;
        };
    }

    return generateRoomOnPosition(roomPosition);
}