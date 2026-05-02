//
// Created by tmpat on 11.05.2025.
//

#include "DoorTile.h"

#include "../Managers/JsonManager.h"

DoorTile::DoorTile(std::string symbol, std::string interactionDescription, Vector2 travelDirection, Vector2 position) :
InteractableTile(
    JsonManager::allTiles["door"]["string"],
    interactionDescription,
    TileInteractionType::Travel,
    position,
    ConsoleColor::getForegroundConsoleColor(JsonManager::allTiles["door"]["color_foreground"]),
    ConsoleColor::getBackgroundConsoleColor(JsonManager::allTiles["door"]["color_background"])
    ){
    m_travelDirection = travelDirection;
}

Vector2 DoorTile::getTravelDirection() {
    return m_travelDirection;
}

RoomChoice DoorTile::getInteractionProperties(){
    return {m_choiceType, m_travelDirection};
}

DoorTile* DoorTile::clone() const{
    return new DoorTile(*this);
}