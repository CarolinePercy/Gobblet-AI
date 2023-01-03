#pragma once
#include "Globals.h"
#include "Grid.h"

/// <summary>
/// The screen that will display the game to the player, and control it.
/// </summary>

class Gameplay
{
public:

	Gameplay();
	void processEvents(sf::Event t_event);
	void update(sf::Vector2i t_mousePos);
	void render(sf::RenderWindow& t_window);
	void resetBoard();

private:

	///The grid all the gameplay occurs on.
	Grid m_grid;

	///The position of the mouse on the screen.
	sf::Vector2i mousePos;

	///The text that announces the result of the game.
	sf::Text announcementText;

	void DrawText(sf::RenderWindow& t_window);
};

