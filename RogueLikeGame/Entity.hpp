#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <string>
class Entity{
  public:
    Entity (float x, float y, char c, const float color[4]);
    ~Entity (void);
    void move (int dx, int dy);
    float getX (void) const;
    float getY (void) const;
    char getChar (void) const;
		float* getColor (void) const;

    void setPos(float x, float y);
  protected:
    float m_dPosition_x;
    float m_dPosition_y;
    char  m_cDisplay_char;
    float m_afDisplay_color[4];
};

inline float Entity::getX (void) const
{
  return m_dPosition_x;
}

inline float Entity::getY (void) const
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

inline void Entity::setPos (float x, float y)
{
  m_dPosition_x = x;
  m_dPosition_y = y;
}

#endif