#ifndef GLOBALS_H
#define GLOBALS_H
#include <SFML/Graphics.hpp>
#include <iostream>

enum class Gamestate
{
	MainMenu,
	Gameplay,
	Help
};

enum class Status
{
	OnGoing,
	Player1Wins,
	Player2Wins
};

extern Gamestate g_gamestate;
extern Status g_status;

extern sf::Font g_font;

extern bool g_exitGame;

unsigned const int G_VIEW_WIDTH = 1920U;
unsigned const int G_VIEW_HEIGHT = 1080U;

#endif // !GLOBALS_H