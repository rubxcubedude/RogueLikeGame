#include "Entity.hpp"

Entity::Entity(float x, float y, char c, const float color[4])
{
  position_x = x;
  position_y = y;
  display_char = c;
	memcpy(display_color, color, sizeof(display_color));
}

Entity::~Entity()
{
}

void Entity::move(float dx, float dy)
{
  position_x += dx;
  position_y += dy;
}