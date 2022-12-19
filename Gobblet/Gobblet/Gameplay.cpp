#include "Gameplay.h"

Gameplay::Gameplay()
{
}

void Gameplay::processEvents(sf::Event t_event)
{
}

void Gameplay::update(sf::Vector2i t_mousePos)
{
}

void Gameplay::render(sf::RenderWindow& t_window)
{
	m_grid.render(t_window);
}
