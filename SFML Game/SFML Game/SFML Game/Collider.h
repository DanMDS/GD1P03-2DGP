#include <SFML/Graphics.hpp>
#include <vector>

#pragma once
/*
	Class: collider
	Description: Easily handles colliders for objects that create them in their constructors
	Written by: Daniel Bolleboom
*/
class Collider
{
private:
	// Values for width and colour of colliders
	int colWidth;
	sf::Color* m_colliderColour;

public:
	// Keeping these public since getting and setting with methods
	// would make this way more tedious than it needs to be, plus 
	// players and enemies need to change these bools a lot
	
	// Booleans for player and enemy movement
	bool m_colTop;
	bool m_colBottom;
	bool m_colLeft;
	bool m_colRight;

	// Vector for colliders for easy access
	std::vector<sf::RectangleShape*> boundsVec;
	std::vector<sf::RectangleShape*>::iterator itBoundsVec;

	// Separate colliders for all 4 sides for player and enemy movement
	sf::RectangleShape* colBoundsTop;
	sf::RectangleShape* colBoundsBottom;
	sf::RectangleShape* colBoundsLeft;
	sf::RectangleShape* colBoundsRight;
	sf::RectangleShape* colObs;

	// Methods
	void DrawColliders(sf::RenderWindow* _window, bool _draw);
	void MoveCollider(sf::Vector2f _pos);
	void UpdateColliders(int* _levelIndex);

	// Getters
	int GetSize() { return boundsVec.size(); };

	Collider(sf::Vector2f _colDim, bool _level = false);
	~Collider();
};