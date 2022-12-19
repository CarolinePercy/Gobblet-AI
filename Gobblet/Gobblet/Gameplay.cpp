#include "Gameplay.h"

Gameplay::Gameplay()
{
}

void Gameplay::processEvents(sf::Event t_event)
{
	if (sf::Keyboard::Escape == t_event.key.code && sf::Event::KeyReleased == t_event.type)
	{
		g_gamestate = Gamestate::MainMenu;
	}
}

void Gameplay::update(sf::Vector2i t_mousePos)
{
}

void Gameplay::render(sf::RenderWindow& t_window)
{
	m_grid.render(t_window);
}
