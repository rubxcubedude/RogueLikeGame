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
    for(int j = 0; j <height/15.0; ++j)
      m_vTiles.push_back(Tile(i*15,j*15));
  }

}