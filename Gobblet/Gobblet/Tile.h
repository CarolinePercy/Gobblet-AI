#pragma once
#include "Globals.h"

class Tile
{
public:
	Tile(sf::Vector2f t_position, sf::Vector2f t_size, bool t_onBoard);
	void render(sf::RenderWindow& t_window);
	bool isInside(sf::Vector2i t_click);
private:
	sf::RectangleShape m_tile;
	bool onBoard;
};
