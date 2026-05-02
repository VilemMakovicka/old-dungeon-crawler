//
// Created by alaf4 on 12.05.2025.
//

#include "HallRoom.h"

#include "Managers/ConsoleManager.h"
#include "TileTypes/StaticTile.h"

HallRoom::HallRoom(Vector2 positionOnMap, ForceGenerateState northDoor, ForceGenerateState southDoor, ForceGenerateState eastDoor, ForceGenerateState westDoor) :
Room(positionOnMap, northDoor, southDoor, eastDoor, westDoor) {
    gen_generateWalls();
}

void HallRoom::gen_generateWalls() {
    std::vector<std::vector<bool>> wallPlacements;

    for (int row = 0; row < s_roomSize.y; row++) {
        wallPlacements.push_back(std::vector<bool>(s_roomSize.x, true));
    }

    wallPlacements[floor(s_roomSize.x/2)][floor(s_roomSize.y/2)] = false;

    if (m_northDoor == true) {
        for (int i = 0; i < floor(s_roomSize.y/2); i++) {
            wallPlacements[floor(s_roomSize.x/2)][i] = false;
        }
    }
    if (m_eastDoor == true) {
        for (int i = s_roomSize.x - 1; i > floor(s_roomSize.x/2); i--) {
            wallPlacements[i][floor(s_roomSize.y/2)] = false;
        }
    }
    if (m_westDoor == true) {
        for (int i = 0; i < floor(s_roomSize.x/2); i++) {
            wallPlacements[i][floor(s_roomSize.y/2)] = false;
        }
    }
    if (m_southDoor == true) {
        for (int i = s_roomSize.y - 1; i > floor(s_roomSize.y/2); i--) {
            wallPlacements[floor(s_roomSize.x/2)][i] = false;
        }
    }

    for (int row = 0; row < s_roomSize.y; row++) {
        for (int col = 0; col < s_roomSize.x; col++) {
            Vector2 position = {col, row};
            if (wallPlacements[col][row] == true && !positionIsOnEdge(position)) {
                setTileOnPosition(position, new WallTile(position));
            }
        }
    }
}

std::string HallRoom::getMinimapSymbol() {
    try {
        nlohmann::json UIElements = JsonManager::UIElements["minimap"]["elements"]["hall_room"];

        bool N = hasNorthDoor();
        bool S = hasSouthDoor();
        bool E = hasEastDoor();
        bool W = hasWestDoor();

        if (N && S && !E && !W) return UIElements["NS"];
        if (!N && !S && E && W) return UIElements["EW"];

        if (!N && S && E && !W) return UIElements["SE"];
        if (!N && S && !E && W) return UIElements["SW"];
        if (N && !S && E && !W) return UIElements["NE"];
        if (N && !S && !E && W) return UIElements["NW"];

        if (N && !S && E && W) return UIElements["NEW"];
        if (N && S && !E && W) return UIElements["NSW"];
        if (!N && S && E && W) return UIElements["SEW"];
        if (N && S && E && !W) return UIElements["NSE"];

        if (N && S && E && W) return UIElements["NSEW"];

        return UIElements["discovered_room_error"];
    }
    catch (...) {
        ConsoleManager::printError("Could not find the correct symbol for 'hall_room'");
        return "!";
    }
}

BackgroundConsoleColor HallRoom::getMinimapBackgroundColor() {
    std::string colorString = JsonManager::UIElements["minimap"]["color_theme"]["hall_room_background"];
    return ConsoleColor::getBackgroundConsoleColor(colorString);
}

ForegroundConsoleColor HallRoom::getMinimapForegroundColor() {
    std::string colorString = JsonManager::UIElements["minimap"]["color_theme"]["hall_room_foreground"];
    return ConsoleColor::getForegroundConsoleColor(colorString);
}