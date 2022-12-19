#pragma once
#include "Globals.h"
#include "Button.h"

class Menu
{
public:

	Menu();
	void processEvents(sf::Event t_event);
	void update(sf::Vector2i t_mousePos);
	void render(sf::RenderWindow& t_window);

private:

	std::vector<Button*> m_buttons;
};

