#include "Gobblet.h"

/// <summary>
/// The overloaded constructor of the Gobblet piece.
/// </summary>
/// <param name="t_size">The size of this gobblet piece.</param>
/// <param name="t_isPlayer">Whether this piece is controlled by the player or AI.</param>
Gobblet::Gobblet(int t_size, bool t_isPlayer) : m_child(nullptr), size(t_size), controlledByPlayer(t_isPlayer)
{
	float bigRadius = (G_VIEW_HEIGHT - 20) / 8.0f;
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

	controlledByPlayer = t_isPlayer;
}

/// <summary>
/// Draws the appearance of the piece onto the board.
/// </summary>
/// <param name="t_window">The sfml window to draw to.</param>
void Gobblet::render(sf::RenderWindow& t_window)
{
	t_window.draw(m_gobblet);
}
