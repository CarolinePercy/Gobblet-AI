#include "Game.h"
#include <iostream>

/// <summary>
/// Default constructor.
/// Sets up the window properties and load and setup the text,
/// also loads and sets up the image.
/// </summary>
Game::Game() :
	m_window{ sf::VideoMode{ G_VIEW_WIDTH, G_VIEW_HEIGHT, 32U }, "SFML Game" }
{}

/// <summary>
/// default destructor. We didn't dynamically allocate anything,
/// so we don't need to free it, but method needs to be here.
/// </summary>
Game::~Game()
{
}


/// <summary>
/// The main game loop.
/// This updates 60 times per second.
/// Also processes update as often as possible and at least 60 times per second.
/// Draws as often as possible but only updates are on time.
/// If updates run slow, then don't render frames.
/// </summary>
void Game::run()
{	
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	const float fps{ 60.0f };
	sf::Time timePerFrame = sf::seconds(1.0f / fps); // 60 fps
	while (m_window.isOpen())
	{
		processEvents(); // as many as possible
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents(); // at least 60 fps
			update(timePerFrame); //60 fps
		}
		render(); // as many as possible
	}
}

/// <summary>
/// Handles user and system events/input.
/// Gets key presses/mouse moves etc from OS
/// and user.
/// </summary>
void Game::processEvents()
{
	g_previousstate = g_gamestate;
	sf::Event newEvent;
	while (m_window.pollEvent(newEvent))
	{
		if ( sf::Event::Closed == newEvent.type) // window message
		{
			g_exitGame = true;
		}

		switch (g_gamestate)
		{
		case Gamestate::MainMenu:
			menuScreen.processEvents(newEvent);
			break;
		case Gamestate::Gameplay:
			gameScreen.processEvents(newEvent);
			break;
		case Gamestate::Help:
			helpScreen.processEvents(newEvent);
			break;
		default:
			break;
		}
	}

	if (g_gamestate == Gamestate::Gameplay && g_previousstate == Gamestate::MainMenu)
	{
		gameScreen.resetBoard();
	}
}

/// <summary>
/// Updates the world every 60th of a second.
/// </summary>
/// <param name="t_deltaTime">The time that has passed since last frame.</param>
void Game::update(sf::Time t_deltaTime)
{
	switch (g_gamestate)
	{
	case Gamestate::MainMenu:
		menuScreen.update(sf::Mouse::getPosition(m_window));
		break;
	case Gamestate::Gameplay:
		gameScreen.update(sf::Mouse::getPosition(m_window));
		break;
	case Gamestate::Help:
		helpScreen.update(sf::Mouse::getPosition(m_window));
		break;
	default:
		break;
	}

	if (g_exitGame)
	{
		m_window.close();
	}
}

/// <summary>
/// Draws the whole game to the SFML screen. Controls which screen will be shown to the player.
/// </summary>
void Game::render()
{
	m_window.clear();

	switch (g_gamestate)
	{
	case Gamestate::MainMenu:
		menuScreen.render(m_window);
		break;
	case Gamestate::Gameplay:
		gameScreen.render(m_window);
		break;
	case Gamestate::Help:
		helpScreen.render(m_window);
		break;
	default:
		break;
	}

	m_window.display();
}

