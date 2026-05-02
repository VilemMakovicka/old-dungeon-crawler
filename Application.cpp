//
// Created by tmpat on 09.05.2025.
//

#include "Application.h"
/* zde bude "manager" hry plus minus bambus
* dodelat!!!!*/
void Application::Run() {

    Menu* mainMenu = new MainMenu();
    int applicationState = mainMenu->printAndGetChoice();
    delete mainMenu;

    GameInstance* game = new GameInstance();
    while (applicationState > 0){
        if (applicationState == 1) {
            game->NewGame();
        }
        else if (applicationState == 2 && GameInstance::s_savedGameState != nullptr) {
            game->LoadGame();
        }
        else {
            continue; //Pokud ani jedna podmínka nevyhověla, spusť celý proces znovu. (Pro případ bugů)
        }

        applicationState = game->Run();
    }
}

Application::Application() {

}

Application::~Application() {

}