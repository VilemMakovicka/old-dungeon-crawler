#include <iostream>
#include "Application.h"
#include "Room.h"
#include "Enemies/Enemy.h"
#include "Managers/ConsoleManager.h"
#include "Menus/RoomMenu.h"
#include "Managers/Random.h"

int main() {
    //Tenhle řádek opravuje problémy s Ansi escape kódama (zabarvením konzole atd...)
    ConsoleManager::fixAnsiProblems();

/*enemy test
    auto en = Enemy::getRandomEnemyOfType(EnemyType::BasicEnemy);
    std::cout << en->getName() << std::endl;
    std::cout << std::to_string(en->getHealth()) << std::endl;
    std::cout << std::to_string(en->getAttack()) << std::endl;
*/
    Application* app = new Application();
    app -> Run();
    delete app;

    return 0;
}
