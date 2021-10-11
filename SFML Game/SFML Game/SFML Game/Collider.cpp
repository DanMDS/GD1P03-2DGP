#include "Collider.h"
#include <iostream>

void Collider::MoveCollider(sf::Vector2f _pos)
{
	for (itBoundsVec = boundsVec.begin(); itBoundsVec != boundsVec.end(); itBoundsVec++)
	{
		(*itBoundsVec)->setPosition(_pos);
	}
}

void Collider::UpdateColliders(int* _levelIndex)
{
	// Deleting all colliders except the level walls
	if (boundsVec.size() > 4)
	{
		while (boundsVec.size() != 4)
		{
			itBoundsVec = boundsVec.end() - 1;
			delete* itBoundsVec;
			*itBoundsVec = nullptr;
			boundsVec.erase(itBoundsVec);
		}
	}
	
	// Changing position and size of level colliders depending on level index
	switch (*_levelIndex)
	{
	case -1:

		break;
	case 0:
		colObs = new sf::RectangleShape(sf::Vector2f(1000, 38));
		colObs->setFillColor(*m_colliderColour);
		colObs->setOutlineColor(sf::Color::Blue);
		colObs->setOutlineThickness(1);
		colObs->setPosition(sf::Vector2f(38, 200));
		boundsVec.push_back(colObs);


		colObs = new sf::RectangleShape(sf::Vector2f(1000, 38));
		colObs->setFillColor(*m_colliderColour);
		colObs->setOutlineColor(sf::Color::Blue);
		colObs->setOutlineThickness(1);
		colObs->setPosition(sf::Vector2f(38, 482));
		boundsVec.push_back(colObs);

		break;
	case 1:

		break;
	case 2:

		break;
	case 3:

		break;
	case 4:
		colObs = new sf::RectangleShape(sf::Vector2f(38, 450));
		colObs->setFillColor(*m_colliderColour);
		colObs->setOutlineColor(sf::Color::Blue);
		colObs->setOutlineThickness(1);
		colObs->setPosition(sf::Vector2f(300, 38));
		boundsVec.push_back(colObs);

		colObs = new sf::RectangleShape(sf::Vector2f(38, 450));
		colObs->setFillColor(*m_colliderColour);
		colObs->setOutlineColor(sf::Color::Blue);
		colObs->setOutlineThickness(1);
		colObs->setPosition(sf::Vector2f(942, 38));
		boundsVec.push_back(colObs);

		colObs = new sf::RectangleShape(sf::Vector2f(38, 450));
		colObs->setFillColor(*m_colliderColour);
		colObs->setOutlineColor(sf::Color::Blue);
		colObs->setOutlineThickness(1);
		colObs->setPosition(sf::Vector2f(510, 232));
		boundsVec.push_back(colObs);

		colObs = new sf::RectangleShape(sf::Vector2f(38, 450));
		colObs->setFillColor(*m_colliderColour);
		colObs->setOutlineColor(sf::Color::Blue);
		colObs->setOutlineThickness(1);
		colObs->setPosition(sf::Vector2f(732, 232));
		boundsVec.push_back(colObs);

		break;
	case 5:
		colObs = new sf::RectangleShape(sf::Vector2f(38, 267));
		colObs->setFillColor(*m_colliderColour);
		colObs->setOutlineColor(sf::Color::Blue);
		colObs->setOutlineThickness(1);
		colObs->setPosition(sf::Vector2f(200, 245));
		boundsVec.push_back(colObs);

		colObs = new sf::RectangleShape(sf::Vector2f(1080, 38));
		colObs->setFillColor(*m_colliderColour);
		colObs->setOutlineColor(sf::Color::Blue);
		colObs->setOutlineThickness(1);
		colObs->setPosition(sf::Vector2f(200, 208));
		boundsVec.push_back(colObs);

		colObs = new sf::RectangleShape(sf::Vector2f(880, 38));
		colObs->setFillColor(*m_colliderColour);
		colObs->setOutlineColor(sf::Color::Blue);
		colObs->setOutlineThickness(1);
		colObs->setPosition(sf::Vector2f(400, 475));
		boundsVec.push_back(colObs);

		break;
	case 6:

		break;
	case 7:

		break;
	case 8:
		colObs = new sf::RectangleShape(sf::Vector2f(1000, 76));
		colObs->setFillColor(*m_colliderColour);
		colObs->setOutlineColor(sf::Color::Blue);
		colObs->setOutlineThickness(1);
		colObs->setPosition(sf::Vector2f(242, 400));
		boundsVec.push_back(colObs);

		colObs = new sf::RectangleShape(sf::Vector2f(1000, 76));
		colObs->setFillColor(*m_colliderColour);
		colObs->setOutlineColor(sf::Color::Blue);
		colObs->setOutlineThickness(1);
		colObs->setPosition(sf::Vector2f(242, 245));
		boundsVec.push_back(colObs);

		break;
	case 9:
		colObs = new sf::RectangleShape(sf::Vector2f(100, 100));
		colObs->setFillColor(*m_colliderColour);
		colObs->setOutlineColor(sf::Color::Blue);
		colObs->setOutlineThickness(1);
		colObs->setPosition(sf::Vector2f(425, 150));
		boundsVec.push_back(colObs);

		colObs = new sf::RectangleShape(sf::Vector2f(100, 100));
		colObs->setFillColor(*m_colliderColour);
		colObs->setOutlineColor(sf::Color::Blue);
		colObs->setOutlineThickness(1);
		colObs->setPosition(sf::Vector2f(755, 150));
		boundsVec.push_back(colObs);

		colObs = new sf::RectangleShape(sf::Vector2f(100, 100));
		colObs->setFillColor(*m_colliderColour);
		colObs->setOutlineColor(sf::Color::Blue);
		colObs->setOutlineThickness(1);
		colObs->setPosition(sf::Vector2f(425, 470));
		boundsVec.push_back(colObs);

		colObs = new sf::RectangleShape(sf::Vector2f(100, 100));
		colObs->setFillColor(*m_colliderColour);
		colObs->setOutlineColor(sf::Color::Blue);
		colObs->setOutlineThickness(1);
		colObs->setPosition(sf::Vector2f(755, 470));
		boundsVec.push_back(colObs);

		break;
	}
}

