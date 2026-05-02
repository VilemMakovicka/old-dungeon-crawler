//
// Created by adaze on 10.05.2025.
//

#include "InteractableTile.h"

InteractableTile::InteractableTile(std::string symbol, std::string interactionDescription, TileInteractionType choiceType, Vector2 position, ForegroundConsoleColor foregroundColor, BackgroundConsoleColor backgroundColor) :
Tile(symbol, position, foregroundColor, backgroundColor) {
    m_interactionDescription = interactionDescription;
    m_choiceType = choiceType;
    m_interactionVector2 = {0, 0};
}

InteractableTile::InteractableTile(std::string symbol, std::string interactionDescription, TileInteractionType choiceType, Vector2 position) :
Tile(symbol, position) {
    m_interactionDescription = interactionDescription;
    m_choiceType = choiceType;
    m_interactionVector2 = {0, 0};
}

InteractableTile::InteractableTile(std::string symbol, std::string interactionDescription, TileInteractionType choiceType, Vector2 position, std::string foregroundColor, std::string backgroundColor) :
Tile(symbol, position, foregroundColor, backgroundColor) {
    m_interactionDescription = interactionDescription;
    m_choiceType = choiceType;
    m_interactionVector2 = {0, 0};
}


std::string InteractableTile::getInteractionDescription() {
    return m_interactionDescription;
}

RoomChoice InteractableTile::getInteractionProperties() {
    return {m_choiceType, m_interactionVector2};
}

void InteractableTile::setInteractionVector2(Vector2 vector2) {
    m_interactionVector2 = vector2;
}

void InteractableTile::setChoiceType(TileInteractionType choiceType) {
    m_choiceType = choiceType;
}

TileInteractionType InteractableTile::getInteractionType() {
    return m_choiceType;
}
