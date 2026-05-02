//
// Created by adaze on 10.05.2025.
//

#include "RoomChoice.h"


std::string RoomChoice::toString() {
    std::string finalString;
    switch (type) {
        case TileInteractionType::Travel:
            finalString = "Travel to: ";
        break;
        case TileInteractionType::PickUp:
            finalString = "Pickup on position: ";
        break;
        default:
            break;
    }
    return finalString + position.toString();
}