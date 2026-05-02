//
// Created by Vilém on 10/05/2025.
//

#include "Room.h"

#include "Managers/ConsoleManager.h"
#include "Managers/StringExtensions.h"
#include "TileTypes/EmptyTile.h"
#include "TileTypes/EnemyTile.h"


Room::Room(Vector2 positionOnMap, ForceGenerateState northDoor, ForceGenerateState southDoor, ForceGenerateState eastDoor, ForceGenerateState westDoor) {
    m_northDoor = false;
    m_eastDoor = false;
    m_westDoor = false;
    m_southDoor = false;

    m_forceNorthDoor = northDoor;
    m_forceSouthDoor = southDoor;
    m_forceEastDoor = eastDoor;
    m_forceWestDoor = westDoor;

    m_positionOnMap = positionOnMap;
    generateRoom();
}

std::string Room::getMinimapSymbol() {
    return JsonManager::UIElements["minimap"]["elements"]["discovered_room_unknown"];
}

BackgroundConsoleColor Room::getMinimapBackgroundColor() {
    return BackgroundConsoleColor::Default;
}

ForegroundConsoleColor Room::getMinimapForegroundColor() {
    return ForegroundConsoleColor::Default;
}

Room::Room(Room& copy) {

    m_positionOnMap = copy.m_positionOnMap;
    m_northDoor = copy.m_northDoor;
    m_eastDoor = copy.m_eastDoor;
    m_westDoor = copy.m_westDoor;
    m_southDoor = copy.m_southDoor;

    m_forceNorthDoor = copy.m_forceNorthDoor;
    m_forceSouthDoor = copy.m_forceSouthDoor;
    m_forceEastDoor = copy.m_forceEastDoor;
    m_forceWestDoor = copy.m_forceWestDoor;

    for (std::vector<Tile*> row : copy.m_tiles) {
        std::vector<Tile*> copiedRow;

        for (Tile* tile : row) {
            copiedRow.push_back(tile->clone()); // Deep copy
        }

        m_tiles.push_back(copiedRow);
    }
    //std::clog << "Copying room " << m_positionOnMap.toString() << "..." << std::endl;
}

void Room::dropDeadEnemyLoot() {
    for (InteractableTile* tile : getInteractableTiles()) {
        if (auto* enemyTile = dynamic_cast<EnemyTile*>(tile)) {
            if (enemyTile->getEnemy()->isDead()) {
                if (Tile* newTile = enemyTile->getEnemy()->getRandomLootAsTile(enemyTile->getPosition()))
                    setTileOnPosition(enemyTile->getPosition(), newTile);
                else
                    setTileOnPosition(enemyTile->getPosition(), new EmptyTile(enemyTile->getPosition()));
            }
        };
    }
}


void Room::generateRoom() {
    ConsoleManager::printLog("Generating room base...");
    try {
        gen_generateBase();
        gen_generateWalls();
        gen_generateDoors();
    }
    catch (...){
        ConsoleManager::printError("Could generate this room.");
    }
    ConsoleManager::printLog("Generating complete.");
}

void Room::gen_generateBase() {
    for (int row = 0; row < s_roomSize.y; row++) {
        std::vector<Tile*> tileRow(s_roomSize.x, nullptr);
        m_tiles.push_back(tileRow);
    }

    for (int row = 0; row < m_tiles.size(); row++) {
        for (int col = 0; col < m_tiles[0].size(); col++) {
            Vector2 position = {col, row};
            setTileOnPosition(position, new EmptyTile(position));
        }
    }
}

void Room::gen_generateWalls() {
    for (int row = 0; row < m_tiles.size(); row++) {
        for (int col = 0; col < m_tiles[0].size(); col++) {
            Vector2 position = {col, row};
            if (positionIsOnEdge(position)) {
                setTileOnPosition(position, new WallTile(position));
            }
        }
    }
}

bool Room::positionIsOnEdge(Vector2 position) {
    return (position.x == 0 || position.y == 0 || position.x == s_roomSize.x - 1 || position.y == s_roomSize.y - 1);
}

Room::~Room() {
    for (std::vector<Tile *> tileRow : m_tiles) {
        for (Tile* tile : tileRow) {
            delete tile;
        }
    }
}

void Room::print() {
    std::vector<std::string> lines;

    for (std::vector<Tile*> tileRow : m_tiles) {
        std::string rowString;
        for (Tile* tile : tileRow) {
            rowString += tile->getSymbol();
        }
        lines.push_back(StringExtensions::centerString(rowString, 20));
    }

    ConsoleManager::printBoxView(lines, "Map", 22, ConsoleColor::getForegroundConsoleColor(JsonManager::UIElements["color_themes"]["map"]["frame"]));
}

std::vector<std::string> Room::getBoxView() {
    std::vector<std::string> lines;

    for (std::vector<Tile*> tileRow : m_tiles) {
        std::string rowString;
        for (Tile* tile : tileRow) {
            rowString += tile->getSymbol();
        }
        lines.push_back(StringExtensions::centerString(rowString, 20));
    }

    return StringExtensions::createCutoffBoxView(
        lines,
        "Map",
        22,
        11,
        ConsoleColor::getForegroundConsoleColor(JsonManager::UIElements["color_themes"]["map"]["frame"]),
        ConsoleColor::getForegroundConsoleColor(JsonManager::UIElements["color_themes"]["map"]["headings"])
        );
}