void Collider::DrawColliders(sf::RenderWindow* _window, bool _draw)
{
	// Drawing colliders
	for (auto& itr : boundsVec)
	{
		if (_draw)
		{
			itr->setOutlineColor(sf::Color::Blue);
		}
		else
		{
			itr->setOutlineColor(sf::Color::Transparent);
		}
		_window->draw(*itr);
	}
}
 
int Collider::GetSize()
{
	return boundsVec.size();
}

Collider::Collider(sf::Vector2f _colDim, bool _level)
{
	// Initialising variables and adding colliders
	m_colliderColour = new sf::Color(68, 68, 68);

	m_colTop = m_colBottom = m_colLeft = m_colRight = false;

	colObs = new sf::RectangleShape();
	colObs->setFillColor(*m_colliderColour);
	colObs->setOutlineColor(sf::Color::Blue);
	colObs->setOutlineThickness(1);

	if (_level)
	{
		colWidth = 38;

		// Adding top level collider
		colObs = new sf::RectangleShape(sf::Vector2f(_colDim.x, colWidth));
		colObs->setFillColor(*m_colliderColour);
		colObs->setOutlineColor(sf::Color::Blue);
		colObs->setOutlineThickness(1);
		boundsVec.push_back(colObs);

		// Adding bottom level collider
		colObs = new sf::RectangleShape(sf::Vector2f(_colDim.x, colWidth));
		colObs->setFillColor(*m_colliderColour);
		colObs->setOutlineColor(sf::Color::Blue);
		colObs->setOutlineThickness(1);
		colObs->setPosition(sf::Vector2f(0, _colDim.y - colWidth));
		boundsVec.push_back(colObs);

		// Adding left level collider
		colObs = new sf::RectangleShape(sf::Vector2f(colWidth, _colDim.y));
		colObs->setFillColor(*m_colliderColour);
		colObs->setOutlineColor(sf::Color::Blue);
		colObs->setOutlineThickness(1);
		colObs->setPosition(sf::Vector2f(0, 0));
		boundsVec.push_back(colObs);

		// Adding right level collider
		colObs = new sf::RectangleShape(sf::Vector2f(colWidth, _colDim.y));
		colObs->setFillColor(*m_colliderColour);
		colObs->setOutlineColor(sf::Color::Blue);
		colObs->setOutlineThickness(1);
		colObs->setPosition(sf::Vector2f(_colDim.x - colWidth, 0));
		boundsVec.push_back(colObs);

		// Setting other colliders to null
		colBoundsBottom = colBoundsLeft = colBoundsRight = colBoundsTop = nullptr;
	}
	else
	{
		colWidth = 7;

		// Adding top collider
		colBoundsTop = new sf::RectangleShape(sf::Vector2f(_colDim.x - 2, colWidth));
		colBoundsTop->setOutlineColor(sf::Color::Blue);
		colBoundsTop->setFillColor(sf::Color::Transparent);
		colBoundsTop->setOutlineThickness(1);
		colBoundsTop->setOrigin(colBoundsTop->getSize().x / 2, _colDim.y / 2 + colWidth);
		boundsVec.push_back(colBoundsTop);

		// Adding bottom collider
		colBoundsBottom = new sf::RectangleShape(sf::Vector2f(_colDim.x - 2, colWidth));
		colBoundsBottom->setOutlineColor(sf::Color::Blue);
		colBoundsBottom->setFillColor(sf::Color::Transparent);
		colBoundsBottom->setOutlineThickness(1);
		colBoundsBottom->setOrigin(colBoundsBottom->getSize().x / 2, -_colDim.y / 2);
		boundsVec.push_back(colBoundsBottom);

		// Adding left collider
		colBoundsLeft = new sf::RectangleShape(sf::Vector2f(colWidth, _colDim.y - 2));
		colBoundsLeft->setOutlineColor(sf::Color::Blue);
		colBoundsLeft->setFillColor(sf::Color::Transparent);
		colBoundsLeft->setOutlineThickness(1);
		colBoundsLeft->setOrigin(_colDim.x / 2 + colWidth, colBoundsLeft->getSize().y / 2);
		boundsVec.push_back(colBoundsLeft);

		// Adding right collider
		colBoundsRight = new sf::RectangleShape(sf::Vector2f(colWidth, _colDim.y - 2));
		colBoundsRight->setOutlineColor(sf::Color::Blue);
		colBoundsRight->setFillColor(sf::Color::Transparent);
		colBoundsRight->setOutlineThickness(1);
		colBoundsRight->setOrigin(-_colDim.x / 2, colBoundsRight->getSize().y / 2);
		boundsVec.push_back(colBoundsRight);

		// Setting other collider to null
		colObs = nullptr;
	}
}

Collider::~Collider()
{
	// Deallocating memory
	for (auto& itr : boundsVec)
	{
		delete itr;
		itr = nullptr;
	}
	boundsVec.clear();

	delete m_colliderColour;
	m_colliderColour = nullptr;
}
