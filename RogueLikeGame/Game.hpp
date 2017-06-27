#ifndef GAME_HPP
#define GAME_HPP

#include <vector>
#include "Entity.hpp"
#include "gl\freeglut.h"

class Game
{
	public:
		Game (void);
		~Game (void);
		void initialize (std::vector<Entity*> v);
		void update ();
	private:
		std::vector<Entity*> vEntities;
		void draw (void);
		void drawAllEntities(std::vector<Entity*> v);
};

#endif