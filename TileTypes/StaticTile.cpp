//
// Created by tmpat on 10.05.2025.
//

#include "StaticTile.h"

StaticTile::StaticTile(std::string symbol, Vector2 position) :
Tile(symbol, position){

}

StaticTile::StaticTile(std::string symbol, Vector2 position, std::string foregroundColor, std::string backgroundColor) :
Tile(symbol, position, foregroundColor, backgroundColor){

}

StaticTile::StaticTile(std::string symbol, Vector2 position, ForegroundConsoleColor foregroundColor, BackgroundConsoleColor backgroundColor) :
Tile(symbol, position, foregroundColor, backgroundColor){

}

StaticTile *StaticTile::clone() const {
    return new StaticTile(*this);
}