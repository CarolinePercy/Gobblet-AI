#include "Grid.h"

Grid::Grid() : m_selectedTile(nullptr)
{
	sf::Vector2f position;
	sf::Vector2f size;

	//main grid
	size.x = (G_VIEW_HEIGHT - 20) / 4.0f;
	size.y = size.x;
	position.x = (G_VIEW_WIDTH - G_VIEW_HEIGHT) / 2;
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
		Tile* tile = new Tile(position, size, false);
		for (int i = 1; i <= 4; i++)
		{
			Gobblet* gobble = new Gobblet(i, true);
			tile->setCurrentGobblet(gobble);
		}

		m_inventoryTiles.push_back(tile);
		position.y += size.y;
	}

	//right player
	position.x = G_VIEW_WIDTH - 10;
	position.y = G_VIEW_HEIGHT - 10;
	position -= size;
	for (int i = 0; i < 3; i++)
	{
		Tile* tile = new Tile(position, size, false);
		for (int i = 1; i <= 4; i++)
		{
			Gobblet* gobble = new Gobblet(i, false);
			tile->setCurrentGobblet(gobble);
		}

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

void Grid::onMouseDown(sf::Vector2i t_click)
{
	for (Tile* tile : m_boardTiles)
	{
		if (tile->isInside(t_click))
		{
			m_selectedTile = tile;
		}
	}
	for (Tile* tile : m_inventoryTiles)
	{
		if(tile->isInside(t_click))
		{
			m_selectedTile = tile;
		}
	}
}

void Grid::onMouseUp(sf::Vector2i t_click)
{
	for (Tile* tile : m_boardTiles)
	{
		if (tile->isInside(t_click))
		{
			m_selectedTile->moveGobbletTo(tile);
		}
	}
	for (Tile* tile : m_inventoryTiles)
	{
		if (tile->isInside(t_click))
		{

		}
	}
	m_selectedTile = nullptr;
}
