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
			m_tiles.push_back(new Tile(position, size, true));
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
		m_tiles.push_back(new Tile(position, size, false));
		position.y += size.y;
	}

	//right player
	position.x = 1280 - 10;
	position.y = 720 - 10;
	position -= size;
	for (int i = 0; i < 3; i++)
	{
		m_tiles.push_back(new Tile(position, size, false));
		position.y -= size.y;
	}
}

void Grid::render(sf::RenderWindow& t_window)
{
	for (Tile* tile : m_tiles)
	{
		tile->render(t_window);
	}
}
