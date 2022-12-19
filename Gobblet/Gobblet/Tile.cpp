#include "Tile.h"

Tile::Tile(sf::Vector2f t_position, sf::Vector2f t_size, bool t_onBoard) : onBoard(t_onBoard), m_currentGobblet(nullptr)
{
	m_tile.setPosition(t_position);
	m_tile.setSize(t_size);
	m_tile.setOutlineThickness(5);
	m_tile.setOutlineColor(sf::Color::Black);
}

void Tile::render(sf::RenderWindow& t_window)
{
	t_window.draw(m_tile);
	if (m_currentGobblet != nullptr)
	{
		m_currentGobblet->render(t_window);
	}
}

bool Tile::isInside(sf::Vector2i t_click)
{
	sf::Vector2f pos = m_tile.getPosition();
	sf::Vector2f size = m_tile.getSize();
	return t_click.x > pos.x && t_click.x < pos.x + size.x && t_click.y > pos.y && t_click.y < pos.y + size.y;
}

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

void Tile::moveGobbletTo(Tile* t_destination) 
{
	Gobblet* child = m_currentGobblet->getChild();
	t_destination->setCurrentGobblet(m_currentGobblet);
	m_currentGobblet = child;
	if (m_currentGobblet != nullptr)
	{
		m_currentGobblet->setPosition(m_tile.getPosition() + (m_tile.getSize() / 2.0f));
	}
}
