#ifndef GAME_MAP_HPP
#define GAME_MAP_HPP
#include <map>
#include <vector>
#include "Room.hpp"
#include "Tile.hpp"
#include "Player.hpp"
class GameMap
{
  public:
    GameMap (void);
    ~GameMap (void);
    void initialize (int width, int height, Player* p, int max_rooms = 10, int room_min_size = 3, int room_max_size=20);
    std::map<int,std::vector<Tile>> getTiles (void);
  private:
    int m_nMapWidth;
    int m_nMapHeight;
    std::map<int,std::vector<Tile>> m_mTiles;
    void create_h_tunnel (int x1, int x2, int y);
    void create_v_tunnel (int y1, int y2, int x);
    void create_room (Room room);
};

inline std::map<int, std::vector<Tile>> GameMap::getTiles (void)
{
  return m_mTiles;
}
#endif