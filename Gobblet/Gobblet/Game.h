#ifndef GAME_HPP
#define GAME_HPP

// include guards used so we don't process this file twice
// same as #pragma once
// Don't forget the endif at the bottom

// Gobblet - made by Eoin Galavan & Caroline Percy
#include "Gameplay.h"
#include "Menu.h"
#include "Globals.h"
#include "HelpScreen.h"
#include <iostream>

/// <summary>
/// Main Game class. Used to control the flow of the program.
/// </summary>
class Game
{
public:
	Game();
	~Game();
	void run();

private:

	void processEvents();
	void update(sf::Time t_deltaTime);
	void render();

	/// The main SFML window, where everything will draw to.
	sf::RenderWindow m_window; 


	///The help screen instance the player will see.
	HelpScreen helpScreen;

	///The gameplay screen instance the player will see.
	Gameplay gameScreen;

	///The menu screen instance the player will see.
	Menu menuScreen;

};

#endif // !GAME_HPP

