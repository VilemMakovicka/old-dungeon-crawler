//
// Created by adaze on 10.05.2025.
//

#ifndef ROOMCHOICE_H
#define ROOMCHOICE_H

#include "Managers/Vector2.h"
#include "Enums/TileInteractionType.h"


struct RoomChoice {
    TileInteractionType type;
    Vector2 position;
    std::string toString();
};


#endif //ROOMCHOICE_H
