//
// Created by Vilém on 06/06/2025.
//

#ifndef COMBATMENU_H
#define COMBATMENU_H

#include "Menu.h"
#include "../PlayerState.h"
#include "../Enemies/Enemy.h"

class CombatMenu : public Menu{
private:
    std::vector<Enemy*> m_enemies;
    PlayerState* m_playerState;
    void printVisuals();
public:
    CombatMenu(PlayerState* playerState, std::vector<Enemy*> enemies);
    int printAndGetChoice() override;

};



#endif //COMBATMENU_H
