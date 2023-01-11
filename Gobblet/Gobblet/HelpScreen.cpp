#include "HelpScreen.h"

/// <summary>
/// HelpScreen's Default Constructor.
/// </summary>
HelpScreen::HelpScreen()
{
	sf::Vector2f buttonSize = sf::Vector2f(250, 100);
	m_backButton = new Button(sf::Vector2f(G_VIEW_WIDTH - (buttonSize.x + 20), G_VIEW_HEIGHT - (buttonSize.y + 20)),
		buttonSize, "BACK", sf::Color::Yellow, sf::Color::Red, sf::Color::Green);

	for (int loop = 0; loop < 3; loop++)
	{
		m_difficultyButton = new Button(sf::Vector2f(G_VIEW_WIDTH / 2 - (buttonSize.x + 20 * loop), G_VIEW_HEIGHT - (buttonSize.y + 20)),
			buttonSize, std::to_string(loop + 1), sf::Color::Yellow, sf::Color::Red, sf::Color::Green);
	}

	const int line_no = 15;
	std::string help[line_no] = {
		"Gobblet is a game played on a 4x4 grid with two players,",
		"where the goal is to have 4 pieces in a row, either diagonally, horizontally, or vertically.",
		"The pieces in question range in size, either tiny, small, medium and large.",
		"The larger sizes can stack on top of the smaller ones,",
		"essentially blocking the smaller piece underneath from being considered a part of a 4 in a row.",
		"Each player will start with 3 piles, each having one of each size,buried underneath eachother.",
		"On your turn, you can either take from one of your piles,",
		"placing it somewhere on the board and revealing the smaller piece underneath,",
		"or you can move one of your pieces that is currently on the board, to wherever it can fit.",
		"This includes moving big pieces onto smaller ones, or uncovering your own secured smaller pieces.",
		"Any larger piece can be placed an a smaller piece.",
		"You cannot however place your pieces on your enemies if the piece you are playing was previously on the board.",
		"There is an exception to this though, if the piece your covering is part of a 4 in a row,",
		"that has 3 of your opponents pieces.",
		"If you pick up a piece, you must move that piece."
	};

	for (int i = 0; i < line_no; i++)
	{
		sf::Text newLine;
		newLine.setFont(g_font);
		newLine.setString(help[i]);
		newLine.setCharacterSize(30);
		newLine.setFillColor(sf::Color::White);
		newLine.setPosition(G_VIEW_WIDTH / 2, 75 + (55 * i));
		newLine.setOrigin(newLine.getLocalBounds().width / 2.0f, newLine.getLocalBounds().height / 2.0f);
		helpText.push_back(newLine);
	}
}

/// <summary>
/// Processes the events that happened while the player was on the help screen.
/// </summary>
/// <param name="t_event">The event that occured because of the player.</param>
void HelpScreen::processEvents(sf::Event t_event)
{
	if (sf::Event::MouseButtonPressed == t_event.type)
	{
		if (t_event.key.code == sf::Mouse::Left)
		{
			m_backButton->onMouseDown();

			for (int loop = 0; loop < 3; loop++)
			{
				m_difficultyButton[loop]->onMouseDown();
			}
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

			else
			{
				for (int loop = 0; loop < 3; loop++)
				{
					if (m_difficultyButton[loop]->onMouseUp())
					{
						g_maxDepth = difficulties[loop];
					}
				}
			}
		}
	}

	if (sf::Keyboard::Escape == t_event.key.code && sf::Event::KeyReleased == t_event.type)
	{
		g_exitGame = true;
	}
}

/// <summary>
/// Updates the back button every frame.
/// </summary>
/// <param name="t_mousePos">The mouse's position on the screen.</param>
void HelpScreen::update(sf::Vector2i t_mousePos)
{
	m_backButton->update(t_mousePos);

	for (int loop = 0; loop < 3; loop++)
	{
		m_difficultyButton[loop]->update(t_mousePos);

		if (difficulties[loop] == g_maxDepth)
		{
			m_difficultyButton[loop]->selected();
		}
	}
}

/// <summary>
/// Draws all the relevant items in HelpScreen to the sfml window, such as the back button and the text explaining the game. 
/// </summary>
/// <param name="t_window">The SFML window to draw to.</param>
void HelpScreen::render(sf::RenderWindow& t_window)
{
	for (sf::Text line : helpText)
	{
		t_window.draw(line);
	}

	for (int loop = 0; loop < 3; loop++)
	{
		m_difficultyButton[loop]->render(t_window);
	}

	m_backButton->render(t_window);
}
