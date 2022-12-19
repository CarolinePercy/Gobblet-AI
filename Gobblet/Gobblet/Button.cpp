#include "Button.h"

/// <summary>
/// Overloaded Constructor of the Button class.
/// </summary>
/// <param name="t_pos">The position of the button.</param>
/// <param name="t_size">The size of the button.</param>
/// <param name="t_buttonText">What the button should say on it.</param>
/// <param name="t_idle">What colour the button should be when not interacted with.</param>
/// <param name="t_hover">What colour the button should be when its hovered over.</param>
/// <param name="t_click">What colour the button should be when its clicked.</param>
Button::Button(sf::Vector2f t_pos, sf::Vector2f t_size, std::string t_buttonText, sf::Color t_idle, sf::Color t_hover, sf::Color t_click) :
	idleColor(t_idle), hoverColor(t_hover), clickColor(t_click)
{
	button.setPosition(t_pos);
	button.setSize(t_size);
	button.setFillColor(idleColor);
	button.setOutlineThickness(5);

	buttonText.setFont(g_font);
	buttonText.setString(t_buttonText);
	buttonText.setCharacterSize(40);
	buttonText.setFillColor(sf::Color::Black);
	buttonText.setPosition(t_pos.x + (t_size.x / 2.0f), t_pos.y + (t_size.y / 2.0f));
	buttonText.setOrigin(buttonText.getLocalBounds().width / 2.0f, buttonText.getLocalBounds().height / 2.0f);
}

/// <summary>
/// Method that is called when the player releases the left mouse button.
/// </summary>
void Button::onMouseDown()
{
	if (hover)
	{
		clicking = true;
	}
}

/// <summary>
/// Method that is called when the player clicks down the left mouse button.
/// </summary>
/// <returns>Whether the mouse is hovering over the button.</returns>
bool Button::onMouseUp()
{
	clicking = false;
	return hover;
}

/// <summary>
/// Checks the current status of this button, like it's colour and whether its being hovered over.
/// </summary>
/// <param name="t_pos">The position of the mouse on the screen.</param>
void Button::update(sf::Vector2i t_pos)
{
	sf::Vector2f pos = button.getPosition();
	sf::Vector2f size = button.getSize();
	if (t_pos.x > pos.x && t_pos.x < pos.x + size.x &&
		t_pos.y > pos.y && t_pos.y < pos.y + size.y)
	{
		hover = true;
	}
	else
	{
		hover = false;
	}
	changeColor();
}

/// <summary>
/// Draws the button and its text to the screen.
/// </summary>
/// <param name="t_window">The window to draw to.</param>
void Button::render(sf::RenderWindow& t_window)
{
	t_window.draw(button);
	t_window.draw(buttonText);
}

/// <summary>
/// Changes the colour of the button, depending on how the player is interacting with it.
/// </summary>
void Button::changeColor()
{
	if (clicking)
	{
		button.setFillColor(clickColor);
	}
	else if (hover)
	{
		button.setFillColor(hoverColor);
	}
	else
	{
		button.setFillColor(idleColor);
	}
}
