#pragma once
#include "Globals.h"

class Gobblet
{
public:
	Gobblet(int t_size, bool t_isPlayer);
	void render(sf::RenderWindow& t_window);

	Gobblet* getChild() { return m_child; }
	void setChild(Gobblet* t_child) { m_child = t_child;  };
	void setPosition(sf::Vector2f t_position) { m_gobblet.setPosition(t_position); }
private:
	sf::CircleShape m_gobblet;
	Gobblet* m_child;
	int size = -1;
};
