#include "HelpScreen.h"

HelpScreen::HelpScreen()
{
	sf::Vector2f buttonSize = sf::Vector2f(250, 100);
	m_backButton = new Button(sf::Vector2f(G_VIEW_WIDTH - (buttonSize.x + 20), G_VIEW_HEIGHT - (buttonSize.y + 20)),
		buttonSize, "BACK", sf::Color::Yellow, sf::Color::Red, sf::Color::Green);

	const int line_no = 3;
	std::string help[line_no] = {
		"Move using the arrow keys",
		"Find the stairs to the next floor",
		"Avoid enemies"
	};

	for (int i = 0; i < line_no; i++)
	{
		sf::Text newLine;
		newLine.setFont(g_font);
		newLine.setString(help[i]);
		newLine.setCharacterSize(40);
		newLine.setFillColor(sf::Color::White);
		newLine.setPosition(1200 / 2, 800 / 4 + (50 * i));
		newLine.setOrigin(newLine.getLocalBounds().width / 2.0f, newLine.getLocalBounds().height / 2.0f);
		helpText.push_back(newLine);
	}
}

void HelpScreen::processEvents(sf::Event t_event)
{
	if (sf::Event::MouseButtonPressed == t_event.type)
	{
		if (t_event.key.code == sf::Mouse::Left)
		{
			m_backButton->onMouseDown();
		}
	}
	if (sf::Event::MouseButtonReleased == t_event.type)
	{
		if (t_event.key.code == sf::Mouse::Left)
		{
			if (m_backButton->onMouseUp())
			{
				g_gamestate = Gamestate::MainMenu;
			}
		}
	}
}

void HelpScreen::update(sf::Vector2i t_mousePos)
{
	m_backButton->update(t_mousePos);
}

void HelpScreen::render(sf::RenderWindow& t_window)
{
	for (sf::Text line : helpText)
	{
		t_window.draw(line);
	}

	m_backButton->render(t_window);
}
