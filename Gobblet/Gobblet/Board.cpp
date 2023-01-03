#include "Board.h"

Board::Board(long t_hashCode, int t_playerInventory[3], int t_aiInventory[3], int t_depth, bool t_AIturn) : depth(t_depth), AIturn(t_AIturn)
{
	for (int i = 0; i < 3; i++)
	{
		m_playerInventory[i] = t_playerInventory[i];
		m_aiInventory[i] = t_aiInventory[i];
	}
	// convert t_hashCode into m_board
}

int Board::minimax()
{
	// check for win or tie
	if (checkForWin())
	{
		return 50;
	}
	else if (checkForLoss())
	{
		return -50;
	}
	else if (depth >= MAX_DEPTH)
	{
		return analyseBoardState();
	}

	// if AIs turn, loop throug Ais moves
	if (AIturn == true)
	{
		int bestVal = INT_MIN;
		for (long hash : getOnBoardMoves())
		{
			Board nextBoard(hash, m_playerInventory, m_aiInventory, depth++, !AIturn);
			int value = nextBoard.minimax();
			if (value > bestVal)
			{
				bestHash = nextBoard.getbestHash();
			}
			bestVal = std::max(bestVal, value);
		}
		for (long hash : getOffBoardMoves())
		{
			Board nextBoard(hash, m_playerInventory, m_aiInventory, depth++, !AIturn);
			int value = nextBoard.minimax();
			if (value > bestVal)
			{
				bestHash = nextBoard.getbestHash();
			}
			bestVal = std::max(bestVal, value);
		}
		return bestVal;
	}
	// if Players turn, loop throug Players moves
	else
	{
		int bestVal = INT_MIN;
		for (long hash : getOnBoardMoves())
		{
			Board nextBoard(hash, m_playerInventory, m_aiInventory, depth++, !AIturn);
			int value = nextBoard.minimax();
			if (value < bestVal)
			{
				bestHash = nextBoard.getbestHash();
			}
			bestVal = std::min(bestVal, value);
		}
		for (long hash : getOffBoardMoves())
		{
			Board nextBoard(hash, m_playerInventory, m_aiInventory, depth++, !AIturn);
			int value = nextBoard.minimax();
			if (value < bestVal)
			{
				bestHash = nextBoard.getbestHash();
			}
			bestVal = std::min(bestVal, value);
		}
		return bestVal;
	}
}

std::vector<long> Board::getOnBoardMoves()
{
	std::vector<long> moves;
	if (AIturn)
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (m_board[i][j] < 5 && m_board[i][j] != 0)
				{
					processMovesFrom(i, j, moves);
				}
			}
		}
	}
	else
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (m_board[i][j] >= 5)
				{
					processMovesFrom(i, j, moves);
				}
			}
		}
	}
	return moves;
}

void Board::processMovesFrom(int x, int y, std::vector<long>& t_listOfMoves)
{
	if (AIturn)
	{
		int size = m_board[x][y] + 4;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (m_board[i][j] < m_board[x][y] || (m_board[i][j] >= 5 && m_board[i][j] < size))
				{
					// move from x,y to i,j then add new hash value to the vector
				}
			}
		}
	}
	else
	{
		int size = m_board[x][y] - 4;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (m_board[i][j] < size || (m_board[i][j] >= 5 && m_board[i][j] < m_board[x][y]))
				{
					// move from x,y to i,j then add new hash value to the vector
				}
			}
		}
	}
}

std::vector<long> Board::getOffBoardMoves()
{
	char currentBoard[4][4];
	std::vector<long> moves;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			currentBoard[i][j] = m_board[i][j];
		}
	}
	
	int pieceSize = 0;
	if (AIturn)
	{
		int biggesttPiece = -1;
		for (int i = 0; i < 3; i++)
		{
			if (m_aiInventory[i] > pieceSize)
			{
				pieceSize = m_aiInventory[i];
				biggesttPiece = i;
			}
		}
		if (pieceSize < 1)
			return moves;
		else
			m_aiInventory[biggesttPiece]--;
		modifyForTriplesAI(pieceSize);
	}
	else
	{
		int biggesttPiece = -1;
		for (int i = 0; i < 3; i++)
		{
			if (m_playerInventory[i] > pieceSize)
			{
				pieceSize = m_playerInventory[i];
				biggesttPiece = i;
			}
		}
		if (pieceSize < 1)
			return moves;
		else
			m_aiInventory[biggesttPiece]--;
		modifyForTriplesPlayer(pieceSize);
	}
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (m_board[i][j] == 0)
			{
				// move 5,pieceSize to i,j then add new hash value to the vector
			}
		}
	}
	// reset the board
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			m_board[i][j] = currentBoard[i][j];
		}
	}
	return moves;
}

