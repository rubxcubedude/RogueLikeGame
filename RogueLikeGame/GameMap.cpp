#include "GameMap.hpp"
#include <time.h>
GameMap::GameMap()
{
}

GameMap::~GameMap()
{
}

void GameMap::initialize(int width, int height, Player* p, int max_rooms, int room_min_size, int room_max_size)
{
  m_nMapHeight = height;
  m_nMapWidth = width;
  for(int i = 0; i<width/15.0; ++i)
  {
    std::vector<Tile> vTiles;
    for(int j = 0; j <height/15.0; ++j)
    {
        vTiles.push_back(Tile(i*15,j*15, true));
    }
    m_mTiles.insert(make_pair(i, vTiles));
  }
  time_t seconds;
  time(&seconds);
  srand((unsigned int) seconds);

  //we always create 1 minimally sized room in middle of the map
  Room room1(p->getX(), p->getY(), room_min_size, room_min_size);
  create_room(room1);
  m_vRooms.push_back(room1);
  int count = 1;
  while(count < max_rooms)
  {
    Room room2(rand()%width,rand()%height,rand()%(room_max_size-room_min_size)+room_min_size,rand()%(room_max_size-room_min_size)+room_min_size);
    if(room2.getX() > 15 && room2.getY() > 15  
       && (room2.getX()+room2.getX()*room2.getWidth()) < (width - 15) && (room2.getY()+room2.getY()*room2.getHeight()) < (height - 15))
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

void GameMap::create_room(Room room)
{
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