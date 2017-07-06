#include "Game.hpp"
#include "ColorConstants.hpp"

Game::Game(int width, int height)
{
  m_pPlayer = new Player(width/2.0+0.5, height/2.0-3, '@', WHITEF);
  m_vEntities.push_back(m_pPlayer);
  m_nScreenWidth = width;
  m_nScreenHeight = height;
  m_pGameMap.initialize(width, height, m_pPlayer, 20, 3, 5);
  loadTextureFromBmp("walltile.bmp");
  int i =0;
}

Game::~Game(void)
{
  if(m_pPlayer != NULL) delete m_pPlayer;
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
  /*glEnable(GL_TEXTURE_2D);
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        glGenTextures(1, &m_uiTextureId);
        glBindTexture(GL_TEXTURE_2D, m_uiTextureId);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,     GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,     GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);*/
  //store our tiles real quick
  std::map<int,std::vector<Tile>> tempTiles = m_pGameMap.getTiles();
  for(std::map<int,std::vector<Tile>>::iterator it = tempTiles.begin(); it != tempTiles.end(); ++ it)
  {
    for(std::vector<Tile>::iterator it2 = it->second.begin(); it2 != it->second.end(); ++it2)
    {
      if(it2->isBlocked())
        glColor4fv(BLOCKED_TILE);
      else if (it2->isBlockingSight())
        glColor4fv(NOT_BLOCKED_TILE);
      else
        glColor4fv(NOT_BLOCKED_TILE);
      //what we drawing has to be character
      if(it2->isBlocked())
      {
        

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 256, 256, 0, GL_RGB,
               GL_UNSIGNED_BYTE, m_pucTextureArray.c_str());
        glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
        glBindTexture(GL_TEXTURE_2D, m_uiTextureId);
        glBegin( GL_QUADS );
          glTexCoord2d(0.0,1.0); glVertex3f(it2->getPosX()-7.5, it2->getPosY()+7.5, 0.0);
          glTexCoord2d(1.0,1.0); glVertex3f(it2->getPosX()+7.5, it2->getPosY()+7.5, 0.0);
          glTexCoord2d(1.0,0.0); glVertex3f(it2->getPosX()+7.5, it2->getPosY()-7.5, 0.0);
          glTexCoord2d(0.0,0.0); glVertex3f(it2->getPosX()-7.5, it2->getPosY()-7.5, 0.0);
        glEnd();
        
      }
      else
      {
       glBegin(GL_LINE_LOOP);
        glVertex3f(it2->getPosX()-7.5, it2->getPosY()+7.5, 0.0);
        glVertex3f(it2->getPosX()+7.5, it2->getPosY()+7.5, 0.0);
        glVertex3f(it2->getPosX()+7.5, it2->getPosY()-7.5, 0.0);
        glVertex3f(it2->getPosX()-7.5, it2->getPosY()-7.5, 0.0);
      glEnd();
      }
    }
  }
 // glDisable(GL_TEXTURE_2D);
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
  glutPostRedisplay();
  if (key == 27)
    exit(0);
}


//=======================================================================================
//=======================================================================================
void Game::loadTextureFromBmp (const char* szImageFileName)
{
  FILE *fpBmpFile;
  BITMAPFILEHEADER fileHeader;
  BITMAPINFOHEADER infoHeader;
  RGBTRIPLE rgb;

  // open the texture bitmap file and read the file and info headers
  fpBmpFile = fopen(szImageFileName, "rb");
  if (fpBmpFile == NULL)
  { 
    return;
  }

  fread(&fileHeader, sizeof(fileHeader), 1, fpBmpFile);
  if (fileHeader.bfType != 0x4D42)
  { // ensure no resource leak
    fclose(fpBmpFile);
    return;
  }

  fread(&infoHeader, sizeof(infoHeader), 1, fpBmpFile);
  unsigned int Width  = infoHeader.biWidth;
  unsigned int Height = infoHeader.biHeight;

  // read in the BMP image data
  fseek(fpBmpFile, fileHeader.bfOffBits, SEEK_SET);
  unsigned int j = 0;
  for (unsigned int i=0; i < (unsigned int)(Width * Height); i++)
  { fread(&rgb, sizeof(rgb), 1, fpBmpFile);  // read one rgb triplet at a time
    m_pucTextureArray+= rgb.rgbtRed;
    m_pucTextureArray+= rgb.rgbtGreen;
    m_pucTextureArray+= rgb.rgbtBlue;
    j+=3;
  }
  // close the texture file
  fclose(fpBmpFile);
}