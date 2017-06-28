#include "GameMap.hpp"
GameMap::GameMap()
{
}

GameMap::~GameMap()
{
}

void GameMap::initialize(int width, int height)
{
  m_nMapHeight = height;
  m_nMapWidth = width;
  for(int i = 0; i<width/15.0; ++i)
  {
    std::vector<Tile> vTiles;
    for(int j = 0; j <height/15.0; ++j)
    {
      if(j==0 || i == 0|| i == width/15 || j == height/15)
        vTiles.push_back(Tile(i*15,j*15, true));
      else
        vTiles.push_back(Tile(i*15,j*15));
    }
    m_mTiles.insert(make_pair(i, vTiles));
  }

}