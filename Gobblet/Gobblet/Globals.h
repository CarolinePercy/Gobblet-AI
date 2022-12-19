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

#endif // !GLOBALS_H