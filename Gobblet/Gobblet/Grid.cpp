#include "Grid.h"

/// <summary>
/// Default constructor. Initialises the layout of the Grid, and the Gobblet pieces for the Player and AI.
/// </summary>
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
			m_boardTiles.push_back(new Tile(position, size));
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
		Tile* tile = new Tile(position, size);
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
		Tile* tile = new Tile(position, size);
		for (int i = 1; i <= 4; i++)
		{
			Gobblet* gobble = new Gobblet(i, false);
			tile->setCurrentGobblet(gobble);
		}

		m_player2Tiles.push_back(tile);
		position.y -= size.y;
	}
}

/// <summary>
/// Resets the board back to it's original state, with all pieces going back to the players' inventories.
/// </summary>
void Grid::resetBoard()
{
	std::vector<Gobblet*> player1Gobblets;
	std::vector<Gobblet*> player2Gobblets;
	Gobblet* g;

	for (Tile* tile : m_boardTiles)
	{
		g = tile->getCurrentGobblet();
		if (g != nullptr)
		{
			getChildGobbletsOut(g, &player1Gobblets, &player2Gobblets);

			if (g->isControlledByPlayer())
			{
				player1Gobblets.push_back(g);
			}

			else
			{
				player2Gobblets.push_back(g);
			}

			tile->removeCurrentGobblet();
		}
	}

	resetPlayerTiles(m_player1Tiles, player1Gobblets);
	resetPlayerTiles(m_player2Tiles, player2Gobblets);

}

/// <summary>
/// Puts the gobblets collected from the board back into the player's inventory. Is called for both the user and AI's inventory.
/// </summary>
/// <param name="t_player">The tiles of the player's inventory.</param>
/// <param name="t_playerGobblets">The Gobblets that belong to this player.</param>
void Grid::resetPlayerTiles(std::vector<Tile*> t_player, std::vector<Gobblet*> t_playerGobblets)
{
	int size = -1;
	for (Tile* tile : t_player)
	{
		size = -1;

		if (tile->getCurrentGobblet() == nullptr)
		{
			size = 1;
		}

		else if (tile->getCurrentGobblet()->getSize() < 4)
		{
			size = tile->getCurrentGobblet()->getSize() + 1;
		}

		else
		{
			continue;
		}

		while (size <= 4)
		{
			for (Gobblet* g : t_playerGobblets)
			{
				if (g->getSize() == size)
				{
					tile->setCurrentGobblet(g);
					t_playerGobblets.erase(std::remove(t_playerGobblets.begin(),
						t_playerGobblets.end(), g), t_playerGobblets.end());
					size++;
				}
			}
		}
	}
}

/// <summary>
/// Draws each tile and their Gobblets to screen. Also draws the Gobblet that is currently picked up.
/// </summary>
/// <param name="t_window">The SFML window to draw to.</param>
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

/// <summary>
/// Updates the Grid each frame.
/// </summary>
/// <param name="t_mousePos">The mouse's position during this frame.</param>
void Grid::update(sf::Vector2i t_mousePos)
{
	if (m_selectedGobblet != nullptr)
	{
		m_selectedGobblet->setPosition(sf::Vector2f(t_mousePos.x, t_mousePos.y));
	}
}

/// <summary>
/// What is triggered when the user presses the left mouse button.
/// Is used to calculate whether the user is clicking on a Gobblet that they can move, 
/// and move the piece accordingly if so.
/// </summary>
/// <param name="t_click">The position of the mouse on the window when the left mouse button was clicked.</param>
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

/// <summary>
/// What is triggered when the user releases the left mouse button. 
/// Is used to calculate whether a Gobblet that is currently held can be placed down.
/// </summary>
/// <param name="t_click">The position of the mouse on the window when the left mouse button was released.</param>
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

		m_selectedTile = nullptr;
	}
}

/// <summary>
/// The AI's turn is triggered by this method.
/// </summary>
void Grid::processOpponentTurn()
{
	checkRows();

	if (g_status == Status::OnGoing)
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
		checkRows();
	}

}

