#ifndef GAME_MAP_HPP
#define GAME_MAP_HPP
#include "gl/freeglut.h"
#include "Room.hpp"
#include "Tile.hpp"
#include "Player.hpp"
#include "BasicMonster.hpp"

enum GameState{PLAYER_TURN, NPC_TURN, PLAYER_DEAD};


class GameMap
{
  public:
    GameMap (void);
    ~GameMap (void);
    void initialize (int max_rooms = 6);
    void draw (void);
    void processState (void);
    void updateFOV (void);

    void movePlayerUp (void);
    void movePlayerDown (void);
    void movePlayerLeft (void);
    void movePlayerRight (void);

  private:
    int m_nMapWidth;
    int m_nMapHeight;
    Tile m_mTiles[66][51];
    void create_h_tunnel (int x1, int x2, int y);
    void create_v_tunnel (int y1, int y2, int x);
    void create_room (Room room, bool createNPC = true);
    Room m_vRooms[20];
    Player m_pPlayer;
    void drawMap (void);
    void drawEntities (void);
    void drawBattle (void);
    void drawUI (void);
    void drawText(int x, int y, std::string input);
    void loadTextureFromBmp (const char* szImageFileName);
    GLuint m_uiTextureId;
    std::string  m_pucTextureArray;
    void createDungeon (int maxRooms);
    BasicMonster m_vMonsters[20];
    int m_nCurrentVisibleMonster;
    int m_nMonsterCounter;
    GameState m_pCurrentState;
   
};
#endif