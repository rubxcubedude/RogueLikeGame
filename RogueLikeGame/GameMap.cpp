#include "GameMap.hpp"
#include "ColorConstants.hpp"
#include <time.h>

GameMap::GameMap()
{
  m_pCurrentState = PLAYER_TURN;
}

GameMap::~GameMap()
{
}

void GameMap::initialize(int max_rooms)
{
  m_nMapWidth = 976;
  m_nMapHeight = 751;
  m_pPlayer.init(32,25,'@', WHITEF);
  loadTextureFromBmp("walltile.bmp");
  for(int i = 0; i<m_nMapWidth/15.0; ++i)
  {
    for(int j = 0; j <m_nMapHeight/15.0; ++j)
    {
      m_mTiles[i][j].init(i*15, j*15);
    }
  }
  m_mTiles[m_pPlayer.getX()][m_pPlayer.getY()].addEntity(m_pPlayer);
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
  Room room1(m_pPlayer.getX()*15, m_pPlayer.getY()*15, room_min_size, room_min_size);
  create_room(room1 , false);
  m_vRooms[0] = room1;
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
      for(int i = 0; i< sizeof(m_vRooms); ++ i)
      {
        bool val = room2.intersect(m_vRooms[i]);
        intersect = intersect || val;
      }
      if(!intersect)
      {
        m_vRooms[count]=room2;
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

  for(int i = 0; i<m_nMapWidth/15.0; ++i)
  {
    for(int j = 0; j <m_nMapHeight/15.0; ++j)
    {
      for(int k =0; k <room.getWidth(); k++)
      {
        for(int l=0; l< room.getHeight(); l++)
        {
          if((room.getX()+(k*15) < m_mTiles[i][j].getPosX()+7.5 && room.getX() +(k*15) > m_mTiles[i][j].getPosX()-7.5) &&
            (room.getY()+(l*15) < m_mTiles[i][j].getPosY()+7.5 && room.getY()+(l*15) > m_mTiles[i][j].getPosY()-7.5))
          {
            m_mTiles[i][j].setIsWall(false);
            if(createNPC && monsterX == k && monsterY == l)
            {
              Entity t;
              t.init(i, j, 'T', YELLOWF); 
              m_mTiles[i][j].addEntity(t);
            }
          }
        }
      }
    }
  }
}


void GameMap::create_h_tunnel (int x1, int x2, int y)
{
  for(int i = 0; i<m_nMapWidth/15.0; ++i)
  {
    for(int j = 0; j <m_nMapHeight/15.0; ++j)
    {
      if(std::min(x1,x2) < m_mTiles[i][j].getPosX()+7.5 && std::max(x1,x2) > m_mTiles[i][j].getPosX()-7.5 &&
        (y < m_mTiles[i][j].getPosY()+7.5 && y > m_mTiles[i][j].getPosY()-7.5))
      {
        m_mTiles[i][j].setIsWall(false);
      }
    }
  }
}

void GameMap::create_v_tunnel (int y1, int y2, int x)
{
  for(int i = 0; i<m_nMapWidth/15.0; ++i)
  {
    for(int j = 0; j <m_nMapHeight/15.0; ++j)
    {
      if(std::min(y1,y2) < m_mTiles[i][j].getPosY()-7.5 && std::max(y1,y2) > m_mTiles[i][j].getPosY()-7.5 &&
        (x < m_mTiles[i][j].getPosX()+7.5 && x > m_mTiles[i][j].getPosX()-7.5))
      {
        m_mTiles[i][j].setIsWall(false);
      }
    }
  }
}

void GameMap::updateFOV()
{
  int x = m_pPlayer.getX();
  int y = m_pPlayer.getY();
  //first set everything dark
  for(int i = 0; i<m_nMapWidth/15.0; ++i)
  {
    for(int j = 0; j <m_nMapHeight/15.0; ++j)
    {  
        m_mTiles[i][j].setIsDark(true);
    }
  }

  //now light up area around player
  m_mTiles[x][y].setIsDark(false);
  m_mTiles[x][y].setIsBlockedSight(false);
  m_mTiles[x+1][y].setIsDark(false);
  m_mTiles[x+1][y].setIsBlockedSight(false);
  m_mTiles[x-1][y].setIsDark(false);
  m_mTiles[x-1][y].setIsBlockedSight(false);
  m_mTiles[x][y+1].setIsDark(false);
  m_mTiles[x][y+1].setIsBlockedSight(false);
  m_mTiles[x][y-1].setIsDark(false);
  m_mTiles[x][y-1].setIsBlockedSight(false);
  m_mTiles[x+1][y+1].setIsBlockedSight(false);
  m_mTiles[x+1][y+1].setIsDark(false);
  m_mTiles[x+1][y-1].setIsBlockedSight(false);
  m_mTiles[x+1][y-1].setIsDark(false);
  m_mTiles[x-1][y+1].setIsBlockedSight(false);
  m_mTiles[x-1][y+1].setIsDark(false);
  m_mTiles[x-1][y-1].setIsBlockedSight(false);
  m_mTiles[x-1][y-1].setIsDark(false);
}

void GameMap::draw(void)
{
  drawMap();
}

void GameMap::processState(void)
{
  int i= 0;
  if(m_pCurrentState != PLAYER_TURN)
    m_pCurrentState = PLAYER_TURN;
}

void GameMap::drawMap(void)
{ 
  for(int i = 0; i<m_nMapWidth/15.0; ++i)
  {
    for(int j = 0; j <m_nMapHeight/15.0; ++j)
    {
      m_mTiles[i][j].draw();
    }
  }
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

void GameMap::movePlayerUp (void)
{ 
  if(m_pCurrentState == PLAYER_TURN)
  {
    if(!m_mTiles[m_pPlayer.getX()][m_pPlayer.getY()+1].isBlocked())
    {
      m_pPlayer.move(0,1);
      m_mTiles[m_pPlayer.getX()][m_pPlayer.getY()].addEntity(m_pPlayer);
      m_mTiles[m_pPlayer.getX()][m_pPlayer.getY()-1].removeEntity();
    }
  }
  m_pCurrentState = NPC_TURN;
}

void GameMap::movePlayerDown (void)
{
  if(m_pCurrentState == PLAYER_TURN)
  {
    if(!m_mTiles[m_pPlayer.getX()][m_pPlayer.getY()-1].isBlocked())
    {
      m_pPlayer.move(0,-1);
      m_mTiles[m_pPlayer.getX()][m_pPlayer.getY()].addEntity(m_pPlayer);
      m_mTiles[m_pPlayer.getX()][m_pPlayer.getY()+1].removeEntity();
    }
  }
  m_pCurrentState = NPC_TURN;
}

void GameMap::movePlayerLeft (void)
{
  if(m_pCurrentState == PLAYER_TURN)
  {
    if(!m_mTiles[m_pPlayer.getX()-1][m_pPlayer.getY()].isBlocked())
    {
      m_pPlayer.move(-1,0);
      m_mTiles[m_pPlayer.getX()][m_pPlayer.getY()].addEntity(m_pPlayer);
      m_mTiles[m_pPlayer.getX()+1][m_pPlayer.getY()].removeEntity();
    }
  } 
  m_pCurrentState = NPC_TURN;
}

void GameMap::movePlayerRight (void)
{
  if(m_pCurrentState == PLAYER_TURN)
  {
    if(!m_mTiles[m_pPlayer.getX()+1][m_pPlayer.getY()].isBlocked())
    {
      m_pPlayer.move(1,0);
      m_mTiles[m_pPlayer.getX()][m_pPlayer.getY()].addEntity(m_pPlayer);
      m_mTiles[m_pPlayer.getX()-1][m_pPlayer.getY()].removeEntity();
    }
    m_pCurrentState = NPC_TURN;
  }
}