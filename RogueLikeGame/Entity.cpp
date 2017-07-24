#include "Entity.hpp"

Entity::Entity()
{
  m_bIsVisible = false;
}

Entity::~Entity()
{
}

void Entity::move(int dx, int dy)
{
  m_dPosition_x += dx;
  m_dPosition_y += dy;
}


void Entity::init(int x, int y, char c, const float color[4])
{
  m_dPosition_x = x;
  m_dPosition_y = y;
  m_cDisplay_char = c;
  memcpy(m_afDisplay_color, color, sizeof(m_afDisplay_color));
}


void Entity::draw()
{
  glColor4fv(m_afDisplay_color);
  glRasterPos2d(m_dPosition_x*15-5,m_dPosition_y*15-2.5);
    //what we drawing has to be character
  if(m_bIsVisible)
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, m_cDisplay_char);
}