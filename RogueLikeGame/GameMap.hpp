#ifndef GAME_MAP_HPP
#define GAME_MAP_HPP
#include <map>
#include <vector>
#include "Tile.hpp"
class GameMap
{
  public:
    GameMap (void);
    ~GameMap (void);
    void initialize (int width, int height);
    std::map<int,std::vector<Tile>> getTiles (void);
  private:
    int m_nMapWidth;
    int m_nMapHeight;
    std::map<int,std::vector<Tile>> m_mTiles;
};

inline std::map<int, std::vector<Tile>> GameMap::getTiles (void)
{
  return m_mTiles;
}
#endif