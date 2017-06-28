#include "Tile.hpp"

Tile::Tile(double x, double y, bool isBlocked, bool isBlockingSight)
{
  m_dPositionX = x;
  m_dPositionY = y;
  m_bIsBlocked = isBlocked;
  m_bIsBlockingSight = isBlockingSight;
}

Tile::~Tile()
{
}