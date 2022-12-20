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
	if (m_selectedGobblet != nullptr)
	{
		m_selectedGobblet->render(t_window);
	}
}

void Grid::update(sf::Vector2i t_mousePos)
{
	if (m_selectedGobblet != nullptr)
	{
		m_selectedGobblet->setPosition(sf::Vector2f(t_mousePos.x, t_mousePos.y));
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
	if (m_selectedTile != nullptr)
	{
		m_selectedGobblet = m_selectedTile->getCurrentGobblet();
		m_selectedTile->removeCurrentGobblet();
	}
}

void Grid::onMouseUp(sf::Vector2i t_click)
{
	m_selectedTile->setCurrentGobblet(m_selectedGobblet);
	m_selectedGobblet = nullptr;
	for (Tile* tile : m_boardTiles)
	{
		if (tile->isInside(t_click))
		{
			if (compareGobbletSizes(m_selectedTile, tile))
			{
				m_selectedTile->moveGobbletTo(tile);
			}
		}
	}

	m_selectedTile = nullptr;
}

bool Grid::compareGobbletSizes(Tile* t_from, Tile* t_to)
{
	Gobblet* fromGobblet = t_from->getCurrentGobblet();
	int fromSize = 0;
	if (fromGobblet != nullptr)
	{
		fromSize = fromGobblet->getSize();
	}

	Gobblet* toGobblet = t_to->getCurrentGobblet();
	int toSize = 0;
	if (toGobblet != nullptr)
	{
		toSize = toGobblet->getSize();
	}

	return fromSize > toSize;

	checkIfThreeIsInARow();
}

void Grid::checkIfThreeIsInARow()
{
	threeInRow.clear();

	VerticalCheck();
	HorizontalCheck();
	DiagonalCheck();
}

void Grid::DiagonalCheck()
{
	int numOfEnemy = 0;
	int numOfPlayer = 0;
	Gobblet* g;

	// Diagonal Check

	for (int j = 0; j < 4; j++)
	{
		g = m_boardTiles[(j * 5)]->getCurrentGobblet();

		if (g != nullptr)
		{
			if (g->isControlledByPlayer())
			{
				numOfPlayer++;
			}

			else
			{
				numOfEnemy++;
			}
		}
	}

	if (numOfPlayer >= 3 || numOfEnemy >= 3)
	{
		threeInRow.push_back(std::vector<int>{0, 5, 10, 15});
		std::cout << "Three in a row!: " << 0 << ", " << 5 << ", " << 10 << ", " << 15 << std::endl;
		// theres three in a row!
	}

	numOfEnemy = 0;
	numOfPlayer = 0;

	for (int j = 0; j < 4; j++)
	{
		g = m_boardTiles[((j + 1) * 3)]->getCurrentGobblet();

		if (g != nullptr)
		{
			if (g->isControlledByPlayer())
			{
				numOfPlayer++;
			}

			else
			{
				numOfEnemy++;
			}
		}
	}

	if (numOfPlayer >= 3 || numOfEnemy >= 3)
	{
		threeInRow.push_back(std::vector<int>{3, 6, 9, 12});
		std::cout << "Three in a row!: " << 3 << ", " << 6 + 1 << ", " << 9 << ", " << 12 << std::endl;
		// theres three in a row!
	}
}

void Grid::HorizontalCheck()
{
	int numOfEnemy = 0;
	int numOfPlayer = 0;
	Gobblet* g;

	// Horizontal Check
	for (int i = 0; i < 4; i++)
	{
		numOfEnemy = 0;
		numOfPlayer = 0;

		for (int j = 0; j < 4; j++)
		{
			g = m_boardTiles[(j * 4) + i]->getCurrentGobblet();

			if (g != nullptr)
			{
				if (g->isControlledByPlayer())
				{
					numOfPlayer++;
				}

				else
				{
					numOfEnemy++;
				}
			}
		}

		if (numOfPlayer >= 3 || numOfEnemy >= 3)
		{
			threeInRow.push_back(std::vector<int>
			{i, i + 4, i + 8, i + 12});
			// theres three in a row!

			std::cout << "Three in a row!: " << i << ", " << i + 4 << ", " << i + 8 << ", " << i + 12 << std::endl;
		}
	}
}

void Grid::VerticalCheck()
{
	int numOfEnemy = 0;
	int numOfPlayer = 0;
	Gobblet* g;

	// Vertical check
	for (int i = 0; i < 4; i++)
	{
		numOfEnemy = 0;
		numOfPlayer = 0;

		for (int j = 0; j < 4; j++)
		{
			g = m_boardTiles[(i * 4) + j]->getCurrentGobblet();

			if (g != nullptr)
			{
				if (g->isControlledByPlayer())
				{
					numOfPlayer++;
				}

				else
				{
					numOfEnemy++;
				}
			}
		}

		if (numOfPlayer >= 3 || numOfEnemy >= 3)
		{
			int temp = i * 4;

			threeInRow.push_back(std::vector<int>
			{temp, temp + 1, temp + 2, temp + 3});

			std::cout << "Three in a row!: " << temp << ", " << temp + 1 << ", " << temp + 2 <<", " << temp + 3 << std::endl;
			// theres three in a row!
		}
	}
}
