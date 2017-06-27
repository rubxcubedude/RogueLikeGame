#ifndef PLAYER_HPP
#define PLAYER_HPP
#include "Entity.hpp"
class Player: public Entity
{
	public:
		Player(float x, float y, char c, std::string color);
		~Player();
};
#endif