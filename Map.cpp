//
// Created by adaze on 10.05.2025.
//

#include "Map.h"

#include "BossRoom.h"
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

    int roll = Random::getRandomInt(0, 100);

    Vector2 DungeonChanceRange = {0, 50};
    Vector2 HallChanceRange = {51, 90};
    Vector2 BossChanceRange = {91, 100};


    if (roll >= DungeonChanceRange.x && roll <= DungeonChanceRange.y)
        newRoom = new DungeonRoom(position, forceNorthDoor, forceSouthDoor, forceEastDoor, forceWestDoor);
    else if(roll >= HallChanceRange.x && roll <= HallChanceRange.y)
        newRoom = new HallRoom(position, forceNorthDoor, forceSouthDoor, forceEastDoor, forceWestDoor);
    else if(roll >= BossChanceRange.x && roll <= BossChanceRange.y)
        newRoom = new BossRoom(position, forceNorthDoor, forceSouthDoor, forceEastDoor, forceWestDoor);

    std::clog << "Picked room type." << std::endl;
    m_rooms.push_back(newRoom);
    return newRoom;
}

/**
 * Pokud byla místnost na zvolených souřadnicích již vygenerována, vrátí místnost.
 * Pokud místnost ještě vygenerovaná nebyla, vygeneruje na souřadnicích novou mísnost a vrátí ji.
 * @param coordinates Souřadnice místnosti na mapě.
 * @return Pointer nalezené místnosti (Vždy vrátí Room*).
 */
Room* Map::getRoom(Vector2 coordinates) {
    for (Room* room : m_rooms) {
        if (room->getPositionOnMap() == coordinates) {
            return room;
        };
    }

    return generateRoomOnPosition(coordinates);
}

/**
 * Pokud byla místnost na zvolených souřadnicích již vygenerována, vrátí místnost.
 * Pokud místnost ještě vygenerovaná nebyla, vrátí nullptr.
 * @param coordinates Souřadnice místnosti na mapě.
 * @return Pointer nalezené místnosti (Může vrátit nullptr).
 */
Room* Map::roomExists(Vector2 coordinates) {
    for (Room* room : m_rooms) {
        if (room->getPositionOnMap() == coordinates) {
            return room;
        };
    }

    return nullptr;
}

/**
 * Vygeneruje Minimapu a vrátí ji v podobě std::vector<std::string>
 * @param playerCoordinates Poloha hráče (Jsou to souřadnice místnosti která bude uprostřed minimapy.)
 * @param width Šířka minimapy (Včetně rámečku)
 * @param height Výška minimapy (Včetně rámečku)
 * @return std::vector<std::string> ve formě boxview
 */
std::vector<std::string> Map::getBoxView(Vector2 playerCoordinates, int width, int height) {
    //Barvy elementů
    ForegroundConsoleColor frameColor = ConsoleColor::getForegroundConsoleColor(JsonManager::UIElements["minimap"]["color_theme"]["frame"]);
    ForegroundConsoleColor titleColor = ConsoleColor::getForegroundConsoleColor(JsonManager::UIElements["minimap"]["color_theme"]["headings"]);
    ForegroundConsoleColor currentRoomColor = ConsoleColor::getForegroundConsoleColor(JsonManager::UIElements["minimap"]["color_theme"]["current_room"]);
    ForegroundConsoleColor undiscoveredRoomColor = ConsoleColor::getForegroundConsoleColor(JsonManager::UIElements["minimap"]["color_theme"]["undiscovered_room"]);

    //

    nlohmann::json UIElements = JsonManager::UIElements["minimap"]["elements"];

    //

    Vector2 interiorSize = {width - 2, height - 2};
    //V: Zatím netuším proč je interiorsize/2 offsetlej o dva doprava takže zatím prostě odečítám manuálně 2
    Vector2 centerPoint = {interiorSize.x / 2 - 2, interiorSize.y / 2 + interiorSize.y % 2};


    Vector2 topLeftCoords = playerCoordinates - centerPoint - Vector2::one;
    Vector2 bottomRightCoords = playerCoordinates + interiorSize - centerPoint;

    std::vector<std::string> output;
    std::vector<std::vector<std::string>> roomTable;

    for (int y = bottomRightCoords.y; y > topLeftCoords.y; y--) {
        std::vector<std::string> roomRow;
        for (int x = topLeftCoords.x; x < bottomRightCoords.x; x++) {
            if (auto* room = roomExists({x, y})) {
                std::string roomSymbol = room->getMinimapSymbol();
                ForegroundConsoleColor foregroundRoomColor = room->getMinimapForegroundColor();
                BackgroundConsoleColor backgroundRoomColor = room->getMinimapBackgroundColor();

                if (room->getPositionOnMap() == playerCoordinates)
                    foregroundRoomColor = currentRoomColor;

                roomSymbol = StringExtensions::colorizeString(roomSymbol, foregroundRoomColor, backgroundRoomColor);

                roomRow.push_back(roomSymbol);
            }
            else{
                std::string roomSymbol = " ";

                if (auto* room = roomExists({x, y + 1})) {
                    if (room->hasSouthDoor()) {
                        roomSymbol = StringExtensions::colorizeString(UIElements["undiscovered_room"], undiscoveredRoomColor);
                    }
                }
                if (auto* room = roomExists({x, y - 1})) {
                    if (room->hasNorthDoor()) {
                        roomSymbol = StringExtensions::colorizeString(UIElements["undiscovered_room"], undiscoveredRoomColor);
                    }
                }
                if (auto* room = roomExists({x + 1, y})) {
                    if (room->hasWestDoor()) {
                        roomSymbol = StringExtensions::colorizeString(UIElements["undiscovered_room"], undiscoveredRoomColor);
                    }
                }
                if (auto* room = roomExists({x - 1, y})) {
                    if (room->hasEastDoor()) {
                        roomSymbol = StringExtensions::colorizeString(UIElements["undiscovered_room"], undiscoveredRoomColor);
                    }
                }

                roomRow.push_back(roomSymbol);
            }
        }
        roomTable.push_back(roomRow);
    }

    for (auto row : roomTable) {
        std::string line;
        for (auto symbol : row) {
            line += symbol;
        }
        output.push_back(StringExtensions::alignStringLeft(line, interiorSize.x));
    }
    return StringExtensions::createCutoffBoxView(output, "Minimap [" + playerCoordinates.toString() +"]", width, height, frameColor, titleColor);
}
