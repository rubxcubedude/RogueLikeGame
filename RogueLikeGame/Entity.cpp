#include "Entity.hpp"

Entity::Entity(int x, int y, char c, const float color[4])
{
  m_dPosition_x = x;
  m_dPosition_y = y;
  m_cDisplay_char = c;
	memcpy(m_afDisplay_color, color, sizeof(m_afDisplay_color));
  m_bIsVisible = false;
}

Entity::~Entity()
{
}

void Entity::move(int dx, int dy)
{
  m_dPosition_x += dx;
  m_dPosition_y += dy;
}