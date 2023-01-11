#pragma once
#include "Globals.h"

/// <summary>
/// Gobblet class. Is one of the pieces on the board in Grid.
/// </summary>

class Gobblet
{
public:
	Gobblet(int t_size, bool t_isPlayer);
	void render(sf::RenderWindow& t_window);

	/// <summary>
	/// Returns the Gobblet underneath this one, if there is one.
	/// </summary>
	/// <returns>The gobblet underneath this one.</returns>
	Gobblet* getChild() { return m_child; }

	/// <summary>
	/// Sets the gobblet underneath this one. Used for when this piece is moved on top of another.
	/// </summary>
	/// <param name="t_child">The new gobblet under this one.</param>
	void setChild(Gobblet* t_child) { m_child = t_child;  };

	/// <summary>
	/// 
	/// </summary>
	/// <param name="t_position">The new position of this gobblet piece.</param>
	void setPosition(sf::Vector2f t_position) { m_gobblet.setPosition(t_position); }

	/// <summary>
	/// Moves the gobblet along a straight line.
	/// </summary>
	void moveAlong(sf::Vector2f t_addedMove) { m_gobblet.move(t_addedMove); }

	/// <summary>
	/// Returns the position of the Gobblet.
	/// </summary>
	sf::Vector2f getPosition() { return sf::Vector2f(m_gobblet.getPosition().x - m_gobblet.getRadius(),
		m_gobblet.getPosition().y - m_gobblet.getRadius()); }

	/// <summary>
	/// 
	/// </summary>
	/// <returns>The size of this gobblet.</returns>
	int getSize() { return size; }

	/// <summary>
	/// Returns whether this piece belongs to the player or AI. Used to make sure the player can't move the AI's pieces.
	/// </summary>
	/// <returns>Whether this piece is controlled by the player.</returns>
	bool isControlledByPlayer() { return controlledByPlayer; };
private:

	///The appearance of this Gobblet.
	sf::CircleShape m_gobblet;

	///What gobblet piece is underneath this one.
	Gobblet* m_child;

	///The size of this Gobblet piece.
	int size = -1;

	///Whether this piece is controlled by the player or AI.
	bool controlledByPlayer;
};
