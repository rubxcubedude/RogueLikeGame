#include "Tile.hpp"

Tile::Tile(double x, double y, bool isBlocked, bool isBlockedSight)
{
  m_dPositionX = x;
  m_dPositionY = y;
  m_bIsBlocked = isBlocked;
  m_bIsBlockedSight = isBlockedSight;
}

Tile::~Tile()
{
}