bool Board::checkForWin()
{
	for (int i = 0; i < 4; i++)
	{
		int count = 0;
		for (int j = 0; j < 4; j++)
		{
			if (m_board[i][j] < 5 && m_board[i][j] != 0)
				count++;
		}
		if (count >= 4)
			return true;
	}
	for (int i = 0; i < 4; i++)
	{
		int count = 0;
		for (int j = 0; j < 4; j++)
		{
			if (m_board[j][i] < 5 && m_board[j][i] != 0)
				count++;
		}
		if (count >= 4)
			return true;
	}
	int count = 0;
	for (int i = 0; i < 4; i++)
	{
		if (m_board[i][i] < 5 && m_board[i][i] != 0)
			count++;
	}
	if(count >= 4)
		return true;
	count = 0;
	for (int i = 0; i < 4; i++)
	{
		if (m_board[i][4 - i] < 5 && m_board[i][4 - i] != 0)
			count++;
	}
	if (count >= 4)
		return true;

	return false;
}

bool Board::checkForLoss()
{
	for (int i = 0; i < 4; i++)
	{
		int count = 0;
		for (int j = 0; j < 4; j++)
		{
			if (m_board[i][j] >= 5)
				count++;
		}
		if (count >= 4)
			return true;
	}
	for (int i = 0; i < 4; i++)
	{
		int count = 0;
		for (int j = 0; j < 4; j++)
		{
			if (m_board[j][i] >= 5)
				count++;
		}
		if (count >= 4)
			return true;
	}
	int count = 0;
	for (int i = 0; i < 4; i++)
	{
		if (m_board[i][i] >= 5)
			count++;
	}
	if (count >= 4)
		return true;
	count = 0;
	for (int i = 0; i < 4; i++)
	{
		if (m_board[i][4 - i] >= 5)
			count++;
	}
	if (count >= 4)
		return true;

	return false;
}

void Board::modifyForTriplesAI(int t_pieceSize)
{
	std::vector < std::pair<int, int> > coverable;

	for (int i = 0; i < 4; i++)
	{
		int count = 0;
		for (int j = 0; j < 4; j++)
		{
			if (m_board[i][j] >= 5)
				count++;
		}
		if (count >= 3)
		{
			for (int j = 0; j < 4; j++)
			{
				if (t_pieceSize - 4 > m_board[i][j])
					coverable.push_back(std::pair<int, int>(i, j));
			}
		}
	}

	for (int i = 0; i < 4; i++)
	{
		int count = 0;
		for (int j = 0; j < 4; j++)
		{
			if (m_board[j][i] >= 5)
				count++;
		}
		if (count >= 3)
		{
			for (int j = 0; j < 4; j++)
			{
				if (t_pieceSize - 4 > m_board[j][i])
					coverable.push_back(std::pair<int, int>(j, i));
			}
		}
	}

	int count = 0;
	for (int i = 0; i < 4; i++)
	{
		if (m_board[i][i] >= 5)
			count++;
	}
	if (count >= 3)
	{
		for (int i = 0; i < 4; i++)
		{
			if (t_pieceSize - 4 > m_board[i][i])
				coverable.push_back(std::pair<int, int>(i, i));
		}
	}

	count = 0;
	for (int i = 0; i < 4; i++)
	{
		if (m_board[i][3 - i] >= 5)
			count++;
	}
	if (count >= 3)
	{
		for (int i = 0; i < 4; i++)
		{
			if (t_pieceSize - 4 > m_board[i][3 - i])
				coverable.push_back(std::pair<int, int>(i, 3 - i));
		}
	}

	for (std::pair<int, int> pair : coverable)
	{
		m_board[pair.first][pair.second] = 0;
	}
}

void Board::modifyForTriplesPlayer(int t_pieceSize)
{
	std::vector < std::pair<int, int> > coverable;

	for (int i = 0; i < 4; i++)
	{
		int count = 0;
		for (int j = 0; j < 4; j++)
		{
			if (m_board[i][j] < 5 && m_board[i][j] != 0)
				count++;
		}
		if (count >= 3)
		{
			for (int j = 0; j < 4; j++)
			{
				if (t_pieceSize - 4 > m_board[i][j])
					coverable.push_back(std::pair<int, int>(i, j));
			}
		}
	}

	for (int i = 0; i < 4; i++)
	{
		int count = 0;
		for (int j = 0; j < 4; j++)
		{
			if (m_board[j][i] < 5 && m_board[j][i] != 0)
				count++;
		}
		if (count >= 3)
		{
			for (int j = 0; j < 4; j++)
			{
				if (t_pieceSize - 4 > m_board[j][i])
					coverable.push_back(std::pair<int, int>(j, i));
			}
		}
	}

	int count = 0;
	for (int i = 0; i < 4; i++)
	{
		if (m_board[i][i] < 5 && m_board[i][i] != 0)
			count++;
	}
	if (count >= 3)
	{
		for (int i = 0; i < 4; i++)
		{
			if (t_pieceSize - 4 > m_board[i][i])
				coverable.push_back(std::pair<int, int>(i, i));
		}
	}

	count = 0;
	for (int i = 0; i < 4; i++)
	{
		if (m_board[i][3 - i] < 5 && m_board[i][3 - i] != 0)
			count++;
	}
	if (count >= 3)
	{
		for (int i = 0; i < 4; i++)
		{
			if (t_pieceSize - 4 > m_board[i][3 - i])
				coverable.push_back(std::pair<int, int>(i, 3 - i));
		}
	}

	for (std::pair<int, int> pair : coverable)
	{
		m_board[pair.first][pair.second] = 0;
	}
}

int Board::analyseBoardState()
{
	return 0;
}
