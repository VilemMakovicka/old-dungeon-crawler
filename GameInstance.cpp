//
// Created by Vilém on 10/05/2025.
//

#include "GameInstance.h"

#include "Menus/CombatMenu.h"
#include "TileTypes/EmptyTile.h"

GameInstance::GameInstance() {
    //NewGame();
    s_savedGameState = new GameInstance(nullptr, nullptr, 0);
}
GameInstance::GameInstance(PlayerState* playerState, Map* map, int difficulty) {
    m_playerState = playerState;
    m_map = map;
    m_difficulty = difficulty;
}

GameInstance::~GameInstance() {
    delete m_playerState;
    delete m_map;
}

GameInstance* GameInstance::s_savedGameState = nullptr;

int GameInstance::s_currentGameDifficulty = 1;

void GameInstance::NewGame() {
    m_playerState = new PlayerState();
    m_map = new Map();
    Menu* difficultyMenu = new DifficultyMenu();
    m_difficulty = difficultyMenu->printAndGetChoice();
    s_currentGameDifficulty = m_difficulty;
    delete difficultyMenu;
    //std::clog << "Creating a new game..." << std::endl;
}

void GameInstance::SaveGame() {
    std::clog << "Saving this game..." << std::endl;
    try {
        m_map->getRoom(m_playerState->GetPositionOnMap());

        delete s_savedGameState->m_playerState;
        delete s_savedGameState->m_map;

        s_savedGameState->m_playerState = new PlayerState(*m_playerState);
        s_savedGameState->m_map = new Map(*m_map);
        s_savedGameState->m_difficulty = m_difficulty;
    }
    catch (const char* msg){
        std::cerr << "Could not save game" << std::endl;
        std::cerr << msg << std::endl;
    }
    std::clog << "Saving completed." << std::endl;
}

void GameInstance::LoadGame() {
    std::clog << "Loading a saved game..." << std::endl;
    try {
        delete m_playerState;
        delete m_map;

        m_playerState = new PlayerState(*s_savedGameState->GetPlayerState());
        m_map = new Map(*s_savedGameState->GetMap());
        m_difficulty = s_savedGameState->GetDifficulty();
        s_currentGameDifficulty = m_difficulty;
    }
    catch (const char* msg){
        std::cerr << "Could not load game" << std::endl;
        std::cerr << msg << std::endl;
    }
    std::clog << "Loading completed." << std::endl;
}


Tile *GameInstance::getTileOnCurrentMap(Vector2 position) {
    return m_map->getRoom(m_playerState->GetPositionOnMap())->getTileOnPosition(position);
}

int GameInstance::Run() {
    while (m_playerState->GetHealth() > 0) {
        getCurrentRoom()->dropDeadEnemyLoot();

        RoomMenu* roomMenu = new RoomMenu(m_map->getRoom(m_playerState->GetPositionOnMap()), m_map, m_playerState);
        RoomChoice tileInteraction = roomMenu->printAndReturnChoice();
        delete roomMenu;

        switch (tileInteraction.type) {
            case TileInteractionType::Travel:
                try {
                    m_playerState->travel(tileInteraction.position);
                }
                catch (const char* msg){
                    std::cerr << "Could not travel" << std::endl;
                    std::cerr << msg << std::endl;
                }
                break;
            case TileInteractionType::PickUp:
                //Tile se zkusí překonvertovat na WeaponTile
                    if (auto* InteractingTile = dynamic_cast<WeaponTile*>(getTileOnCurrentMap(tileInteraction.position))) {
                        bool hadWeaponBeforePickup = m_playerState->getWeapon() != nullptr;

                        Tile* replaceWith;
                        if (hadWeaponBeforePickup) replaceWith = new WeaponTile(m_playerState->getWeapon(), InteractingTile->getPosition());
                        else replaceWith = new EmptyTile(InteractingTile->getPosition());

                        m_playerState->setWeapon(InteractingTile->getWeapon());
                        setTileOnCurrentMap(InteractingTile->getPosition(), replaceWith);
                    }
                break;
            case TileInteractionType::Fight: {
                std::vector<Enemy*> enemyList;

                for (InteractableTile* tile : m_map->getRoom(m_playerState->GetPositionOnMap())->getInteractableTiles()) {
                    if (auto* InteractingTile = dynamic_cast<EnemyTile*>(tile)) enemyList.push_back(InteractingTile->getEnemy());
                }

                CombatMenu* combat_menu = new CombatMenu(m_playerState, enemyList);
                combat_menu->printAndGetChoice();
                break;
            }
            default:
                break;
        }

        if (m_playerState->GetHealth() > 0) SaveGame();
    }

    Menu* deathMenu = new DeathMenu();
    int choice = deathMenu->printAndGetChoice();
    delete deathMenu;
    return choice;
}

int GameInstance::GetDifficulty() {
    return m_difficulty;
}

Map* GameInstance::GetMap() {
    return m_map;
}

PlayerState* GameInstance::GetPlayerState() {
    return m_playerState;
}

void GameInstance::setDifficulty(int difficulty) {
    m_difficulty = difficulty;
}

void GameInstance::setTileOnCurrentMap(Vector2 position, Tile *newTile) {
    m_map->getRoom(m_playerState->GetPositionOnMap())->setTileOnPosition(position, newTile);
}

Room *GameInstance::getCurrentRoom() {
    return m_map->getRoom(m_playerState->GetPositionOnMap());
}

