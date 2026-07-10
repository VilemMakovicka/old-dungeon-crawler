#include <iostream>
#include "Application.h"
#include "Room.h"
#include "Enemies/Enemy.h"
#include "Managers/ConsoleManager.h"
#include "Menus/RoomMenu.h"
#include "Managers/Random.h"

int main() {
    //Tenhle řádek opravuje problémy s Ansi escape kódama (zabarvením konzole atd...)
#ifdef _WIN32
    ConsoleManager::EnableUTF8andANSI();
#endif

    //std::ios_base::sync_with_stdio(false);

    Application* app = new Application();
    app -> Run();
    delete app;

    return 0;
}
