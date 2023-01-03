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

		m_player1Tiles.push_back(tile);
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

		m_player2Tiles.push_back(tile);
		position.y -= size.y;
	}
}

void Grid::render(sf::RenderWindow& t_window)
{
	for (Tile* tile : m_boardTiles)
	{
		tile->render(t_window);
	}
	for (Tile* tile : m_player1Tiles)
	{
		tile->render(t_window);
	}
	for (Tile* tile : m_player2Tiles)
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
			if (tile->getCurrentGobblet() != nullptr)
			{
				if (tile->getCurrentGobblet()->isControlledByPlayer())
				{
					m_selectedTile = tile;
				}
			}
		}
	}
	for (Tile* tile : m_player1Tiles)
	{
		if(tile->isInside(t_click))
		{
			if (tile->getCurrentGobblet() != nullptr)
			{
				if (tile->getCurrentGobblet()->isControlledByPlayer())
				{
					m_selectedTile = tile;
				}
			}
		}
	}
	for (Tile* tile : m_player2Tiles)
	{
		if (tile->isInside(t_click))
		{
			if (tile->getCurrentGobblet() != nullptr)
			{
				if (tile->getCurrentGobblet()->isControlledByPlayer())
				{
					m_selectedTile = tile;
				}
			}
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
	if (m_selectedTile != nullptr)
	{
		m_selectedTile->setCurrentGobblet(m_selectedGobblet);
		m_selectedGobblet = nullptr;
	
		for (Tile* tile : m_boardTiles)
		{
			if (tile->isInside(t_click))
			{
				if (MovingFromInventory(m_selectedTile))
				{
					if (tile->getCurrentGobblet() != nullptr)
					{
						if (CheckIfThreeInARow(m_selectedTile, tile))
						{
							if (compareGobbletSizes(m_selectedTile, tile))
							{
								m_selectedTile->moveGobbletTo(tile);
								processOpponentTurn();
							}
						}
					}

					else
					{
						m_selectedTile->moveGobbletTo(tile);
						processOpponentTurn();
					}

				}
				else if (compareGobbletSizes(m_selectedTile, tile))
				{
					m_selectedTile->moveGobbletTo(tile);
					processOpponentTurn();
				}
			}
		}

		checkRows();

		m_selectedTile = nullptr;
	}
}

void Grid::processOpponentTurn()
{
	std::vector<Tile*> emptyTiles;
	for (Tile* tile : m_boardTiles)
	{
		if (tile->getCurrentGobblet() == nullptr)
		{
			emptyTiles.push_back(tile);
		}
	}
	if (emptyTiles.size() > 0)
	{
		std::random_device rd;
		std::mt19937 g(rd());
		std::shuffle(emptyTiles.begin(), emptyTiles.end(), g);
		m_player2Tiles.back()->moveGobbletTo(emptyTiles.back());
	}
	// minimax here
}

bool Grid::compareGobbletSizes(Tile* t_from, Tile* t_to)
{
	int fromSize = 0;
	int toSize = 0;

	if(t_from != nullptr)
	{ 
		Gobblet* fromGobblet = t_from->getCurrentGobblet();
		if (fromGobblet != nullptr)
		{
			fromSize = fromGobblet->getSize();
		}
	}

	if (t_from != nullptr)
	{
		Gobblet* toGobblet = t_to->getCurrentGobblet();
		if (toGobblet != nullptr)
		{
			toSize = toGobblet->getSize();
		}
	}

	return fromSize > toSize;
}

void Grid::checkRows()
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
		if (!DidAPlayerWin(numOfPlayer, numOfEnemy))
		{
			RowWasFound(0, 5, 10, 15);
			// theres three in a row!
		}
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
		if (!DidAPlayerWin(numOfPlayer, numOfEnemy))
		{
			RowWasFound(3, 6, 9, 12);
			// theres three in a row!
		}
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
			if (!DidAPlayerWin(numOfPlayer, numOfEnemy))
			{
				RowWasFound(i, i + 4, i + 8, i + 12);
				// theres three in a row!
			}
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
			if (!DidAPlayerWin(numOfPlayer, numOfEnemy))
			{
				int temp = i * 4;
				RowWasFound(temp, temp + 1, temp + 2, temp + 3);
			}

			// theres three in a row!
		}
	}
}

void Grid::RowWasFound(int in1, int in2, int in3, int in4)
{
	threeInRow.push_back(std::vector<int>{in1, in2, in3, in4});
	std::cout << "Three in a row!: " << in1 << ", " << in2 << ", " << in3 << ", " << in4 << std::endl;
}

bool Grid::DidAPlayerWin(int t_playerNum, int t_enemyNum)
{
	if (t_playerNum >= 4)
	{
		g_status = Status::Player1Wins;
		// Player1 wins!
	}

	else if (t_enemyNum >= 4)
	{
		g_status = Status::Player2Wins;
		// Player2 wins!
	}

	return false;
}

bool Grid::MovingFromInventory(Tile* t_from)
{
	return std::find(m_boardTiles.begin(), m_boardTiles.end(), t_from) == m_boardTiles.end();
}

bool Grid::CheckIfThreeInARow(Tile* t_from, Tile* t_to)
{
	bool t_Valid = false;
	bool inARow = false;

	std::vector<Tile*>::iterator itr = std::find(m_boardTiles.begin(), m_boardTiles.end(), t_from);

	int index = std::distance(m_boardTiles.begin(), itr);

	for (std::vector<int> t : threeInRow)
	{
		inARow = std::find(t.begin(), t.end(), index) == t.end();

		if (inARow)
		{
			break;
		}
	}

	if (inARow)
	{
		t_Valid = t_from->getCurrentGobblet()->isControlledByPlayer() !=
			t_to->getCurrentGobblet()->isControlledByPlayer();
	}

	return t_Valid;
}
