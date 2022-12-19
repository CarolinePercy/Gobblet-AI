#include "Tile.h"

Tile::Tile(sf::Vector2f t_position, sf::Vector2f t_size, bool t_onBoard) : onBoard(t_onBoard)
{
	m_tile.setPosition(t_position);
	m_tile.setSize(t_size);
	m_tile.setOutlineThickness(5);
	m_tile.setOutlineColor(sf::Color::Black);
}

void Tile::render(sf::RenderWindow& t_window)
{
	t_window.draw(m_tile);
}

bool Tile::isInside(sf::Vector2i t_click)
{
	return false;
}
