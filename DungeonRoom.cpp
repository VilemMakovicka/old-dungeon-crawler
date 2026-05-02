//
// Created by adaze on 12.05.2025.
//

#include "DungeonRoom.h"

#include "Managers/ConsoleManager.h"

DungeonRoom::DungeonRoom(Vector2 positionOnMap, ForceGenerateState northDoor, ForceGenerateState southDoor, ForceGenerateState eastDoor, ForceGenerateState westDoor) :
Room(positionOnMap, northDoor, southDoor, eastDoor, westDoor) {
    gen_generateWeapons();
    gen_generateEnemies();
}

void DungeonRoom::gen_generateWeapons() {
    int weaponTokens = Random::getRandomInt(0, 3);

    std::vector<Tile*> selectedTiles = getRandomEmptyTiles(weaponTokens);
    for(Tile* tile : selectedTiles) {
        setTileOnPosition(tile->getPosition(), WeaponTile::getBasicSwordTile(tile->getPosition()));
    }
}

void DungeonRoom::gen_generateEnemies() {
    int enemyTokens = Random::getRandomInt(0, 2);

    std::vector<Tile*> selectedTiles = getRandomEmptyTiles(enemyTokens);
    for (Tile* tile : selectedTiles) {
        setTileOnPosition(tile->getPosition(), new EnemyTile(tile->getPosition(), Enemy::getRandomEnemyOfType(EnemyType::Basic)));
    }
}


std::string DungeonRoom::getMinimapSymbol() {
    try {
        nlohmann::json UIElements = JsonManager::UIElements["minimap"]["elements"]["dungeon_room"];

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
        ConsoleManager::printError("Could not find the correct symbol for 'dungeon_room'");
        return "!";
    }
}

BackgroundConsoleColor DungeonRoom::getMinimapBackgroundColor() {
    std::string colorString = JsonManager::UIElements["minimap"]["color_theme"]["dungeon_room_background"];
    return ConsoleColor::getBackgroundConsoleColor(colorString);
}

ForegroundConsoleColor DungeonRoom::getMinimapForegroundColor() {
    std::string colorString = JsonManager::UIElements["minimap"]["color_theme"]["dungeon_room_foreground"];
    return ConsoleColor::getForegroundConsoleColor(colorString);
}
