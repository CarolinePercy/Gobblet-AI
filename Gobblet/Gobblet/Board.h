#pragma once
#include "Globals.h"
#include "ZobristKeys.h"

/// <summary>
/// Minimax analytic class. Is used to store a numeral representation of the Grid.
/// </summary>

class Board
{
public:
	Board(unsigned long long t_hashCode, int t_playerInventory[3], int t_aiInventory[3], int t_depth, bool t_AIturn);
	int minimax();
	unsigned long long getbestHash() { return bestHash; }
private:
	std::vector<unsigned long long> getOnBoardMoves();
	void processMovesFrom(int x, int y, std::vector<unsigned long long>& t_listOfMoves);
	std::vector<unsigned long long> getOffBoardMoves();
	unsigned long long getMoveHash(int x_from, int y_from, int x_to, int y_to);

	bool checkForWin();
	bool checkForLoss();
	void modifyForTriplesAI(int t_pieceSize);
	void modifyForTriplesPlayer(int t_pieceSize);
	int analyseBoardState();

	/// The layout of the the Grid, in numeral form. 1-4 is AI pieces, 5-8 is the Users, 9 is an empty Tile.
	int m_board[4][4] = {};

	/// The Pieces left in the first player's inventory (User)
	int m_playerInventory[3];

	/// The Pieces left in the second player's inventory (AI)
	int m_aiInventory[3];

	/// How far the AI is currently down in Minimax.
	int depth;

	/// How far the AI should go in Minimax, before cutting it off and making an estimate. Saves on time.
	const int MAX_DEPTH = 3;

	/// Keeps track of whether it the AI's Turn when predicting Minimax.
	bool AIturn;

	/// the best next move the AI can make.
	unsigned long long bestHash;
};
