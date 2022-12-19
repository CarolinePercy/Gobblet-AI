#pragma once
#include "Globals.h"
#include "Button.h"

class HelpScreen
{
public:

	HelpScreen();
	void processEvents(sf::Event t_event);
	void update(sf::Vector2i t_mousePos);
	void render(sf::RenderWindow& t_window);

private:
	///The Button that will bring you back to the MainMenu.
	Button* m_backButton;

	/// The text that will tell the player how to play.
	std::vector<sf::Text> helpText;
};

