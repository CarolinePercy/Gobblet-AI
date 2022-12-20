#include "Gameplay.h"

Gameplay::Gameplay()
{
	announcementText.setFont(g_font);
	announcementText.setCharacterSize(50);
	announcementText.setScale(1.5, 1.5);
	announcementText.setOutlineColor(sf::Color::Black);
	announcementText.setOutlineThickness(10);
}

void Gameplay::processEvents(sf::Event t_event)
{
	if (g_status == Status::OnGoing)
	{
		if (t_event.type == sf::Event::MouseButtonPressed)
		{
			if (t_event.key.code == sf::Mouse::Left)
				m_grid.onMouseDown(mousePos);
		}
		if (t_event.type == sf::Event::MouseButtonReleased)
		{
			if (t_event.key.code == sf::Mouse::Left)
				m_grid.onMouseUp(mousePos);
		}
	}

	if (sf::Keyboard::Escape == t_event.key.code && sf::Event::KeyReleased == t_event.type)
	{
		g_gamestate = Gamestate::MainMenu;
	}
}

void Gameplay::update(sf::Vector2i t_mousePos)
{
	mousePos = t_mousePos;
	m_grid.update(t_mousePos);
}

void Gameplay::render(sf::RenderWindow& t_window)
{
	m_grid.render(t_window);

	if (g_status == Status::Player1Wins)
	{
		announcementText.setString("Player 1 Wins!");
		announcementText.setFillColor(sf::Color::Cyan);
		DrawText(t_window);
	}

	else if (g_status == Status::Player2Wins)
	{
		announcementText.setString("Player 2 Wins!");
		announcementText.setFillColor(sf::Color::Magenta);
		DrawText(t_window);
	}
}

void Gameplay::DrawText(sf::RenderWindow& t_window)
{
	announcementText.setPosition(G_VIEW_WIDTH / 2, G_VIEW_HEIGHT / 2);
	announcementText.setOrigin(announcementText.getLocalBounds().width / 2.0f, announcementText.getLocalBounds().height / 2.0f);
	t_window.draw(announcementText);
}
