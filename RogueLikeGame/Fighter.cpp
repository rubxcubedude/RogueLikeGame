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