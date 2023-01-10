#ifndef GLOBALS_H
#define GLOBALS_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include <algorithm>
#include <iterator>

/// <summary>
/// All the screens the player has the choice of viewing.
/// </summary>
enum class Gamestate
{
	MainMenu,
	Gameplay,
	Help
};

/// <summary>
/// The status of the Gobblet game - who won and lost, or if its still being played.
/// </summary>
enum class Status
{
	OnGoing,
	Player1Wins,
	Player2Wins,
	Draw
};

///The current screen the user is on.
extern Gamestate g_gamestate;

///The previous screen the user was on.
extern Gamestate g_previousstate;

/// The status of the board game - who won, or if it is still going.
extern Status g_status;

///The font used throughout the game.
extern sf::Font g_font;

///Bool that controls when the game ends.
extern bool g_exitGame;

///The width of the SFMl screen the game takes place.
unsigned const int G_VIEW_WIDTH = 1920U;

///The height of the SFMl screen the game takes place.
unsigned const int G_VIEW_HEIGHT = 1080U;

#endif // !GLOBALS_H