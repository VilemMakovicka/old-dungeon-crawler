//
// Created by alaf4 on 10.05.2025.
//

#ifndef TILE_H
#define TILE_H
#include <iostream>

#include "../Enums/ForegroundConsoleColor.h"
#include "../Managers/Vector2.h"
#include "../Managers/JsonManager.h"

class Tile {
protected:
    std::string m_symbol;
    ForegroundConsoleColor m_foregroundColor;
    BackgroundConsoleColor m_backgroundColor;
    Vector2 m_position;
public:
    Tile(std::string symbol, Vector2 position);
    Tile(std::string symbol, Vector2 position, ForegroundConsoleColor foregroundColor, BackgroundConsoleColor backgroundColor = BackgroundConsoleColor::Default);
    Tile(std::string symbol, Vector2 position, std::string foregroundColor, std::string backgroundColor = "Default");
    virtual Tile* clone() const = 0;
    virtual ~Tile() = default;
    std::string getSymbol();
    Vector2 getPosition();
};

#endif //TILE_H
