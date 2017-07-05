#ifndef ROOM_HPP
#define ROOM_HPP

class Room{
  public:
    Room(int x, int y, int w, int h);
    ~Room();
    bool intersect(Room room);
    int getCenterX();
    int getCenterY();
    int getX();
    int getY();
    int getWidth();
    int getHeight();

  private:
    int m_nX;
    int m_nY;
    int m_nWidth;
    int m_nHeight;
};


inline int Room::getX() { return m_nX;}
inline int Room::getY() { return m_nY;}
inline int Room::getWidth() { return m_nWidth;}
inline int Room::getHeight() { return m_nHeight;}
#endif