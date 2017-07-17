#include "Player.hpp"


Player::Player(float x, float y, char c, const float color[4]):
  Entity(x,y,c,color)
{
  m_bIsVisible = true;
}

Player::~Player()
{
}