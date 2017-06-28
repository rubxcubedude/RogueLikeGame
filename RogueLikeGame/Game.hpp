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
    void initialize (std::vector<Entity*> v);

    void update ();

    void addNpc(float x, float y, char c, const float color[4]);

    void processDirectionKeys(int key, int x, int y);
    void processKeyboardKeys(unsigned char key, int x, int y);
  private:
    
    void draw (void);
    void drawAllEntities(std::vector<Entity*> v);
    void drawMap (void);
    
    Player* m_pPlayer;
    GameMap m_pGameMap;
    std::vector<Entity*> m_vEntities;

    int m_nScreenWidth;
    int m_nScreenHeight;
};

#endif