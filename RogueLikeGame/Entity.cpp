#include "Entity.hpp"

Entity::Entity(float x, float y, char c, std::string color)
{
	position_x = x;
	position_y = y;
  display_char = c;
	display_color = color;
}

Entity::~Entity()
{
}

void Entity::move(float dx, float dy)
{
	position_x += dx;
	position_y += dy;
}