#include "Tile.h"

/// <summary>
/// Overloaded constructor of this class.
/// </summary>
/// <param name="t_position">The position this Tile will be.</param>
/// <param name="t_size">The size of this new Tile.</param>
Tile::Tile(sf::Vector2f t_position, sf::Vector2f t_size) :  m_currentGobblet(nullptr)
{
	m_tile.setPosition(t_position);
	m_tile.setSize(t_size);
	m_tile.setOutlineThickness(5);
	m_tile.setOutlineColor(sf::Color::Black);
}


/// <summary>
/// Draws the Tile, and the Gobblet on top of it.
/// </summary>
/// <param name="t_window">The window to draw the tile to.</param>
void Tile::render(sf::RenderWindow& t_window)
{
	t_window.draw(m_tile);
	if (m_currentGobblet != nullptr)
	{
		m_currentGobblet->render(t_window);
	}
}

/// <summary>
/// Checks whether the mouse is inside this Tile.
/// </summary>
/// <param name="t_click">The position of the mouse.</param>
/// <returns>Whether the mouse is in the tile.</returns>
bool Tile::isInside(sf::Vector2i t_click)
{
	sf::Vector2f pos = m_tile.getPosition();
	sf::Vector2f size = m_tile.getSize();
	return t_click.x > pos.x && t_click.x < pos.x + size.x && t_click.y > pos.y && t_click.y < pos.y + size.y;
}

/// <summary>
/// Sets the Gobblet that is currently on this Tile.
/// </summary>
/// <param name="t_currentGobblet">The new Gobblet on this Tile.</param>
void Tile::setCurrentGobblet(Gobblet* t_currentGobblet)
{
	if (m_currentGobblet == nullptr)
	{
		m_currentGobblet = t_currentGobblet;
		m_currentGobblet->setChild(nullptr);
	}
	else
	{
		t_currentGobblet->setChild(m_currentGobblet);
		m_currentGobblet = t_currentGobblet;
	}
	

	if (m_currentGobblet != nullptr) 
	{
		m_currentGobblet->setPosition(m_tile.getPosition() + (m_tile.getSize() / 2.0f));
	}
}

/// <summary>
/// Moves the Gobblet on this Tile to another.
/// </summary>
/// <param name="t_destination">The new Tile the Gobblet will be moved to.</param>
void Tile::moveGobbletTo(Tile* t_destination) 
{
	if(m_currentGobblet != nullptr)
	{ 
		Gobblet* child = m_currentGobblet->getChild();
		t_destination->setCurrentGobblet(m_currentGobblet);
		m_currentGobblet = child;
		if (m_currentGobblet != nullptr)
		{
			m_currentGobblet->setPosition(m_tile.getPosition() + (m_tile.getSize() / 2.0f));
		}
	}
}

/// <summary>
/// Returns the position of the tile in relation to the screen.
/// </summary>
/// <returns>The position of the tile.</returns>
sf::Vector2f Tile::getPosition()
{
	return m_tile.getPosition();
}