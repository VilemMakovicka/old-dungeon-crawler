//
// Created by tmpat on 09.05.2025.
//

#ifndef APPLICATION_H
#define APPLICATION_H

#include <iostream>
#include "Menus/Menu.h"
#include "Menus/MainMenu.h"
#include "GameInstance.h"
class Application {
private:
    static Application* instance;
public:
    Application();
    ~Application();
    void Run();
    static int getDifficulty();
};


#endif //APPLICATION_H