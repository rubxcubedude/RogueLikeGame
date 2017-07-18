#include "Game.hpp"
#include "ColorConstants.hpp"




Game::Game()
{
  m_nScreenWidth = 976;
  m_nScreenHeight = 751;
  m_pGameMap.initialize(20);
  m_pGameMap.updateFOV();
  int i =0;
}

Game::~Game(void)
{
}


void Game::update()
{
  draw();
  m_pGameMap.processState();
}

void Game::draw(void)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  //before we draw entities add the player
  m_pGameMap.draw();
  glutSwapBuffers();
}


void Game::processKeyboardKeys(unsigned char key, int x, int y) 
{
  
  switch(toupper(key))
  {
    case 'A':
      m_pGameMap.movePlayerUp();
      break;
    case 'D':
      m_pGameMap.movePlayerDown();
      break;
    case 'S':
      m_pGameMap.movePlayerLeft();
      break;
    case 'W':
      m_pGameMap.movePlayerRight();
      break;      
  }
  m_pGameMap.updateFOV();
  glutPostRedisplay();
  if (key == 27)
    exit(0);
}

void Game::processDirectionKeys(int key, int x, int y) 
{
  switch(key)
  {
    case GLUT_KEY_LEFT:
      m_pGameMap.movePlayerLeft();
      break;
    case GLUT_KEY_RIGHT:
      m_pGameMap.movePlayerRight();
      break;
    case GLUT_KEY_DOWN:
      m_pGameMap.movePlayerDown();
      break;
    case GLUT_KEY_UP:
     m_pGameMap.movePlayerUp();
      break;      
  }
  m_pGameMap.updateFOV();
  glutPostRedisplay();
  if (key == 27)
    exit(0);
}


