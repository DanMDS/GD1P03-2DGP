#include <SFML/Graphics.hpp>
#include <vector>

#pragma once

class Collider
{
private:
	// Values for width and colour of colliders
	int colWidth;
	sf::Color* m_colliderColour;

public:
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
	int GetSize();

	Collider(sf::Vector2f _colDim, bool _level = false);
	~Collider();
};