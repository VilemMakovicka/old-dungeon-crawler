//
// Created by Vilém on 06/06/2025.
//

#include "JsonManager.h"

nlohmann::json JsonManager::getJsonData(std::string filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        return nullptr;
    }

    nlohmann::json data;
    file >> data;

    return data;
}

nlohmann::json JsonManager::allTiles = getJsonData("../JSON/Tiles.json");
nlohmann::json JsonManager::UIElements = getJsonData("../JSON/UIElements.json");
nlohmann::json JsonManager::weaponData = getJsonData("../JSON/weapons.json");
nlohmann::json JsonManager::enemyData = getJsonData("../JSON/Enemies.json");

std::string JsonManager::toString(nlohmann::json value) {
    std::string output = value;
    return value;
}


