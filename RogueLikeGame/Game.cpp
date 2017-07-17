#include "Game.hpp"
#include "ColorConstants.hpp"




Game::Game(int width, int height)
{
  m_pPlayer = new Player(width/2.0+0.5, height/2.0-3, '@', WHITEF);
  m_nScreenWidth = width;
  m_nScreenHeight = height;
  m_pGameMap.initialize(width, height, m_pPlayer, 20);
  m_pGameMap.updateFOV();
  int i =0;
}

Game::~Game(void)
{
  if(m_pPlayer != NULL) delete m_pPlayer;
}


void Game::update()
{
  draw();
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
  std::map<int,std::vector<Tile>> tempTiles = m_pGameMap.getTiles();
  
  switch(toupper(key))
  {
    case 'A':
      m_pPlayer->move(-15, 0);
      if(tempTiles[m_pPlayer->getX()/15][m_pPlayer->getY()/15].isBlocked())
        m_pPlayer->move(15, 0);
      break;
    case 'D':
      m_pPlayer->move(15, 0);
      if(tempTiles[m_pPlayer->getX()/15][m_pPlayer->getY()/15].isBlocked())
        m_pPlayer->move(-15, 0);
      break;
    case 'S':
      m_pPlayer->move(0, -15);
      if(tempTiles[m_pPlayer->getX()/15][m_pPlayer->getY()/15].isBlocked())
        m_pPlayer->move(0, 15);
      break;
    case 'W':
      m_pPlayer->move(0, 15);
      if(tempTiles[m_pPlayer->getX()/15][m_pPlayer->getY()/15].isBlocked())
        m_pPlayer->move(0, -15);
      break;      
  }
  m_pGameMap.updateFOV();
  glutPostRedisplay();
  if (key == 27)
    exit(0);
}

void Game::processDirectionKeys(int key, int x, int y) 
{
  std::map<int,std::vector<Tile>> tempTiles = m_pGameMap.getTiles();
  switch(key)
  {
    case GLUT_KEY_LEFT:
      m_pPlayer->move(-15, 0);
      if(tempTiles[m_pPlayer->getX()/15+1][m_pPlayer->getY()/15+1].isBlocked())
        m_pPlayer->move(15, 0);
      break;
    case GLUT_KEY_RIGHT:
      m_pPlayer->move(15, 0);
      if(tempTiles[m_pPlayer->getX()/15+1][m_pPlayer->getY()/15+1].isBlocked())
        m_pPlayer->move(-15, 0);
      break;
      break;
    case GLUT_KEY_DOWN:
      m_pPlayer->move(0, -15);
      if(tempTiles[m_pPlayer->getX()/15+1][m_pPlayer->getY()/15+1].isBlocked())
        m_pPlayer->move(0, 15);
      break;
      break;
    case GLUT_KEY_UP:
      m_pPlayer->move(0, 15);
      if(tempTiles[m_pPlayer->getX()/15+1][m_pPlayer->getY()/15+1].isBlocked())
        m_pPlayer->move(0, -15);
      break;      
  }
  m_pGameMap.updateFOV();
  glutPostRedisplay();
  if (key == 27)
    exit(0);
}


