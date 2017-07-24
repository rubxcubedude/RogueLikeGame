#ifndef TILE_HPP
#define TILE_HPP
#include "ColorConstants.hpp"
#include "gl\freeglut.h"
class Tile
{
  public:
    Tile (bool m_bIsWall = true, bool isBlocked=true, bool isBlockedSight=true);
    ~Tile (void);

    void init(double x, double y);
    void draw (void);

    double  getPosX (void);
    double  getPosY (void);

    bool isBlocked (void);

    void setBlocked (bool b);
    void setIsBlockedSight (bool b);
    void setIsDark (bool b);
    void setIsWall (bool b);

  private:
    double m_dPositionX;
    double m_dPositionY;
    bool m_bIsBlocked;
    bool m_bIsBlockedSight;
    bool m_bIsDark;
    bool m_bIsWall;
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
  return m_bIsWall;
}

inline void Tile::setBlocked (bool b)
{
  m_bIsBlocked = b;
}


inline void Tile::setIsWall (bool b)
{
  m_bIsWall = b;
}


inline void Tile::setIsBlockedSight (bool b)
{
  m_bIsBlockedSight = b;
}


inline void Tile::setIsDark (bool b)
{
  m_bIsDark = b;
}
#endif