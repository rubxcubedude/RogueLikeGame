#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <string>
class Entity{
	public:
		Entity (float x, float y, char c, std::string color);
		~Entity (void);
		void move (float dx, float dy);
		float getX (void) const;
		float getY (void) const;
		char getChar (void) const;
	private:
		float position_x;
		float position_y;
		char  display_char;
		std::string display_color;
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

#endif