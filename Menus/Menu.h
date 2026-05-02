//
// Created by Vilém on 09/05/2025.
//

#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <vector>
#include "../Managers/Vector2.h"
#include "../Managers/InputManager.h"
#include "../Managers/ConsoleManager.h"

class Menu{
protected:
    int printAndReturnChoiceMenu(std::string menuContents, Vector2 choiceRange);
public:
    Menu();
    virtual int printAndGetChoice() = 0;
};



#endif //MENU_H
