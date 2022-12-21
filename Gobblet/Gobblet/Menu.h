#pragma once
#include "Globals.h"
#include "Button.h"

/// <summary>
/// The screen that helps the player navigate the program.
/// </summary>

class Menu
{
public:

	Menu();
	void processEvents(sf::Event t_event);
	void update(sf::Vector2i t_mousePos);
	void render(sf::RenderWindow& t_window);

private:

	/// The buttons on the menu screen.
	std::vector<Button*> m_buttons;
};

