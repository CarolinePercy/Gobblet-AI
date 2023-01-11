#include "Gameplay.h"

/// <summary>
/// Gameplay's Default Constructor.
/// </summary>
Gameplay::Gameplay()
{
	announcementText.setFont(g_font);
	announcementText.setCharacterSize(50);
	announcementText.setScale(1.5, 1.5);
	announcementText.setOutlineColor(sf::Color::Black);
	announcementText.setOutlineThickness(10);

	SetUpTurnText();
}

/// <summary>
/// Sets up the text letting the player(s) know who's turn it is.
/// </summary>
void Gameplay::SetUpTurnText()
{
	sf::Color turnTextColour[2];
	sf::Vector2f textPos[2];

	textPos[0] = sf::Vector2f(G_VIEW_WIDTH / 25, G_VIEW_HEIGHT - (G_VIEW_HEIGHT / 7));
	textPos[1] = sf::Vector2f(G_VIEW_WIDTH - (G_VIEW_WIDTH / 4.8), G_VIEW_HEIGHT / 10);

	turnTextColour[0] = sf::Color(212, 244, 255);
	turnTextColour[1] = sf::Color(255, 209, 225);

	turnText[0].setString("Your Turn");
	turnText[1].setString("Player 2's Turn");

	for (int loop = 0; loop < 2; loop++)
	{
		turnText[loop].setFont(g_font);
		turnText[loop].setCharacterSize(30);
		turnText[loop].setScale(1.5, 1.5);

		turnText[loop].setOutlineColor(sf::Color::Black);
		turnText[loop].setOutlineThickness(3);
		turnText[loop].setFillColor(turnTextColour[loop]);

		turnText[loop].setPosition(textPos[loop]);
		announcementText.setOrigin(announcementText.getLocalBounds().width / 2.0f, announcementText.getLocalBounds().height / 2.0f);
	}


}

 /// <summary>
/// Processes the events that happened while the player was on the Gameplay screen.
/// </summary>
/// <param name="t_event">The event that occured because of the player.</param>
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

/// <summary>
/// Updates the Grid and mouse position every frame.
/// </summary>
/// <param name="t_mousePos">The mouse's position on the screen.</param>
void Gameplay::update(sf::Vector2i t_mousePos, sf::Time t_deltaTime)
{
	mousePos = t_mousePos;
	m_grid.update(t_mousePos, t_deltaTime);
}

/// <summary>
/// Draws all the relevant items in Gameplay to the sfml window, such as the Grid 
/// and the announcement text.
/// </summary>
/// <param name="t_window">The SFML window to draw to.</param>
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

	if (g_yourTurn)
	{
		t_window.draw(turnText[0]);
	}

	else
	{
		t_window.draw(turnText[1]);

	}
}

/// <summary>
/// Draws the text of the announcement to the screen.
/// </summary>
/// <param name="t_window">The SFML window to draw to.</param>
void Gameplay::DrawText(sf::RenderWindow& t_window)
{
	announcementText.setPosition(G_VIEW_WIDTH / 2, G_VIEW_HEIGHT / 2);
	announcementText.setOrigin(announcementText.getLocalBounds().width / 2.0f, announcementText.getLocalBounds().height / 2.0f);
	t_window.draw(announcementText);
}

/// <summary>
/// Resets the game back to the beginning.
/// </summary>
void Gameplay::resetBoard()
{
	m_grid.resetBoard();
	g_status = Status::OnGoing;
}