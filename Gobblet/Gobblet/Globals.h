#ifndef GLOBALS_H
#define GLOBALS_H

enum class Gamestate
{
	MainMenu,
	Gameplay,
	Help
};

extern Gamestate g_gamestate;

#endif // !GLOBALS_H