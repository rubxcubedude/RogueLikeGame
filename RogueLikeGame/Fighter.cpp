#include "Fighter.hpp"


Fighter::Fighter():
  Entity()
{
  m_bIsDead= false;
  //m_bIsVisible = true;
}

Fighter::~Fighter()
{
}

void Fighter::initFighter(int maxHp, int defense, int power)
{
  m_nMaxHp = maxHp;
  m_nCurrentHp = maxHp;
  m_nDefense = defense;
  m_nPower = power;
}

void Fighter::takeDmg(int amount)
{
  m_nCurrentHp = m_nCurrentHp - amount;
  if(m_nCurrentHp <=0)
  {
    m_bIsDead = true;
    m_bIsVisible = false;
  }
}

void Fighter::attack(Fighter &f)
{
  int damage = m_nPower - f.getDefense();
  if(damage >0)
    f.takeDmg(damage);
}

void Fighter::draw()
{
  glColor4fv(m_afDisplay_color);
  glRasterPos2d(m_dPosition_x*15-5,m_dPosition_y*15-2.5);
    //what we drawing has to be character
  if(m_bIsVisible && !m_bIsDead)
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, m_cDisplay_char);
}