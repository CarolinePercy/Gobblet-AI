#include "Grid.h"

/// <summary>
/// Zobrist Key class. Helps with the storing of board states.
/// </summary>

class ZobristKeys
{
private:
	/// <summary>
	/// Number of gobblet pieces for each player.
	/// </summary>
	static const unsigned int NUM_OF_PIECES = 8;

	/// <summary>
	/// The amount of cells in a row in the grid : 4 x 4 spaces.
	/// </summary>
	static const unsigned int NUM_OF_CELLS_IN_ROW = 4; 

	/// <summary>
	/// The grid in Zobrist Keys.
	/// </summary>
	static unsigned long table[NUM_OF_CELLS_IN_ROW][NUM_OF_CELLS_IN_ROW][NUM_OF_PIECES];

	/// <summary>
	/// Helps with random number generation.
	/// </summary>
	static std::mt19937 mt;

public:

	static void initialise();
	static unsigned long generateRandomInt();

	static unsigned long long int findHashOfBoard(int t_board[4][4]); // 
	static unsigned long long int movePiece(int t_board[4][4], std::pair<int, int> t_from, std::pair<int, int> t_to);	
	static void getMove(int t_boardBefore[4][4], int t_boardAfter[4][4], int t_coordinates[4]);
};