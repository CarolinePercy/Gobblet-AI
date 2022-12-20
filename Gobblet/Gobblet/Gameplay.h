#pragma once
#include "Globals.h"
#include "Grid.h"

class Gameplay
{
public:

	Gameplay();
	void processEvents(sf::Event t_event);
	void update(sf::Vector2i t_mousePos);
	void render(sf::RenderWindow& t_window);
	void resetBoard();

private:

	Grid m_grid;
	sf::Vector2i mousePos;
	sf::Text announcementText;

	void DrawText(sf::RenderWindow& t_window);
};

