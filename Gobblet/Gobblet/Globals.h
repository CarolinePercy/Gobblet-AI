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
	Player2Wins
};

///The current screen the user is on.
extern Gamestate g_gamestate;

///The previous screen the user was on.
extern Gamestate g_previousstate;

/// The status of the board game - who won, or if it is still going.
extern Status g_status;

extern bool g_yourTurn;

///The font used throughout the game.
extern sf::Font g_font;

///Bool that controls when the game ends.
extern bool g_exitGame;

/// How far the AI should go in Minimax, before cutting it off and making an estimate. Saves on time.
extern int g_maxDepth;

///The width of the SFMl screen the game takes place.
unsigned const int G_VIEW_WIDTH = 1920U;

///The height of the SFMl screen the game takes place.
unsigned const int G_VIEW_HEIGHT = 1080U;

#endif // !GLOBALS_H