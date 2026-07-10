//
// Created by Vilém on 06/06/2025.
//

#include "JsonManager.h"
#include "ConsoleManager.h"

nlohmann::json JsonManager::getJsonData(std::string filePath) {
    ConsoleManager::printLog("opening json of path: " + filePath + "\n");
    std::ifstream file(filePath);

    ConsoleManager::printLog("checking json\n");

    if (!file.is_open()) {
        return nullptr;
    }

    ConsoleManager::printLog("reading json\n");

    nlohmann::json data;
    file >> data;

    std::string jsonSize = std::to_string(data.size());
    std::string message = "returning json of size: " + jsonSize + "\n";
    ConsoleManager::printLog(message);

    return data;
}

nlohmann::json JsonManager::allTiles = getJsonData("../JSON/Tiles.json");
nlohmann::json JsonManager::UIElements = getJsonData("../JSON/UIElements.json");
nlohmann::json JsonManager::weaponData = getJsonData("../JSON/Weapons.json");
nlohmann::json JsonManager::enemyData = getJsonData("../JSON/Enemies.json");

std::string JsonManager::toString(nlohmann::json value) {
    std::string output = value;
    return value;
}