/// <summary>
/// If the user is trying to move their Gobblet on top of another, this check is to see if the Gobblet underneath is smaller, 
/// so it can be gobbled.
/// </summary>
/// <param name="t_from">The Tile the Gobblet is moving from.</param>
/// <param name="t_to">The Tile the Gobblet is moving to.</param>
/// <returns>Whether this is a valid move.</returns>
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
/// Gets all the gobblets out from underneath the surface level Gobblets.
/// </summary>
/// <param name="parentGobblet">The Gobblet that is being checked to see if it has hidden child Gobblets underneath.</param>
/// <param name="t_playerGobblets">A reference to a storage of all the player 1 Gobblets on the board.</param>
/// <param name="t_enemyGobblets">A reference to a storage of all the player 2 Gobblets on the board.</param>
void Grid::getChildGobbletsOut(Gobblet* parentGobblet, std::vector<Gobblet*>* t_playerGobblets, std::vector<Gobblet*>* t_enemyGobblets)
{
	if (parentGobblet->getChild() != nullptr)
	{
		getChildGobbletsOut(parentGobblet->getChild(), t_playerGobblets, t_enemyGobblets);

		if (parentGobblet->getChild()->isControlledByPlayer())
		{
			t_playerGobblets->push_back(parentGobblet->getChild());
		}

		else
		{
			t_enemyGobblets->push_back(parentGobblet->getChild());
		}

		parentGobblet->setChild(nullptr);
	}
}

/// <summary>
/// Checks the status of the board - whether a player has won, or if there is a three in a row.
/// </summary>
void Grid::checkRows()
{
	threeInRow.clear();

	VerticalCheck();
	HorizontalCheck();
	DiagonalCheck();
}

/// <summary>
/// Checks the two diagonal lines for four in a row.
/// </summary>
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
		DidAPlayerWin(numOfPlayer, numOfEnemy);
		RowWasFound(0, 5, 10, 15);
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
		DidAPlayerWin(numOfPlayer, numOfEnemy);
		RowWasFound(3, 6, 9, 12);
		// theres three in a row!
	}
}

/// <summary>
/// Checks the four horizontal lines for four in a row.
/// </summary>
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
			DidAPlayerWin(numOfPlayer, numOfEnemy);
			RowWasFound(i, i + 4, i + 8, i + 12);
			// theres three in a row!
		}
	}
}

/// <summary>
/// Checks the four vertical lines for four in a row.
/// </summary>
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

			DidAPlayerWin(numOfPlayer, numOfEnemy);
			RowWasFound(temp, temp + 1, temp + 2, temp + 3);
			// theres three in a row!
		}
	}
}

/// <summary>
/// Is called to display the three in a row found to the console.
/// </summary>
/// <param name="in1">The index of the first Tile.</param>
/// <param name="in2">The index of the second Tile.</param>
/// <param name="in3">The index of the third Tile.</param>
/// <param name="in4">The index of the fourth Tile.</param>
void Grid::RowWasFound(int in1, int in2, int in3, int in4)
{
	threeInRow.push_back(std::vector<int>{in1, in2, in3, in4});
	std::cout << "Three in a row!: " << in1 << ", " << in2 << ", " << in3 << ", " << in4 << std::endl;
}

/// <summary>
/// Is a check to see whether a player has won or not.
/// </summary>
/// <param name="t_playerNum">The highest number of Player 1 pieces on the same line.</param>
/// <param name="t_enemyNum">The highest number of Player 2 pieces on the same line.</param>
void Grid::DidAPlayerWin(int t_playerNum, int t_enemyNum)
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
}

/// <summary>
/// Returns whether the gobblet moved is being moved from the player's inventory, 
/// or a piece on the board that's being moved to another part of said board.
/// </summary>
/// <param name="t_from">The tile the Gobblet is being taken from.</param>
/// <returns>Whether the tile is from the player's inventories or on the play board.</returns>
bool Grid::MovingFromInventory(Tile* t_from)
{
	return std::find(m_boardTiles.begin(), m_boardTiles.end(), t_from) == m_boardTiles.end();
}

/// <summary>
/// Is used to reinforce the rule of "User can only Gobble another piece from their inventory IF the other player has 3 in a row."
/// </summary>
/// <param name="t_from">The Tile the Gobblet is moving from.</param>
/// <param name="t_to">The Tile the Gobblet is moving to.</param>
/// <returns>Whether this is a valid move.</returns>
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
