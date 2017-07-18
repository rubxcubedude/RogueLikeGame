#ifndef ENTITY_HPP
#define ENTITY_HPP
#include "gl\freeglut.h"

#include <string>
class Entity{
  public:
    Entity ();
    ~Entity (void);

    void init(int x, int y, char c, const float color[4]);
    void move (int dx, int dy);
    void draw (void);

    int getX (void) const;
    int getY (void) const;
    char getChar (void) const;
		float* getColor (void) const;
    bool isVisible (void) const;

    void setPos(int x, int y);
    void setIsVisible (bool b);

  protected:
    int m_dPosition_x;
    int m_dPosition_y;
    char  m_cDisplay_char;
    float m_afDisplay_color[4];
    bool m_bIsVisible;
};

inline int Entity::getX (void) const
{
  return m_dPosition_x;
}

inline int Entity::getY (void) const
{
  return m_dPosition_y;
}

inline char Entity::getChar (void) const
{
  return m_cDisplay_char;
}

inline float* Entity::getColor (void) const
{
  return (float*)m_afDisplay_color;
}

inline void Entity::setPos (int x, int y)
{
  m_dPosition_x = x;
  m_dPosition_y = y;
}


inline void Entity::setIsVisible (bool b)
{
  m_bIsVisible = b;
}


inline bool Entity::isVisible(void) const
{
  return m_bIsVisible;
}

#endif