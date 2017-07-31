#ifndef FIGHTER_HPP
#define FIGHTER_HPP
#include "Entity.hpp"
class Fighter: public Entity
{
  public:
    Fighter();
    ~Fighter();

    void draw (void);

    void initFighter(int maxHp, int defense, int power);
    void takeDmg(int amount);
    void attack(Fighter &f);
    int getDefense(void);
    int getHP(void);
    int getMaxHp(void);
    bool isAlive (void);
    std::string getName(void);
  protected:
    bool m_bIsDead;
    std::string m_strName;
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

inline std::string Fighter::getName(void)
{
  return m_strName;
}

inline int Fighter::getHP(void)
{
  return m_nCurrentHp;
}

inline int Fighter::getMaxHp(void)
{
  return m_nMaxHp;
}

inline bool Fighter::isAlive(void)
{
  return !m_bIsDead;
}
#endif