#ifndef GAME_HPP
#define GAME_HPP
/// <summary>
/// include guards used so we don't process this file twice
/// same as #pragma once
/// Don't forget the endif at the bottom
/// </summary>

// Gobblet - made by Eoin Galavan & Caroline Percy
#include "Gameplay.h"
#include "Menu.h"
#include "Globals.h"
#include "HelpScreen.h"

class Game
{
public:
	Game();
	~Game();
	/// <summary>
	/// main method for game
	/// </summary>
	void run();

private:

	void processEvents();
	void processKeys(sf::Event t_event);
	void update(sf::Time t_deltaTime);
	void render();

	sf::RenderWindow m_window; // main SFML window
	bool m_exitGame; // control exiting game


	// Screens
	HelpScreen helpScreen;
	Gameplay gameScreen;
	Menu menuScreen;

};

#endif // !GAME_HPP

