#ifndef GAME_MAP_HPP
#define GAME_MAP_HPP
#include <map>
#include <vector>
#include "gl/freeglut.h"
#include "Room.hpp"
#include "Tile.hpp"
#include "Player.hpp"
class GameMap
{
  public:
    GameMap (void);
    ~GameMap (void);
    void initialize (int width, int height, Player* p, int max_rooms = 6);
    void draw (void);
    std::map<int,std::vector<Tile>> getTiles (void);
    void updateFOV (void);
  private:
    int m_nMapWidth;
    int m_nMapHeight;
    std::map<int,std::vector<Tile>> m_mTiles;
    void create_h_tunnel (int x1, int x2, int y);
    void create_v_tunnel (int y1, int y2, int x);
    void create_room (Room room);
    std::vector<Room> m_vRooms;
    Player* m_pPlayer;
    std::vector<Entity*> m_vEntities;
    void drawAllEntities();
    void drawMap (void);
    void loadTextureFromBmp (const char* szImageFileName);
    GLuint m_uiTextureId;
    std::string  m_pucTextureArray;
    void createDungeon (int maxRooms);
   
};

inline std::map<int, std::vector<Tile>> GameMap::getTiles (void)
{
  return m_mTiles;
}
#endif