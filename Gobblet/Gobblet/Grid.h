#pragma once
#include "Tile.h"

class Grid
{
public:
	Grid();
	void render(sf::RenderWindow& t_window);
private:
	std::vector<Tile*> m_tiles;
};
