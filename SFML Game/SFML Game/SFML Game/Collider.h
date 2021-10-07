#include <SFML/Graphics.hpp>
#include <vector>

#pragma once

class Collider
{
private:
	int colWidth;
	sf::Color* m_colliderColour;

public:
	bool m_colTop;
	bool m_colBottom;
	bool m_colLeft;
	bool m_colRight;

	std::vector<sf::RectangleShape*> boundsVec;
	std::vector<sf::RectangleShape*>::iterator itBoundsVec;

	sf::RectangleShape* colBoundsTop;
	sf::RectangleShape* colBoundsBottom;
	sf::RectangleShape* colBoundsLeft;
	sf::RectangleShape* colBoundsRight;
	sf::RectangleShape* colObs1;
	sf::RectangleShape* colObs2;
	sf::RectangleShape* colObs3;
	sf::RectangleShape* colObs4;

	void DrawColliders(sf::RenderWindow* _window, bool _draw);
	void MoveCollider(sf::Vector2f _pos);
	void UpdateColliders(int* _levelIndex);
	int GetSize();

	Collider(sf::Vector2f _colDim, bool _level = false);
	~Collider();
};