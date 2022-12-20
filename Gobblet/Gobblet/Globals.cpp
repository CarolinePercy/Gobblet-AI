#include "Globals.h"

Gamestate g_gamestate = Gamestate::Gameplay;
Gamestate g_previousstate = Gamestate::Gameplay;
Status g_status = Status::OnGoing;
sf::Font g_font;
bool g_exitGame = false;