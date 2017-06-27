#ifndef GAME_HPP
#define GAME_HPP

#include <vector>
#include "Entity.hpp"
#include "Player.hpp"
#include "gl\freeglut.h"

class Game
{
  public:
    Game (void);
    ~Game (void);
    void initialize (std::vector<Entity*> v);

    void update ();

    void addNpc(float x, float y, char c, std::string color);

    void processDirectionKeys(int key, int x, int y);
    void processKeyboardKeys(unsigned char key, int x, int y);
  private:
    
    void draw (void);
    void drawAllEntities(std::vector<Entity*> v);
    
    Player* p1;
    std::vector<Entity*> vEntities;
};

#endif