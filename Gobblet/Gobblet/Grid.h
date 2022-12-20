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
	bool compareGobbletSizes(Tile* t_from, Tile* t_to);
	std::vector<Tile*> m_boardTiles;
	std::vector<Tile*> m_inventoryTiles;

	Tile* m_selectedTile;
	Gobblet* m_selectedGobblet;


	sf::Vector2i mousePos;

	std::vector<std::vector<int>> threeInRow;

	
	void checkRows();

	void DiagonalCheck();
	void HorizontalCheck();
	void VerticalCheck();

	void RowWasFound(int in1, int in2, int in3, int in4);
	bool DidAPlayerWin(int t_playerNum, int t_enemyNum);

};
