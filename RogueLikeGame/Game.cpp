#include "Game.hpp"
Game::Game(void)
{
  p1= new Player(0.0f, 0.0f, '@', "BLACK");
  vEntities.push_back(p1);
}

Game::~Game(void)
{
  if(p1 != NULL) delete p1;
  for(std::vector<Entity*>::iterator it= vEntities.begin(); it != vEntities.end(); ++it)
    if ((*it) != NULL) delete (*it);
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
  //before we draw entities add the player
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

void Game::addNpc(float x, float y, char c, std::string color)
{
  Entity* n = new Entity(x,y,c,color);
  vEntities.push_back(n);
}

void Game::processKeyboardKeys(unsigned char key, int x, int y) 
{
  switch(toupper(key))
  {
    case 'A':
      p1->move(-0.01, 0);
      break;
    case 'D':
      p1->move(0.01, 0);
      break;
    case 'S':
      p1->move(0, -0.01);
      break;
    case 'W':
      p1->move(0, 0.01);
      break;      
  }
  glutPostRedisplay();
  if (key == 27)
    exit(0);
}

void Game::processDirectionKeys(int key, int x, int y) 
{
  switch(key)
  {
    case GLUT_KEY_LEFT:
      p1->move(-0.01, 0);
      break;
    case GLUT_KEY_RIGHT:
      p1->move(0.01, 0);
      break;
    case GLUT_KEY_DOWN:
      p1->move(0, -0.01);
      break;
    case GLUT_KEY_UP:
      p1->move(0, 0.01);
      break;      
  }
  glutPostRedisplay();
  if (key == 27)
    exit(0);
}