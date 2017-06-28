#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <string>
class Entity{
  public:
    Entity (float x, float y, char c, const float color[4]);
    ~Entity (void);
    void move (float dx, float dy);
    float getX (void) const;
    float getY (void) const;
    char getChar (void) const;
		float* getColor (void) const;
  protected:
    float position_x;
    float position_y;
    char  display_char;
    float display_color[4];
};

inline float Entity::getX (void) const
{
  return position_x;
}

inline float Entity::getY (void) const
{
  return position_y;
}

inline char Entity::getChar (void) const
{
  return display_char;
}

inline float* Entity::getColor (void) const
{
  return (float*)display_color;
}

#endif