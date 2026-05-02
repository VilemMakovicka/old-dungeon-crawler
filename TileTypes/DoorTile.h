//
// Created by tmpat on 11.05.2025.
//

#ifndef DOORTILE_H
#define DOORTILE_H
#include "../Managers/Vector2.h"
#include "InteractableTile.h"



class DoorTile : public InteractableTile{
private:
    Vector2 m_travelDirection;
public:
    DoorTile(std::string symbol, std::string interactionDescription, Vector2 travelDirection, Vector2 position);
    DoorTile *clone() const override;
    Vector2 getTravelDirection();
    RoomChoice getInteractionProperties() override;
};



#endif //DOORTILE_H
