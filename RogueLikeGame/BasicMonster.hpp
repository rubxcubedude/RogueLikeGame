#ifndef BASIC_MONSTER_HPP
#define BASIC_MONSTER_HPP
#include "Fighter.hpp"
class BasicMonster: public Fighter
{
  public:
    BasicMonster();
    ~BasicMonster();

    bool inFOV(Fighter &f);
    void takeTurn (void);

  private:
    int m_nEnemyPosX;
    int m_nEnemyPosY;
    bool m_bJustAppeared;
    Fighter m_fEnemy;

};
#endif