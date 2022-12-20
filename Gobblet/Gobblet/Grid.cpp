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
			if (tile->getCurrentGobblet()->getIsPlayer())
			{
				m_selectedTile = tile;
			}
		}
	}
	for (Tile* tile : m_player1Tiles)
	{
		if(tile->isInside(t_click))
		{
			if (tile->getCurrentGobblet()->getIsPlayer())
			{
				m_selectedTile = tile;
			}
		}
	}
	for (Tile* tile : m_player2Tiles)
	{
		if (tile->isInside(t_click))
		{
			if (tile->getCurrentGobblet()->getIsPlayer())
			{
				m_selectedTile = tile;
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
	}
	for (Tile* tile : m_boardTiles)
	{
		if (tile->isInside(t_click))
		{
			if (compareGobbletSizes(m_selectedTile, tile))
			{
				m_selectedTile->moveGobbletTo(tile);
				processOpponentTurn();
			}
		}
	}
	m_selectedTile = nullptr;
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
	// placeholder minimax test
	int bestMoveScore = INT_MIN;
	int bestMove = 1;

	for (int i = 1; i <= 10; i++)
	{
		if (i == 9)
		{
			int j = 0;
		}
		int moveScore = minimax(0 + i, 0, false);
		if (moveScore > bestMoveScore)
		{
			bestMoveScore = moveScore;
			bestMove = i;
		}
	}
	std::cout << "best move is to add " << bestMove << std::endl;
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

/// <summary>
/// minimax template, currently has AI aiming for 20 while opponent wants -20, value can change by up to an amount, stops if depth hits 20
/// </summary>
/// <param name="board"></param>
/// <param name="depth"></param>
/// <param name="AITurn"></param>
/// <returns></returns>
int Grid::minimax(int board, int depth, bool AITurn)
{
	int maxDepth = 5;
	// check for win or tie
	if (board >= 20)
	{
		return maxDepth - depth;
	}
	else if (board <= -20)
	{
		return -depth;
	}
	else if (depth > maxDepth)
	{
		return 0;
	}

	// if AIs turn, loop throug Ais moves
	if (AITurn == true)
	{
		int bestVal = INT_MIN;
		for (int i = 1; i <= 10; i++)
		{
			int value = minimax(board + i, depth + 1, !AITurn);
			bestVal = std::max(bestVal, value);
		}
		return bestVal;
	}
	// if Players turn, loop throug Players moves
	else
	{
		int bestVal = INT_MAX;
		for (int i = 5; i >= 1; i--)
		{
			int value = minimax(board - i, depth + 1, !AITurn);
			bestVal = std::min(bestVal, value);
		}
		return bestVal;
	}
}
