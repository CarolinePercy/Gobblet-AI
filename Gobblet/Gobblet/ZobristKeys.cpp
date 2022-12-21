#include "ZobristKeys.h"

ZobristKeys::ZobristKeys()
{
	for (int i = 0; i < NUM_OF_CELLS_IN_ROW; i++)
	{
		for (int j = 0; j < NUM_OF_CELLS_IN_ROW; j++)
		{
			for (int k = 0; k < NUM_OF_PIECES; k++)
			{
				table[i][j][k] = generateRandomInt();
			}
		}
	}
}

unsigned long long int ZobristKeys::findHashOfBoard(int t_board[4][4])
{
	unsigned long long int h = 0;


	for (int i = 0; i < NUM_OF_CELLS_IN_ROW; i++)
	{
		for (int j = 0; j < NUM_OF_CELLS_IN_ROW; j++)
		{
			if (t_board[i][j] != '-')
			{
				int piece = t_board[i][j];
				h ^= table[i][j][piece];
			}
		}


	}
	return h;
}

unsigned long ZobristKeys::generateRandomInt()
{
	std::uniform_int_distribution<unsigned long long int>
		dist(0, UINT64_MAX);

	return dist(mt);
}

unsigned long long int ZobristKeys::movePiece(int t_board[4][4],
	std::pair<int,int> t_from, std::pair<int, int> t_to)
{
	unsigned long long int hashValue = 0;

	char piece = t_board[t_from.first][t_from.second];

	t_board[t_from.first][t_from.second] = '-';

	hashValue ^= table[t_from.first][t_from.second][piece];

	t_board[t_to.first][t_to.second] = piece;
	hashValue ^= table[t_to.first][t_to.second][piece];

	return hashValue;
}