//
// Created by adaze on 10.05.2025.
//

#ifndef INTERACTABLETILE_H
#define INTERACTABLETILE_H

#include "Tile.h"
#include "../Enums/TileInteractionType.h"
#include "../RoomChoice.h"

class InteractableTile : public Tile {
protected:
    std::string m_interactionDescription;
    TileInteractionType m_choiceType;
    Vector2 m_interactionVector2;
public:
    InteractableTile(std::string symbol, std::string interactionDescription, TileInteractionType choiceType, Vector2 position);
    InteractableTile(std::string symbol, std::string interactionDescription, TileInteractionType choiceType, Vector2 position, ForegroundConsoleColor foregroundColor, BackgroundConsoleColor backgroundColor = BackgroundConsoleColor::Default);
    InteractableTile(std::string symbol, std::string interactionDescription, TileInteractionType choiceType, Vector2 position, std::string foregroundColor, std::string backgroundColor = "Default");
    std::string getInteractionDescription();
    virtual RoomChoice getInteractionProperties();
    void setChoiceType(TileInteractionType choiceType);
    void setInteractionVector2(Vector2 vector2);
    TileInteractionType getInteractionType();
};



#endif //INTERACTABLETILE_H
