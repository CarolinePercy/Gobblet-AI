#include "Grid.h"

class ZobristKeys
{
private:
	static const unsigned int NUM_OF_PIECES = 8; // 4 for each player
	static const unsigned int NUM_OF_CELLS_IN_ROW = 4; // 4 x 4 grid spaces

	unsigned long table[NUM_OF_CELLS_IN_ROW][NUM_OF_CELLS_IN_ROW][NUM_OF_PIECES];

	unsigned long generateRandomInt();
	std::mt19937 mt = std::mt19937(01234567);

public:

	ZobristKeys();
	unsigned long long int findHashOfBoard(int t_board[4][4]); // 
	unsigned long long int movePiece(int t_board[4][4],
		std::pair<int, int> t_from, std::pair<int, int> t_to);
	
	void getMove(int t_boardBefore[4][4], int t_boardAfter[4][4], int t_coordinates[4]);
};