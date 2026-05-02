//
// Created by alaf4 on 10.05.2025.
//

#ifndef ROOMMENU_H
#define ROOMMENU_H

#include "../Room.h"
#include "Menu.h"
#include "../RoomChoice.h"
#include "../PlayerState.h"

class RoomMenu : public Menu{
private:
    Room* m_room;
    PlayerState* m_playerState;
    std::vector<InteractableTile*> categorizeInteractableTiles(std::vector<InteractableTile*> interactableTiles);
public:
    int printAndGetChoice() override;
    RoomChoice printAndReturnChoice();
    RoomMenu(Room* room, PlayerState* playerState);
};



#endif //ROOMMENU_H
