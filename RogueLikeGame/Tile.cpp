#include "Tile.hpp"

Tile::Tile(bool isBlocked, bool isBlockedSight)
{
  m_bIsBlocked = isBlocked;
  m_bIsBlockedSight = isBlockedSight;
  m_bHasEntity = false;
}

Tile::~Tile()
{
}


void Tile::init(double x, double y)
{
  m_dPositionX = x;
  m_dPositionY = y;
}


void Tile::addEntity(Entity t)
{
  m_pEntity = t;
  m_bHasEntity = true;
}

void Tile::removeEntity()
{
  m_bHasEntity = false;
}

void Tile::draw()
{
  if (m_bIsBlockedSight)
    glColor4fv(BLACKF);
  else if(m_bIsBlocked && m_bIsDark)
    glColor4fv(DARK_WALL);
  else if(m_bIsBlocked )
    glColor4fv(BLOCKED_TILE);
  else if(m_bIsDark)
    glColor4fv(DARK_GROUND);
  else
    glColor4fv(NOT_BLOCKED_TILE);
  //what we drawing has to be character
  glBegin( GL_QUADS );
    glTexCoord2d(0.0,1.0); glVertex3f(m_dPositionX-7.5, m_dPositionY+7.5, 0.0);
    glTexCoord2d(1.0,1.0); glVertex3f(m_dPositionX+7.5, m_dPositionY+7.5, 0.0);
    glTexCoord2d(1.0,0.0); glVertex3f(m_dPositionX+7.5, m_dPositionY-7.5, 0.0);
    glTexCoord2d(0.0,0.0); glVertex3f(m_dPositionX-7.5, m_dPositionY-7.5, 0.0);
  glEnd();

  if(m_bHasEntity)
  {
    glColor4fv(YELLOWF);
    m_pEntity.draw();
  }
}