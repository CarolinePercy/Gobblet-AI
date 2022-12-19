#include "Gameplay.h"

Gameplay::Gameplay()
{
}

void Gameplay::processEvents(sf::Event t_event)
{
	if (t_event.type == sf::Event::MouseButtonPressed)
	{
		m_grid.onMouseDown(mousePos);
	}
	if (t_event.type == sf::Event::MouseButtonReleased)
	{
		m_grid.onMouseUp(mousePos);
	}
}

void Gameplay::update(sf::Vector2i t_mousePos)
{
	mousePos = t_mousePos;
}

void Gameplay::render(sf::RenderWindow& t_window)
{
	m_grid.render(t_window);
}
