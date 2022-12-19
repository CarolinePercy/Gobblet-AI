#ifndef GLOBALS_H
#define GLOBALS_H
#include <SFML/Graphics.hpp>

#include <SFML/Graphics.hpp>

enum class Gamestate
{
	MainMenu,
	Gameplay,
	Help
};

extern Gamestate g_gamestate;

extern sf::Font g_font;

extern bool g_exitGame;

unsigned const int G_VIEW_WIDTH = 1280U;
unsigned const int G_VIEW_HEIGHT = 720U;

#endif // !GLOBALS_H