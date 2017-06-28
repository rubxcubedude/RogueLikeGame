#ifndef TILE_HPP
#define TILE_HPP
class Tile
{
  public:
    Tile (double x, double y, bool isBlocked=false, bool isBlockingSight=false);
    ~Tile (void);
    bool isBlocked (void);
    bool isBlockingSight (void);
    double  getPosX (void);
    double  getPosY (void);

  private:
    double m_dPositionX;
    double m_dPositionY;
    bool m_bIsBlocked;
    bool m_bIsBlockingSight;
};

inline bool Tile::isBlocked (void)
{
  return m_bIsBlocked;
}

inline bool Tile::isBlockingSight (void)
{
  return m_bIsBlockingSight;
}

inline double Tile::getPosX (void)
{
  return m_dPositionX;

}

inline double Tile::getPosY (void)
{
  return m_dPositionY;

}
#endif