Tile *Room::getTileOnPosition(Vector2 position) {
    if (position.x < 0 || position.y < 0 || position.x >= s_roomSize.x - 1 || position.y >= s_roomSize.y - 1) {
        ConsoleManager::printError("Tried to access tiles out of room's bounds!");
        return nullptr;
    }
    return m_tiles[position.y][position.x];
}

std::string Room::getTilesAsString() {
    std::string finalString;

    for (std::vector<Tile*> tileRow : m_tiles) {
        std::string rowString;
        for (Tile* tile : tileRow) {
            rowString += tile->getSymbol();
        }
        rowString = StringExtensions::centerString(rowString, 37);
        finalString += rowString + "\n";
    }

    return finalString;
}


Vector2 Room::getPositionOnMap() {
    return m_positionOnMap;
}

void Room::setTileOnPosition(Vector2 position, Tile *newTile) {
    delete m_tiles[position.y][position.x];
    m_tiles[position.y][position.x] = newTile;
}
std::vector<InteractableTile *> Room::getInteractableTiles() {
    std::vector<InteractableTile *> interactableTiles;

    for (std::vector<Tile*> tileRow : m_tiles) {
        for (Tile* tile : tileRow) {
            if (auto* interactable = dynamic_cast<InteractableTile*>(tile)) {
                interactableTiles.push_back(interactable);
            }
        }
    }

    return interactableTiles;
}
Vector2 Room::s_roomSize = Vector2(9, 9);

void Room::gen_generateDoors() {
    int doorTokens = Random::getRandomInt(2, 4);

    std::vector<bool*> bools = {&m_northDoor, &m_southDoor, &m_eastDoor, &m_westDoor};

    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(bools.begin(), bools.end(), g);

    for (int i = 0; i < doorTokens; i++) {
        *bools[i] = true;
    }

    if (m_forceNorthDoor == ForceGenerateState::ForceGenerate) { m_northDoor = true; }
    if (m_forceNorthDoor == ForceGenerateState::ForceRemove) { m_northDoor = false; }
    if (m_forceSouthDoor == ForceGenerateState::ForceGenerate) { m_southDoor = true; }
    if (m_forceSouthDoor == ForceGenerateState::ForceRemove) { m_southDoor = false; }
    if (m_forceEastDoor == ForceGenerateState::ForceGenerate) { m_eastDoor = true; }
    if (m_forceEastDoor == ForceGenerateState::ForceRemove) { m_eastDoor = false; }
    if (m_forceWestDoor == ForceGenerateState::ForceGenerate) { m_westDoor = true; }
    if (m_forceWestDoor == ForceGenerateState::ForceRemove) { m_westDoor = false; }

    if (m_northDoor) {
        Vector2 POSITION_DOOR_NORTH = Vector2(floor(s_roomSize.x/2), 0);
        setTileOnPosition(POSITION_DOOR_NORTH, new DoorTile("DN", JsonManager::allTiles["door"]["interaction_description"][0], Vector2::up, POSITION_DOOR_NORTH));
    }
    if (m_westDoor) {
        Vector2 POSITION_DOOR_WEST = Vector2(0, floor(s_roomSize.y/2));
        setTileOnPosition(POSITION_DOOR_WEST, new DoorTile("DW", JsonManager::allTiles["door"]["interaction_description"][1], Vector2::left, POSITION_DOOR_WEST));
    }
    if (m_eastDoor) {
        Vector2 POSITION_DOOR_EAST = Vector2(s_roomSize.x - 1, floor(s_roomSize.y/2));
        setTileOnPosition(POSITION_DOOR_EAST, new DoorTile("DE", JsonManager::allTiles["door"]["interaction_description"][2], Vector2::right, POSITION_DOOR_EAST));
    }
    if (m_southDoor) {
        Vector2 POSITION_DOOR_SOUTH = Vector2(floor(s_roomSize.x/2), s_roomSize.y - 1);
        setTileOnPosition(POSITION_DOOR_SOUTH, new DoorTile("DS", JsonManager::allTiles["door"]["interaction_description"][3], Vector2::down, POSITION_DOOR_SOUTH));
    }
}

bool Room::hasNorthDoor() {
    return m_northDoor;
}

bool Room::hasEastDoor() {
    return m_eastDoor;
}

bool Room::hasSouthDoor() {
    return m_southDoor;
}

bool Room::hasWestDoor() {
    return m_westDoor;
}

std::vector<Tile *> Room::getAllEmptyTiles() {
    std::vector<Tile *> emptyTiles;

    for (std::vector<Tile*> tileRow : m_tiles) {
        for (Tile* tile : tileRow) {
            if (dynamic_cast<EmptyTile*>(tile)) { emptyTiles.push_back(tile); }
        }
    }

    return emptyTiles;
}

std::vector<Tile *> Room::getRandomEmptyTiles(unsigned int amount) {
    std::vector<Tile *> allEmptyTiles = getAllEmptyTiles();

    if (allEmptyTiles.size() <= amount) return allEmptyTiles;

    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(allEmptyTiles.begin(), allEmptyTiles.end(), g);

    std::vector<Tile *> chosenEmptyTiles;

    for (int i = 0; i < amount; i++) {
        chosenEmptyTiles.push_back(allEmptyTiles[i]);
    }

    return chosenEmptyTiles;
}
