#ifndef TILE_HPP
#define TILE_HPP
#include "Entity.hpp"
#include "ColorConstants.hpp"
#include "gl\freeglut.h"
class Tile
{
  public:
    Tile (bool isBlocked=true, bool isBlockedSight=true);
    ~Tile (void);

    void init(double x, double y);
    void draw (void);
    void addEntity(Entity t);
    void removeEntity (void);

    double  getPosX (void);
    double  getPosY (void);

    bool isBlocked (void);

    void setBlocked (bool b);
    void setIsBlockedSight (bool b);
    void setIsDark (bool b);

  private:
    double m_dPositionX;
    double m_dPositionY;
    bool m_bIsBlocked;
    bool m_bIsBlockedSight;
    bool m_bIsDark;
    bool m_bHasEntity;
    Entity m_pEntity;
};

inline double Tile::getPosX (void)
{
  return m_dPositionX;

}

inline double Tile::getPosY (void)
{
  return m_dPositionY;

}

inline bool Tile::isBlocked (void)
{
  return m_bIsBlocked;
}

inline void Tile::setBlocked (bool b)
{
  m_bIsBlocked = b;
}


inline void Tile::setIsBlockedSight (bool b)
{
  m_bIsBlockedSight = b;
  if(!b)
    m_pEntity.setIsVisible(true);
}


inline void Tile::setIsDark (bool b)
{
  m_bIsDark = b;
}
#endif