#include "Game.hpp"
#include "ColorConstants.hpp"
Game::Game(int width, int height)
{
  m_pPlayer = new Player(width/2.0, height/2.0+0.5, '@', WHITEF);
  m_vEntities.push_back(m_pPlayer);
  m_nScreenWidth = width;
  m_nScreenHeight = height;
  m_pGameMap.initialize(width, height);
  int i =0;
}

Game::~Game(void)
{
  if(m_pPlayer != NULL) delete m_pPlayer;
  for(std::vector<Entity*>::iterator it= m_vEntities.begin(); it != m_vEntities.end(); ++it)
    if ((*it) != NULL) delete (*it);
}

void Game::initialize(std::vector<Entity*> v)
{
    m_vEntities= v;
}

void Game::update()
{
  draw();
}

void Game::draw(void)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  //before we draw entities add the player
  drawMap();
  drawAllEntities(m_vEntities);
  glutSwapBuffers();
}

void Game::drawMap(void)
{ 
  //store our tiles real quick
  std::vector<Tile> tempTiles = m_pGameMap.getTiles();
  for(std::vector<Tile>::iterator it = tempTiles.begin(); it != tempTiles.end(); ++ it)
  {
    if(it->isBlocked())
      glColor4fv(BLOCKED_TILE);
    else if (it->isBlockingSight())
      glColor4fv(NOT_BLOCKED_TILE);
    else
      glColor4fv(NOT_BLOCKED_TILE);
    //what we drawing has to be character
    if(it->isBlocked())
    {
      glBegin(GL_POLYGON);
        glVertex3f(it->getPosX()-7.5, it->getPosY()+7.5, 0.0);
        glVertex3f(it->getPosX()+7.5, it->getPosY()+7.5, 0.0);
        glVertex3f(it->getPosX()+7.5, it->getPosY()-7.5, 0.0);
        glVertex3f(it->getPosX()-7.5, it->getPosY()-7.5, 0.0);
      glEnd();
    }
    else
    {
      glBegin(GL_LINE_LOOP);
        glVertex3f(it->getPosX()-7.5, it->getPosY()+7.5, 0.0);
        glVertex3f(it->getPosX()+7.5, it->getPosY()+7.5, 0.0);
        glVertex3f(it->getPosX()+7.5, it->getPosY()-7.5, 0.0);
        glVertex3f(it->getPosX()-7.5, it->getPosY()-7.5, 0.0);
      glEnd();
    }
  }
}

void Game::drawAllEntities(std::vector<Entity*> v)
{
  for(std::vector<Entity*>::iterator it= v.begin(); it != v.end(); ++it)
  {
    //set position to draw
		glColor4fv((*it)->getColor());
    glRasterPos2d((*it)->getX(),(*it)->getY());
    //what we drawing has to be character
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, (*it)->getChar());
  }
}

void Game::addNpc(float x, float y, char c, const float color[4])
{
  Entity* n = new Entity(x,y,c,color);
  m_vEntities.push_back(n);
}

void Game::processKeyboardKeys(unsigned char key, int x, int y) 
{
  switch(toupper(key))
  {
    case 'A':
      m_pPlayer->move(-15, 0);
      break;
    case 'D':
      m_pPlayer->move(15, 0);
      break;
    case 'S':
      m_pPlayer->move(0, -15);
      break;
    case 'W':
      m_pPlayer->move(0, 15);
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
      m_pPlayer->move(-15, 0);
      break;
    case GLUT_KEY_RIGHT:
      m_pPlayer->move(15, 0);
      break;
    case GLUT_KEY_DOWN:
      m_pPlayer->move(0, -15);
      break;
    case GLUT_KEY_UP:
      m_pPlayer->move(0, 15);
      break;      
  }
  glutPostRedisplay();
  if (key == 27)
    exit(0);
}