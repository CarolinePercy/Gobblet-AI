#pragma once
#include "Tile.h"
#include "Gobblet.h"

class Grid
{
public:
	Grid();
	void render(sf::RenderWindow& t_window);
private:
	std::vector<Tile*> m_boardTiles;
	std::vector<Tile*> m_inventoryTiles;
};
