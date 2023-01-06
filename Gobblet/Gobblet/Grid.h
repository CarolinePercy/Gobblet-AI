#pragma once
#include "Tile.h"
#include "Gobblet.h"
#include "Board.h"

/// <summary>
/// The class that keeps track of the board. It knows where pieces are and where they can go.
/// </summary>

class Grid
{
public:
	Grid();
	void render(sf::RenderWindow& t_window);
	void update(sf::Vector2i t_mousePos);
	void onMouseDown(sf::Vector2i t_click);
	void onMouseUp(sf::Vector2i t_click);

	void resetBoard();
private:

	void processOpponentTurn();
	bool compareGobbletSizes(Tile* t_from, Tile* t_to);

	/// The tiles on the main board, between the two players.
	std::vector<Tile*> m_boardTiles;

	/// The inventory of the second player (AKA the user).
	std::vector<Tile*> m_player1Tiles;

	/// The inventory of the second player (AKA the AI).
	std::vector<Tile*> m_player2Tiles;

	///The Tile the user has selected by clicking on it. Is saved in case the placing of the Gobblet is invalid, so it has this to refer back to.
	Tile* m_selectedTile;

	///The Gobblet the user is selecting and trying to move.
	Gobblet* m_selectedGobblet;

	///All the stored three of the same colour Gobblets in a row.
	std::vector<std::vector<int>> threeInRow;

	void getChildGobbletsOut(Gobblet* parentGobblet, std::vector<Gobblet*>* t_playerGobblets,
		std::vector<Gobblet*>* t_enemyGobblets);
	void resetPlayerTiles(std::vector<Tile*> t_player, std::vector<Gobblet*> t_playerGobblets);

	void checkRows();

	void DiagonalCheck();
	void HorizontalCheck();
	void VerticalCheck();

	void RowWasFound(int in1, int in2, int in3, int in4);
	void DidAPlayerWin(int t_playerNum, int t_enemyNum);

	bool MovingFromInventory(Tile* t_from);
	bool CheckIfThreeInARow(Tile* t_from, Tile* t_to);

	void calculateBestMove();
	void makeMove(unsigned long long before, unsigned long long after);
};
