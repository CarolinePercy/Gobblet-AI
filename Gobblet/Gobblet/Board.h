#pragma once
#include "Globals.h"
#include "ZobristKeys.h"

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

	int m_board[4][4] = {};
	int m_playerInventory[3];
	int m_aiInventory[3];
	int depth;
	const int MAX_DEPTH = 3;
	bool AIturn;

	unsigned long long bestHash;
};
