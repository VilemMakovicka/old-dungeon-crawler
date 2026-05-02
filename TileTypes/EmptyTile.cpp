//
// Created by Vilém on 10/06/2025.
//

#include "EmptyTile.h"

EmptyTile::EmptyTile(Vector2 position) :
StaticTile(
    JsonManager::allTiles["empty"]["string"],
    position,
    ConsoleColor::getForegroundConsoleColor(JsonManager::allTiles["empty"]["color_foreground"]),
    ConsoleColor::getBackgroundConsoleColor(JsonManager::allTiles["empty"]["color_background"])
    ){

}

EmptyTile::~EmptyTile() = default;

StaticTile *EmptyTile::clone() const {
    return new EmptyTile(*this);
}