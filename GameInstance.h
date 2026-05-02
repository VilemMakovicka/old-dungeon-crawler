//
// Created by Vilém on 10/05/2025.
//

#ifndef GAMEINSTANCE_H
#define GAMEINSTANCE_H

#include "Menus/Menu.h"
#include "DeathMenu.h"
#include "Map.h"
#include "Menus/DifficultyMenu.h"
#include "PlayerState.h"
#include "Menus/RoomMenu.h"
#include <conio.h>

class GameInstance {
private:
    PlayerState* m_playerState;
    Map* m_map;
    int m_difficulty;
    Tile* getTileOnCurrentMap(Vector2 position);
    void setTileOnCurrentMap(Vector2 position, Tile* newTile);
public:
    static int s_currentGameDifficulty;
    static GameInstance *s_savedGameState;
    GameInstance();
    GameInstance(PlayerState* playerState, Map* map, int difficulty);
    ~GameInstance();
    int Run();
    void LoadGame();
    void SaveGame();
    void NewGame();
    PlayerState* GetPlayerState();
    Map* GetMap();
    int GetDifficulty();
    void setDifficulty(int difficulty);
    Room* getCurrentRoom();
};



#endif //GAMEINSTANCE_H
