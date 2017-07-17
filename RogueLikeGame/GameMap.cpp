#include "GameMap.hpp"
#include "ColorConstants.hpp"
#include <time.h>

GameMap::GameMap()
{
}

GameMap::~GameMap()
{
}

void GameMap::initialize(int width, int height, Player* p, int max_rooms)
{
  m_nMapHeight = height;
  m_nMapWidth = width;
  m_pPlayer = p;
  m_vEntities.clear();
  m_vEntities.push_back(m_pPlayer);
  loadTextureFromBmp("walltile.bmp");
  for(int i = 0; i<width/15.0; ++i)
  {
    std::vector<Tile> vTiles;
    for(int j = 0; j <height/15.0; ++j)
    {
        vTiles.push_back(Tile(i*15,j*15));
    }
    m_mTiles.insert(make_pair(i, vTiles));
  }
  
  createDungeon(max_rooms);
}

void GameMap::createDungeon(int max_rooms)
{
  time_t seconds;
  time(&seconds);
  srand((unsigned int) seconds);

  int room_min_size = 3;
  int room_max_size = 5;

  //we always create 1 minimally sized room in middle of the map
  Room room1(m_pPlayer->getX(), m_pPlayer->getY(), room_min_size, room_min_size);
  create_room(room1 , false);
  m_vRooms.push_back(room1);
  int count = 1;
  while(count < max_rooms)
  {
    int x = 15 + int(rand())%(m_nMapWidth/15)*15;
    int y = 15 + int(rand())%(m_nMapHeight/15)*15;
    

    Room room2(x, y, int(rand())%(room_max_size-room_min_size)+room_min_size, int(rand())%(room_max_size-room_min_size)+room_min_size);
    int width2 = room2.getX()+15*room2.getWidth();
    int height2 = room2.getY()+15*room2.getHeight();

    if( width2 < (m_nMapWidth - 15) && height2 < (m_nMapHeight - 15))
    {
      bool intersect = false;
      for(std::vector<Room>::iterator it= m_vRooms.begin(); it != m_vRooms.end(); ++ it)
      {
        bool val = room2.intersect(*it);
        intersect = intersect || val;
      }
      if(!intersect)
      {
        m_vRooms.push_back(room2);
        create_room(room2);
        count ++;
        if(rand()%2 == 1)
        {
          create_h_tunnel(room1.getX(), room2.getX(), room1.getY());
          create_v_tunnel(room1.getY(), room2.getY(), room2.getX());
        }
        else
        {
          create_v_tunnel(room1.getY(), room2.getY(), room1.getX());
          create_h_tunnel(room1.getX(), room2.getX(), room2.getY());   
        }
      }
    }   
  }
}

void GameMap::create_room(Room room, bool createNPC)
{
  int monsterX = rand() % room.getWidth();
  int monsterY = rand() % room.getHeight();

  for(std::map<int,std::vector<Tile>>::iterator it = m_mTiles.begin(); it != m_mTiles.end(); ++ it)
  {
    for(std::vector<Tile>::iterator it2 = it->second.begin(); it2 != it->second.end(); ++it2)
    {
      for(int i =0; i <room.getWidth(); i++)
      {
        for(int j=0; j< room.getHeight(); j++)
        {
          if((room.getX()+(i*15) < it2->getPosX()+7.5 && room.getX() +(i*15) > it2->getPosX()-7.5) &&
            (room.getY()+(j*15) < it2->getPosY()+7.5 && room.getY()+(j*15) > it2->getPosY()-7.5))
          {
            it2->setBlocked(false);
            if(createNPC && monsterX == i && monsterY == j)
            {
              Entity* t = new Entity(room.getX()+(i*15), room.getY()+(j*15), 'T', YELLOWF); 
              m_vEntities.push_back(t);
            }
          }
        }
      }
    }
  }

  
}


void GameMap::create_h_tunnel (int x1, int x2, int y)
{
  for(std::map<int,std::vector<Tile>>::iterator it = m_mTiles.begin(); it != m_mTiles.end(); ++ it)
  {
    for(std::vector<Tile>::iterator it2 = it->second.begin(); it2 != it->second.end(); ++it2)
    {
      if(std::min(x1,x2) < it2->getPosX()+7.5 && std::max(x1,x2) > it2->getPosX()-7.5 &&
        (y < it2->getPosY()+7.5 && y > it2->getPosY()-7.5))
      {
        it2->setBlocked(false);
      }
    }
  }
}

void GameMap::create_v_tunnel (int y1, int y2, int x)
{
  for(std::map<int,std::vector<Tile>>::iterator it = m_mTiles.begin(); it != m_mTiles.end(); ++ it)
  {
    for(std::vector<Tile>::iterator it2 = it->second.begin(); it2 != it->second.end(); ++it2)
    {
      if(std::min(y1,y2) < it2->getPosY()-7.5 && std::max(y1,y2) > it2->getPosY()-7.5 &&
        (x < it2->getPosX()+7.5 && x > it2->getPosX()-7.5))
      {
        it2->setBlocked(false);
      }
    }
  }
}

void GameMap::updateFOV()
{
  float x = m_pPlayer->getX();
  float y = m_pPlayer->getY();
  for(std::map<int,std::vector<Tile>>::iterator it = m_mTiles.begin(); it != m_mTiles.end(); ++ it)
  {
    for(std::vector<Tile>::iterator it2 = it->second.begin(); it2 != it->second.end(); ++it2)
    {   
      if( x < it2->getPosX()+20 && x > it2->getPosX()-30 &&
          y < it2->getPosY()+20 && y > it2->getPosY()-20)
      {  
        it2->setIsBlockedSight(false);
        it2->setIsDark(false);
      }
      else
        it2->setIsDark(true);
    }
  }
  for(std::vector<Entity*>::iterator it = m_vEntities.begin(); it != m_vEntities.end(); ++ it)
  {
    if( x < (*it)->getX()+20 && x > (*it)->getX()-30 &&
          y < (*it)->getY()+20 && y > (*it)->getY()-20)
      {  
        (*it)->setIsVisible(true);
      }
  }

}

void GameMap::draw(void)
{
  drawMap();
  drawAllEntities();
}

void GameMap::drawMap(void)
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
  for(std::map<int,std::vector<Tile>>::iterator it = m_mTiles.begin(); it != m_mTiles.end(); ++ it)
  {
    for(std::vector<Tile>::iterator it2 = it->second.begin(); it2 != it->second.end(); ++it2)
    {
      if (it2->isBlockedSight())
        glColor4fv(BLACKF);
      else if(it2->isBlocked() && !it2->isDark())
        glColor4fv(BLOCKED_TILE);
      else if(it2->isBlocked() )
        glColor4fv(DARK_WALL);
      else if(it2->isDark())
        glColor4fv(DARK_GROUND);
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
       glBegin(GL_QUADS);
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

//=======================================================================================
//=======================================================================================
void GameMap::loadTextureFromBmp (const char* szImageFileName)
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


void GameMap::drawAllEntities()
{
  for(std::vector<Entity*>::iterator it= m_vEntities.begin(); it != m_vEntities.end(); ++it)
  {
    //set position to draw
		glColor4fv((*it)->getColor());
    glRasterPos2d((*it)->getX(),(*it)->getY());
    //what we drawing has to be character
    if((*it)->isVisible())
      glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, (*it)->getChar());
  }
}