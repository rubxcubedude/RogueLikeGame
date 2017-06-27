#include "Game.hpp"
Game::Game(void)
{
}

Game::~Game(void)
{
}

void Game::initialize(std::vector<Entity*> v)
{
		vEntities= v;
}

void Game::update()
{
	draw();
}

void Game::draw(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	drawAllEntities(vEntities);
	glutSwapBuffers();
}

void Game::drawAllEntities(std::vector<Entity*> v)
{
	for(std::vector<Entity*>::iterator it= v.begin(); it != v.end(); ++it)
	{
		//set position to draw
		glRasterPos2d((*it)->getX(),(*it)->getY());
		//what we drawing has to be character
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, (*it)->getChar());
	}
}