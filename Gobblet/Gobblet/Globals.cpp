#include "Globals.h"

Gamestate g_gamestate = Gamestate::MainMenu;
Gamestate g_previousstate = Gamestate::MainMenu;
Status g_status = Status::OnGoing;
sf::Font g_font;
bool g_exitGame = false;
bool g_yourTurn = true;