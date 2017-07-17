#ifndef GAME_HPP
#define GAME_HPP

#include <vector>
#include "Entity.hpp"
#include "Player.hpp"
#include "GameMap.hpp"

#include "gl\freeglut.h"

class Game
{
  public:
    Game (int width =800, int height = 500);
    ~Game (void);

    void update ();

    void processDirectionKeys(int key, int x, int y);
    void processKeyboardKeys(unsigned char key, int x, int y);
  private:
    
    void draw (void);
    
    Player* m_pPlayer;
    GameMap m_pGameMap;
    
    int m_nScreenWidth;
    int m_nScreenHeight;
};

#endif