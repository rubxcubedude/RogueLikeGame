#ifndef TILE_HPP
#define TILE_HPP
class Tile
{
  public:
    Tile (double x, double y, bool isBlocked=true, bool isBlockedSight=true);
    ~Tile (void);
    bool isBlocked (void);
    bool isBlockedSight (void);
    bool isDark (void);
    
    double  getPosX (void);
    double  getPosY (void);

    void setBlocked (bool b);
    void setIsBlockedSight (bool b);
    void setIsDark (bool b);

  private:
    double m_dPositionX;
    double m_dPositionY;
    bool m_bIsBlocked;
    bool m_bIsBlockedSight;
    bool m_bIsDark;
};

inline bool Tile::isBlocked (void)
{
  return m_bIsBlocked;
}

inline bool Tile::isBlockedSight (void)
{
  return m_bIsBlockedSight;
}


inline bool Tile::isDark (void)
{
  return m_bIsDark;
}

inline double Tile::getPosX (void)
{
  return m_dPositionX;

}

inline double Tile::getPosY (void)
{
  return m_dPositionY;

}


inline void Tile::setBlocked (bool b)
{
  m_bIsBlocked = b;
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