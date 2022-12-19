#include "Grid.h"

Grid::Grid()
{
	sf::Vector2f position;
	sf::Vector2f size;

	//main grid
	size.x = (720 - 20) / 4.0f;
	size.y = size.x;
	position.x = (1280 - 720) / 2;
	position.y = 10;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			m_boardTiles.push_back(new Tile(position, size, true));
			position.y += size.y;
		}
		position.y = 10;
		position.x += size.x;
	}
	
	//left player
	position.x = 10;
	position.y = 10;
	for (int i = 0; i < 3; i++)
	{
		Gobblet* gobble1 = new Gobblet(1, true);
		Gobblet* gobble2 = new Gobblet(2, true);
		gobble2->setChild(gobble1);
		Gobblet* gobble3 = new Gobblet(3, true);
		gobble2->setChild(gobble2);
		Gobblet* gobble4 = new Gobblet(4, true);
		gobble2->setChild(gobble3);

		Tile* tile = new Tile(position, size, false);
		tile->setCurrentGobblet(gobble4);
		m_inventoryTiles.push_back(tile);
		position.y += size.y;
	}

	//right player
	position.x = 1280 - 10;
	position.y = 720 - 10;
	position -= size;
	for (int i = 0; i < 3; i++)
	{
		Gobblet* gobble1 = new Gobblet(1, false);
		Gobblet* gobble2 = new Gobblet(2, false);
		gobble2->setChild(gobble1);
		Gobblet* gobble3 = new Gobblet(3, false);
		gobble2->setChild(gobble2);
		Gobblet* gobble4 = new Gobblet(4, false);
		gobble2->setChild(gobble3);

		Tile* tile = new Tile(position, size, false);
		tile->setCurrentGobblet(gobble4);
		m_inventoryTiles.push_back(tile);
		position.y -= size.y;
	}
}

void Grid::render(sf::RenderWindow& t_window)
{
	for (Tile* tile : m_boardTiles)
	{
		tile->render(t_window);
	}
	for (Tile* tile : m_inventoryTiles)
	{
		tile->render(t_window);
	}
}
