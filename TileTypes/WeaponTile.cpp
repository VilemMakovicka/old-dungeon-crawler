//
// Created by adaze on 11.05.2025.
//

#include "WeaponTile.h"
#include <nlohmann/json.hpp>
#include <fstream>

#include "../Managers/JsonManager.h"

Weapon *WeaponTile::getWeapon() {
    return m_weapon;
}

WeaponTile::WeaponTile(Weapon *weapon, Vector2 position) :
InteractableTile(
    JsonManager::allTiles["item"]["string"],
    JsonManager::toString(JsonManager::allTiles["item"]["interaction_description"]) + weapon->toString(),
    TileInteractionType::PickUp,
    position,
    ConsoleColor::getForegroundConsoleColor(JsonManager::allTiles["item"]["color_foreground"]),
    ConsoleColor::getBackgroundConsoleColor(JsonManager::allTiles["item"]["color_background"])
    ){
    m_weapon = weapon;
}

RoomChoice WeaponTile::getInteractionProperties(){
    return {m_choiceType, m_position};
}

WeaponTile *WeaponTile::getBasicSwordTile(Vector2 position) {
    return new WeaponTile(Weapon::getRandomWeaponByType("sword"), position);
}

WeaponTile *WeaponTile::clone() const {
    return new WeaponTile(*this);
}