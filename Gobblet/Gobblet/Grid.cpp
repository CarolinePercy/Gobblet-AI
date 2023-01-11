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

	playerBGColours[0] = sf::Color(119, 140, 199);
	playerBGColours[1] = sf::Color(199, 119, 119);

	background.setFillColor(playerBGColours[0]);
	background.setSize(sf::Vector2f(G_VIEW_WIDTH, G_VIEW_HEIGHT));
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

	g_yourTurn = true;
	background.setFillColor(playerBGColours[0]);
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
			tile->getCurrentGobblet()->setPosition(tile->getOffsetPosition());
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

		tile->getCurrentGobblet()->setPosition(tile->getOffsetPosition());
	}
}

/// <summary>
/// Draws each tile and their Gobblets to screen. Also draws the Gobblet that is currently picked up.
/// </summary>
/// <param name="t_window">The SFML window to draw to.</param>
void Grid::render(sf::RenderWindow& t_window)
{
	t_window.draw(background);

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

	if (AIMoveFrom != nullptr)
	{
		AIMoveFrom->getCurrentGobblet()->render(t_window);
	}
}

/// <summary>
/// Updates the Grid each frame.
/// </summary>
/// <param name="t_mousePos">The mouse's position during this frame.</param>
void Grid::update(sf::Vector2i t_mousePos, sf::Time t_deltaTime)
{
	if (m_selectedGobblet != nullptr)
	{
		m_selectedGobblet->setPosition(sf::Vector2f(t_mousePos.x, t_mousePos.y));
	}

	if (!g_yourTurn)
	{
		if (AIWaitTime < 0)
		{
			if (AIMoveFrom != nullptr && AIMoveTo != nullptr)
			{
				Gobblet* g = AIMoveFrom->getCurrentGobblet();

				sf::Vector2f distance = g->getPosition() - AIMoveTo->getPosition();
				float distanceLength = sqrt((distance.x * distance.x) + (distance.y * distance.y));

				//std::cout << distanceLength << std::endl;

				if (distanceLength < 100)
				{
					
					AIMoveFrom->moveGobbletTo(AIMoveTo);

					checkRows();

					if (g_status == Status::OnGoing)
					{
						g_yourTurn = true;
						background.setFillColor(playerBGColours[0]);
					}

					AIMoveFrom = nullptr;
					AIMoveTo = nullptr;
				}

				else
				{
					g->moveAlong(moveDirection * moveSpeed);
				}
			}

			else
			{
				std::cout << "Error!" << std::endl;

				

				checkRows();

				if (g_status == Status::OnGoing)
				{
					g_yourTurn = true;
					background.setFillColor(playerBGColours[0]);
				}

				AIMoveFrom = nullptr;
				AIMoveTo = nullptr;
			}

		}

		AIWaitTime -= t_deltaTime.asSeconds();
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
	if (g_yourTurn)
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
}

/// <summary>
/// What is triggered when the user releases the left mouse button. 
/// Is used to calculate whether a Gobblet that is currently held can be placed down.
/// </summary>
/// <param name="t_click">The position of the mouse on the window when the left mouse button was released.</param>
void Grid::onMouseUp(sf::Vector2i t_click)
{
	if (g_yourTurn)
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
}

/// <summary>
/// The AI's turn is triggered by this method.
/// </summary>
void Grid::processOpponentTurn()
{
	AIWaitTime = rand() % 2 + 1;

	checkRows();

	if (g_status == Status::OnGoing)
	{
		g_yourTurn = false;

		background.setFillColor(playerBGColours[1]);
		calculateBestMove();
		makeMove(boardStates[0], boardStates[1]);
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

void Grid::calculateBestMove()
{
	unsigned long long board = 0;
	for (Tile* tile : m_boardTiles)
	{
		board *= 10;
		Gobblet* current = tile->getCurrentGobblet();
		if (current != nullptr)
		{
			board += current->getSize();
			if (current->isControlledByPlayer())
				board += 4; // AI pieces are 1-4, AI are 5-8
		}

		else
		{
			board += 9;
		}
	}
	int playerInventory[3] = { 0 };
	int i = 0;
	for (Tile* tile : m_player1Tiles)
	{
		Gobblet* current = tile->getCurrentGobblet();
		if (current != nullptr)
		{
			playerInventory[i] = current->getSize();
		}


		i++;
	}
	int enemyInventory[3] = { 0 };
	i = 0;
	for (Tile* tile : m_player2Tiles)
	{
		Gobblet* current = tile->getCurrentGobblet();
		if (current != nullptr)
		{
			enemyInventory[i] = current->getSize();
		}
		i++;
	}
	boardStates[0] = board;
	Board calculate(boardStates[0], playerInventory, enemyInventory, 0, true);
	calculate.minimax();
	boardStates[1] = calculate.getbestHash();

}

void Grid::makeMove(unsigned long long before, unsigned long long after)
{
	std::vector<std::pair<int, int>> coordinates;
	int beforeBoard[4][4];
	int afterBoard[4][4];

	for (int i = 3; i >= 0; i--)
	{
		for (int j = 3; j >= 0; j--)
		{
			beforeBoard[j][i] = before % 10;
			before /= 10;
			afterBoard[j][i] = after % 10;
			after /= 10;
			if (beforeBoard[j][i] != afterBoard[j][i])
			{
				coordinates.push_back(std::pair<int, int>(j, i));
			}
		}
	}

	int differences = coordinates.size();
	if (differences > 2 || differences <= 0)
	{
		std::cout << "error in AI" << std::endl;
	}
	else if (differences == 1)
	{
		Tile* from = nullptr;

		int biggestSize = -1;
		for (Tile* tile : m_player2Tiles)
		{
			Gobblet* gobblet = tile->getCurrentGobblet();
			if (gobblet != nullptr)
			{
				if (gobblet->getSize() > biggestSize)
				{
					from = tile;
					biggestSize = gobblet->getSize();
				}
			}
		}
		if (biggestSize > 0)
		{
			int counter = coordinates.back().first + (coordinates.back().second * 4);
			for (Tile* tile : m_boardTiles)
			{
				if (counter == 0)
				{
					AIMoveFrom = from;
					AIMoveTo = tile;

					moveDirection = tile->getPosition() - from->getPosition();
					float length = sqrt((moveDirection.x * moveDirection.x) + (moveDirection.y * moveDirection.y));
					moveDirection = moveDirection / length;

					//from->moveGobbletTo(tile);
				}
				counter--;
			}
		}
	}
	else if (differences == 2)
	{
		Tile* fromTile = nullptr;
		Tile* toTile = nullptr;
		int fromCounter = 0;
		int toCounter = 0;
		for (std::pair<int, int> coordinate : coordinates)
		{
			int beforeSize = beforeBoard[coordinate.first][coordinate.second];
			int afterSize = afterBoard[coordinate.first][coordinate.second];

			if (beforeSize > 4)
				beforeSize -= 4;
			if (afterSize > 4)
				afterSize -= 4;

			if (beforeSize > afterSize)
			{
				fromCounter = coordinate.first + (coordinate.second * 4);
			}
			else if (beforeSize < afterSize)
			{
				toCounter = coordinate.first + (coordinate.second * 4);
			}
		}
		for (Tile* tile : m_boardTiles)
		{
			if (fromCounter == 0)
			{
				fromTile = tile;
			}
			else if (toCounter == 0)
			{
				toTile = tile;
			}
			fromCounter--;
			toCounter--;
		}

		AIMoveFrom = fromTile;
		AIMoveTo = toTile;
		//fromTile->moveGobbletTo(toTile);

		moveDirection = toTile->getPosition() - fromTile->getPosition();
		float length = sqrt((moveDirection.x * moveDirection.x) + (moveDirection.y * moveDirection.y));
		moveDirection = moveDirection / length;
	}
}

void Grid::slidePiece()
{
}
