#include "ZobristKeys.h"

std::mt19937 ZobristKeys::mt = std::mt19937(01234567);
unsigned long ZobristKeys::table[NUM_OF_CELLS_IN_ROW][NUM_OF_CELLS_IN_ROW][NUM_OF_PIECES] = {};

/// <summary>
/// Default constructor for class.
/// </summary>
void ZobristKeys::initialise()
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

/// <summary>
/// Converts the current state of the board into a Zobrist Key.
/// </summary>
/// <param name="t_board">The grid in a simplified form.</param>
/// <returns>The current board's Zobrist key.</returns>
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

/// <summary>
/// Returns a number between 0 and 1.84 * 10^19 (inclusive).
/// </summary>
/// <returns>The generated number.</returns>
unsigned long ZobristKeys::generateRandomInt()
{
	std::uniform_int_distribution<unsigned long long int>
		dist(0, UINT64_MAX);

	return dist(mt);
}

/// <summary>
/// Moves a piece on the board, returning the Zobrist key of the new board state.
/// </summary>
/// <param name="t_board">The board in simplified form.</param>
/// <param name="t_from">Where the piece originally is.</param>
/// <param name="t_to">Where the piece wants to go.</param>
/// <returns>The Zobrist Key of the new board state.</returns>
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

/// <summary>
/// Finds what move occured between the first and second board.
/// </summary>
/// <param name="t_boardBefore">The board before the move.</param>
/// <param name="t_boardAfter">The board after the move.</param>
/// <param name="t_coordinates">What will store the move coordinates.</param>
void ZobristKeys::getMove(int t_boardBefore[4][4], int t_boardAfter[4][4], int t_coordinates[4])
{
	for (int i = 0; i < NUM_OF_CELLS_IN_ROW; i++)
	{
		for (int j = 0; j < NUM_OF_CELLS_IN_ROW; j++)
		{
			if (t_boardBefore[i][j] != t_boardAfter[i][j])
			{
				int before = t_boardBefore[i][j];
				int after = t_boardAfter[i][j];

				if (before > 4)
				{
					before -= 4;
				}

				if (after > 4)
				{
					after -= 4;
				}

				if (before > after)
				{
					// before coordinates
					t_coordinates[0] = i;
					t_coordinates[1] = j;
				}

				else
				{
					//after coordinates
					t_coordinates[2] = i;
					t_coordinates[3] = j;
				}
			}
		}
	}
}
