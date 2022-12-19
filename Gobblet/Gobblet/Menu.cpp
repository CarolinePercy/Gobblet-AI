#include "Menu.h"

Menu::Menu()
{
	sf::Vector2f buttonSize = sf::Vector2f(400, 150);
	std::string buttonTexts[3] = { "PLAY", "HELP", "EXIT" };
	for (int i = 0; i < 3; i++)
	{
		m_buttons.push_back(new Button(sf::Vector2f(G_VIEW_WIDTH * 0.5f - (buttonSize.x / 2), G_VIEW_HEIGHT / 8 + (buttonSize.y * 1.2 * i)),
			buttonSize, buttonTexts[i], sf::Color::Yellow, sf::Color::Red, sf::Color::Green));
	}
}

void Menu::processEvents(sf::Event t_event)
{
	if (sf::Event::MouseButtonPressed == t_event.type)
	{
		if (t_event.key.code == sf::Mouse::Left)
		{
			for (Button* button : m_buttons)
			{
				button->onMouseDown();
			}
		}
	}
	if (sf::Event::MouseButtonReleased == t_event.type)
	{
		if (t_event.key.code == sf::Mouse::Left)
		{
			int counter = 0;
			for (Button* button : m_buttons)
			{
				if (button->onMouseUp())
				{
					switch (counter)
					{
					case 0:
						g_gamestate = Gamestate::Gameplay;
						break;
					case 1:
						g_gamestate = Gamestate::Help;
						break;
					case 2:
						g_exitGame = true;
						break;
					}
				}
				counter++;
			}
		}
	}
}

void Menu::update(sf::Vector2i t_mousePos)
{
	for (Button* button : m_buttons)
	{
		button->update(t_mousePos);
	}
}

void Menu::render(sf::RenderWindow& t_window)
{
	for (Button* button : m_buttons)
	{
		button->render(t_window);
	}
}
