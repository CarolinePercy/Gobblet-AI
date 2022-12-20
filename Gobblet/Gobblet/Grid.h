#pragma once
#include "Tile.h"
#include "Gobblet.h"

class Grid
{
public:
	Grid();
	void render(sf::RenderWindow& t_window);
	void onMouseDown(sf::Vector2i t_click);
	void onMouseUp(sf::Vector2i t_click);
private:
	bool compareGobbletSizes(Tile* t_from, Tile* t_to);
	std::vector<Tile*> m_boardTiles;
	std::vector<Tile*> m_inventoryTiles;

	sf::Vector2i mousePos;
	Tile* m_selectedTile;
};
