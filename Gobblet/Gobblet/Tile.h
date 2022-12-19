#pragma once
#include "Globals.h"
#include "Gobblet.h"

class Tile
{
public:
	Tile(sf::Vector2f t_position, sf::Vector2f t_size, bool t_onBoard);
	void render(sf::RenderWindow& t_window);
	bool isInside(sf::Vector2i t_click);

	void removeCurrentGobblet() { if (m_currentGobblet != nullptr) { m_currentGobblet = m_currentGobblet->getChild(); } }
	void setCurrentGobblet(Gobblet* t_currentGobblet);
	Gobblet* getCurrentGobblet() { return m_currentGobblet; }
	void moveGobbletTo(Tile* t_destination);
private:
	Gobblet* m_currentGobblet;
	sf::RectangleShape m_tile;
	bool onBoard;
};
