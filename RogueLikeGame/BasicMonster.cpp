#include "BasicMonster.hpp"


BasicMonster::BasicMonster():
  Fighter()
{
  m_bIsVisible =false;
  m_bJustAppeared = true;
}

BasicMonster::~BasicMonster()
{
}

void BasicMonster::takeTurn()
{
  if(m_bIsVisible && !m_bIsDead)
  {
    if(m_bJustAppeared)
      m_bJustAppeared = false; //give the player 1 turn to react
    else if(m_fEnemy.getX() == m_dPosition_x-1 && m_dPosition_y == m_fEnemy.getY()+1 ||
            m_fEnemy.getX() == m_dPosition_x+1 && m_dPosition_y == m_fEnemy.getY()+1 ||
            m_fEnemy.getX() == m_dPosition_x-1 && m_dPosition_y == m_fEnemy.getY()-1 ||
            m_fEnemy.getX() == m_dPosition_x+1 && m_dPosition_y == m_fEnemy.getY()-1)
      attack(m_fEnemy);/*
    else if(rand()%2 ==1)
      move(m_nEnemyPosX-m_dPosition_x, 0);
    else
      move(0, m_nEnemyPosY-m_dPosition_y);*/
  }
}


bool BasicMonster::inFOV(Fighter &f)
{
  if(f.getX() == m_dPosition_x-1 && m_dPosition_y == f.getY()+1 ||
     f.getX() == m_dPosition_x+1 && m_dPosition_y == f.getY()+1 ||
     f.getX() == m_dPosition_x-1 && m_dPosition_y == f.getY()-1 ||
     f.getX() == m_dPosition_x+1 && m_dPosition_y == f.getY()-1 ||
     f.getX() == m_dPosition_x && m_dPosition_y == f.getY()+1 ||
     f.getX() == m_dPosition_x && m_dPosition_y == f.getY()-1 ||
     f.getX() == m_dPosition_x-1 && m_dPosition_y == f.getY() ||
     f.getX() == m_dPosition_x+1 && m_dPosition_y == f.getY())
  {
    m_bIsVisible = true;
    m_fEnemy  = f;
  }

  return m_bIsVisible;
}