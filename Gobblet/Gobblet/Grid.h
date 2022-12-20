#pragma once
#include "Tile.h"
#include "Gobblet.h"

class Grid
{
public:
	Grid();
	void render(sf::RenderWindow& t_window);
	void update(sf::Vector2i t_mousePos);
	void onMouseDown(sf::Vector2i t_click);
	void onMouseUp(sf::Vector2i t_click);
private:
	void processOpponentTurn();
	bool compareGobbletSizes(Tile* t_from, Tile* t_to);
	std::vector<Tile*> m_boardTiles;
	std::vector<Tile*> m_inventoryTiles;

	Tile* m_selectedTile;
	Gobblet* m_selectedGobblet;
};
