#ifndef GAME_MAP_HPP
#define GAME_MAP_HPP
#include <vector>
#include "Tile.hpp"
class GameMap
{
  public:
    GameMap (void);
    ~GameMap (void);
    void initialize (int width, int height);
    std::vector<Tile> getTiles (void);
  private:
    int m_nMapWidth;
    int m_nMapHeight;
    std::vector<Tile> m_vTiles;
};

inline std::vector<Tile> GameMap::getTiles (void)
{
  return m_vTiles;
}
#endif