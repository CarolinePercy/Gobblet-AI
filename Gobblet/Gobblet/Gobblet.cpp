#include "Gobblet.h"

Gobblet::Gobblet(int t_size, bool t_isPlayer) : m_child(nullptr), size(t_size)
{
	float bigRadius = (720 - 20) / 8.0f;
	switch (t_size)
	{
	case 1:
		m_gobblet.setRadius(bigRadius / 4);
		break;
	case 2:
		m_gobblet.setRadius(bigRadius / 2);
		break;
	case 3:
		m_gobblet.setRadius(3 * (bigRadius / 4));
		break;
	case 4:
		m_gobblet.setRadius(bigRadius);
		break;
	default:
		//error message
		break;
	}
	m_gobblet.setOrigin(m_gobblet.getRadius(), m_gobblet.getRadius());

	if (t_isPlayer)
		m_gobblet.setFillColor(sf::Color::Blue);
	else
		m_gobblet.setFillColor(sf::Color::Red);
}

void Gobblet::render(sf::RenderWindow& t_window)
{
	t_window.draw(m_gobblet);
}
