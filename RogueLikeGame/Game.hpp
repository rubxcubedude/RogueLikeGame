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
    Game ();
    ~Game (void);

    void update ();

    void processDirectionKeys(int key, int x, int y);
    void processKeyboardKeys(unsigned char key, int x, int y);
  private:
    
    void draw (void);
    
    GameMap m_pGameMap;
    
    int m_nScreenWidth;
    int m_nScreenHeight;
};

#endif