#pragma once
#include "Globals.h"

class Board
{
public:
	Board(long t_hashCode, int t_playerInventory[3], int t_aiInventory[3], int t_depth, bool t_AIturn);
	int minimax();
	long getbestHash() { return bestHash; }
private:
	std::vector<long> getOnBoardMoves();
	void processMovesFrom(int x, int y, std::vector<long>& t_listOfMoves);
	std::vector<long> getOffBoardMoves();

	bool checkForWin();
	bool checkForLoss();
	void modifyForTriplesAI(int t_pieceSize);
	void modifyForTriplesPlayer(int t_pieceSize);
	int analyseBoardState();

	char m_board[4][4] = {0};
	int m_playerInventory[3];
	int m_aiInventory[3];
	int depth;
	const int MAX_DEPTH = 5;
	bool AIturn;

	long bestHash;
};
