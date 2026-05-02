//
// Created by Vilém on 06/06/2025.
//

#ifndef JSONMANAGER_H
#define JSONMANAGER_H

#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>

class JsonManager {
public:
    static nlohmann::json allTiles;
    static nlohmann::json UIElements;
    static nlohmann::json weaponData;

    static nlohmann::json getJsonData(std::string filePath);
    static std::string toString(nlohmann::json value);
};



#endif //JSONMANAGER_H
