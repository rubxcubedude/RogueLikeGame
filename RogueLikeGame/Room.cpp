#include "Room.hpp"


Room::Room()
{
}

Room::Room(int x, int y, int w, int h)
{
  m_nX = x;
  m_nY = y;
  m_nWidth = w;
  m_nHeight = h;
}

Room::~Room()
{
}

void Room::init(int x, int y, int w, int h)
{
  m_nX = x;
  m_nY = y;
  m_nWidth = w;
  m_nHeight = h;
}


bool Room::intersect(Room room)
{
  return (m_nX <= room.getX()+(15*room.getWidth()) && m_nX+(15*m_nWidth) >= room.getX() &&
          m_nY <= room.getY()+(15*room.getHeight()) && m_nX+(15*m_nHeight) >= room.getY());
}

int Room::getCenterX()
{
  return (m_nX+m_nX+(15*m_nWidth))/2;
}


int Room::getCenterY()
{
  return (m_nY+m_nY+(15*m_nWidth))/2;
}