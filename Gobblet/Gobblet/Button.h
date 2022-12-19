#pragma once
#include "Globals.h"

/// <summary>
///A button class, that keeps track of when it it hovered over, pressed, and what it looks like.
/// </summary>

class Button
{
public:
	Button(sf::Vector2f t_pos, sf::Vector2f t_size, std::string t_buttonText, sf::Color t_idle, sf::Color t_hover, sf::Color t_click);
	void onMouseDown();
	bool onMouseUp();
	void update(sf::Vector2i t_pos);
	void render(sf::RenderWindow& t_window);
private:

	///The physical design of the button.
	sf::RectangleShape button;

	///The text that appears on the button, telling the user what it will do once clicked.
	sf::Text buttonText;

	///The colour the button will be when idle.
	sf::Color idleColor;

	///The colour the button will be when hovered over.
	sf::Color hoverColor;

	///The colour the button will be when clicked.
	sf::Color clickColor;

	///Whether the mouse is currently hovering over this button.
	bool hover = false;

	///Whether the mouse is currently clicking on this button.
	bool clicking = false;

	void changeColor();
};
