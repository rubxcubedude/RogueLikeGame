#ifndef FIGHTER_HPP
#define FIGHTER_HPP
#include "Entity.hpp"
class Fighter: public Entity
{
  public:
    Fighter();
    ~Fighter();

    void initFighter(int maxHp, int defense, int power);
    void takeDmg(int amount);
    void attack(Fighter &f);
    int getDefense(void);
    bool isAlive (void);
  protected:
    bool m_bIsDead;

  private:
    int m_nMaxHp;
    int m_nCurrentHp;
    int m_nDefense;
    int m_nPower;
    
};

inline int Fighter::getDefense(void)
{
  return m_nDefense;
}

inline bool Fighter::isAlive(void)
{
  return !m_bIsDead;
}
#endif