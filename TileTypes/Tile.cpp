//
// Created by alaf4 on 10.05.2025.
//

#include "Tile.h"

#include "../Managers/StringExtensions.h"

Tile::Tile(std::string symbol, Vector2 position, ForegroundConsoleColor foregroundColor, BackgroundConsoleColor backgroundColor) {
    m_symbol = symbol;
    m_position = position;
    m_foregroundColor = foregroundColor;
    m_backgroundColor = backgroundColor;
}

Tile::Tile(std::string symbol, Vector2 position) {
    m_symbol = symbol;
    m_position = position;
    m_foregroundColor = ForegroundConsoleColor::Default;
    m_backgroundColor = BackgroundConsoleColor::Default;
}

Tile::Tile(std::string symbol, Vector2 position, std::string foregroundColor, std::string backgroundColor) {
    m_symbol = symbol;
    m_position = position;
    m_foregroundColor = ConsoleColor::getForegroundConsoleColor(foregroundColor);
    m_backgroundColor = ConsoleColor::getBackgroundConsoleColor(backgroundColor);
}

std::string Tile::getSymbol() {
    return StringExtensions::colorizeString(m_symbol, m_foregroundColor, m_backgroundColor);
}

Vector2 Tile::getPosition() {
    return m_position;
}