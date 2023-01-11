#pragma once
#include "Globals.h"
#include "Gobblet.h"

/// <summary>
/// Is one cell on the Grid class.
/// </summary>

class Tile
{
public:
	Tile(sf::Vector2f t_position, sf::Vector2f t_size);
	void render(sf::RenderWindow& t_window);
	bool isInside(sf::Vector2i t_click);

	void removeCurrentGobblet() { if (m_currentGobblet != nullptr) { m_currentGobblet = m_currentGobblet->getChild(); } }
	void setCurrentGobblet(Gobblet* t_currentGobblet);
	Gobblet* getCurrentGobblet() { return m_currentGobblet; }
	void moveGobbletTo(Tile* t_destination);

	sf::Vector2f getPosition();
	sf::Vector2f getOffsetPosition();
private:

	/// The Gobblet that is currently on top of this Tile.
	Gobblet* m_currentGobblet;

	/// The appearance of the Tile object.
	sf::RectangleShape m_tile;
};
