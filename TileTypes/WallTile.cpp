//
// Created by Vilém on 07/06/2025.
//

#include "WallTile.h"

WallTile::WallTile(Vector2 position) :
StaticTile(
    JsonManager::allTiles["wall"]["string"],
    position,
    ConsoleColor::getForegroundConsoleColor(JsonManager::allTiles["wall"]["color_foreground"]),
    ConsoleColor::getBackgroundConsoleColor(JsonManager::allTiles["wall"]["color_background"])
    ){

}

WallTile::~WallTile() {

}

StaticTile *WallTile::clone() const {
    return new WallTile(*this);
}