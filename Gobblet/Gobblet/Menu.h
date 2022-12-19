#pragma once
#include "Globals.h"

class Menu
{
public:

	Menu();
	void processEvents(sf::Event t_event);
	void update(sf::Vector2i t_mousePos);
	void render(sf::RenderWindow& t_window);

private:
};

