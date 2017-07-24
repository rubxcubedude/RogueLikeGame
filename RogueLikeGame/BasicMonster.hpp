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
    bool m_bJustAppeared;
    Fighter m_fEnemy;

};
#endif