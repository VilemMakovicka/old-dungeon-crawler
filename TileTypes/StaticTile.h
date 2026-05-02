//
// Created by tmpat on 10.05.2025.
//

#ifndef STATICTILE_H
#define STATICTILE_H



#include "Tile.h"


class StaticTile : public Tile{
public:
    StaticTile(std::string symbol, Vector2 position);
    StaticTile(std::string symbol, Vector2 position, ForegroundConsoleColor foregroundColor, BackgroundConsoleColor backgroundColor = BackgroundConsoleColor::Default);
    StaticTile(std::string symbol, Vector2 position, std::string foregroundColor, std::string backgroundColor = "Default");
    StaticTile *clone() const override;
};



#endif //STATICTILE_H

