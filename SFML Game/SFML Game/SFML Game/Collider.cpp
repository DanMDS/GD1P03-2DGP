#include "Collider.h"

void Collider::MoveCollider(sf::Vector2f _pos)
{
	for (itBoundsVec = boundsVec.begin(); itBoundsVec != boundsVec.end(); itBoundsVec++)
	{
		(*itBoundsVec)->setPosition(_pos);
	}
}

void Collider::UpdateColliders(int* _levelIndex)
{
	// Changing position and size of level colliders depending on level index
	switch (*_levelIndex)
	{
	case -1:
		colObs1->setSize(sf::Vector2f(10, 10));
		colObs1->setPosition(sf::Vector2f(-20, -20));

		colObs2->setSize(sf::Vector2f(10, 10));
		colObs2->setPosition(sf::Vector2f(-20, -20));

		colObs3->setSize(sf::Vector2f(10, 10));
		colObs3->setPosition(sf::Vector2f(-20, -20));

		colObs4->setSize(sf::Vector2f(10, 10));
		colObs4->setPosition(sf::Vector2f(-20, -20));

		break;
	case 0:
		colObs1->setSize(sf::Vector2f(1000, 38));
		colObs1->setPosition(sf::Vector2f(38, 200));

		colObs2->setSize(sf::Vector2f(1000, 38));
		colObs2->setPosition(sf::Vector2f(38, 482));

		colObs3->setSize(sf::Vector2f(10, 10));
		colObs3->setPosition(sf::Vector2f(-20, -20));

		colObs4->setSize(sf::Vector2f(10, 10));
		colObs4->setPosition(sf::Vector2f(-20, -20));

		break;
	case 1:
		colObs1->setSize(sf::Vector2f(10, 10));
		colObs1->setPosition(sf::Vector2f(-20, -20));

		colObs2->setSize(sf::Vector2f(10, 10));
		colObs2->setPosition(sf::Vector2f(-20, -20));

		colObs3->setSize(sf::Vector2f(10, 10));
		colObs3->setPosition(sf::Vector2f(-20, -20));

		colObs4->setSize(sf::Vector2f(10, 10));
		colObs4->setPosition(sf::Vector2f(-20, -20));

		break;
	case 2:
		colObs1->setSize(sf::Vector2f(10, 10));
		colObs1->setPosition(sf::Vector2f(-20, -20));

		colObs2->setSize(sf::Vector2f(10, 10));
		colObs2->setPosition(sf::Vector2f(-20, -20));

		colObs3->setSize(sf::Vector2f(10, 10));
		colObs3->setPosition(sf::Vector2f(-20, -20));

		colObs4->setSize(sf::Vector2f(10, 10));
		colObs4->setPosition(sf::Vector2f(-20, -20));

		break;
	case 3:
		colObs1->setSize(sf::Vector2f(10, 10));
		colObs1->setPosition(sf::Vector2f(-20, -20));

		colObs2->setSize(sf::Vector2f(10, 10));
		colObs2->setPosition(sf::Vector2f(-20, -20));

		colObs3->setSize(sf::Vector2f(10, 10));
		colObs3->setPosition(sf::Vector2f(-20, -20));

		colObs4->setSize(sf::Vector2f(10, 10));
		colObs4->setPosition(sf::Vector2f(-20, -20));

		break;
	case 4:
		colObs1->setSize(sf::Vector2f(10, 10));
		colObs1->setPosition(sf::Vector2f(-20, -20));

		colObs2->setSize(sf::Vector2f(10, 10));
		colObs2->setPosition(sf::Vector2f(-20, -20));

		colObs3->setSize(sf::Vector2f(10, 10));
		colObs3->setPosition(sf::Vector2f(-20, -20));

		colObs4->setSize(sf::Vector2f(10, 10));
		colObs4->setPosition(sf::Vector2f(-20, -20));

		break;
	case 5:
		colObs1->setSize(sf::Vector2f(10, 10));
		colObs1->setPosition(sf::Vector2f(-20, -20));

		colObs2->setSize(sf::Vector2f(10, 10));
		colObs2->setPosition(sf::Vector2f(-20, -20));

		colObs3->setSize(sf::Vector2f(10, 10));
		colObs3->setPosition(sf::Vector2f(-20, -20));

		colObs4->setSize(sf::Vector2f(10, 10));
		colObs4->setPosition(sf::Vector2f(-20, -20));

		break;
	case 6:
		colObs1->setSize(sf::Vector2f(10, 10));
		colObs1->setPosition(sf::Vector2f(-20, -20));

		colObs2->setSize(sf::Vector2f(10, 10));
		colObs2->setPosition(sf::Vector2f(-20, -20));

		colObs3->setSize(sf::Vector2f(10, 10));
		colObs3->setPosition(sf::Vector2f(-20, -20));

		colObs4->setSize(sf::Vector2f(10, 10));
		colObs4->setPosition(sf::Vector2f(-20, -20));

		break;
	case 7:
		colObs1->setSize(sf::Vector2f(10, 10));
		colObs1->setPosition(sf::Vector2f(-20, -20));

		colObs2->setSize(sf::Vector2f(10, 10));
		colObs2->setPosition(sf::Vector2f(-20, -20));

		colObs3->setSize(sf::Vector2f(10, 10));
		colObs3->setPosition(sf::Vector2f(-20, -20));

		colObs4->setSize(sf::Vector2f(10, 10));
		colObs4->setPosition(sf::Vector2f(-20, -20));

		break;
	case 8:
		colObs1->setSize(sf::Vector2f(10, 10));
		colObs1->setPosition(sf::Vector2f(-20, -20));

		colObs2->setSize(sf::Vector2f(10, 10));
		colObs2->setPosition(sf::Vector2f(-20, -20));

		colObs3->setSize(sf::Vector2f(10, 10));
		colObs3->setPosition(sf::Vector2f(-20, -20));

		colObs4->setSize(sf::Vector2f(10, 10));
		colObs4->setPosition(sf::Vector2f(-20, -20));

		break;
	case 9:
		colObs1->setSize(sf::Vector2f(10, 10));
		colObs1->setPosition(sf::Vector2f(-20, -20));

		colObs2->setSize(sf::Vector2f(10, 10));
		colObs2->setPosition(sf::Vector2f(-20, -20));

		colObs3->setSize(sf::Vector2f(10, 10));
		colObs3->setPosition(sf::Vector2f(-20, -20));

		colObs4->setSize(sf::Vector2f(10, 10));
		colObs4->setPosition(sf::Vector2f(-20, -20));

		break;
	}
}

void Collider::DrawColliders(sf::RenderWindow* _window, bool _draw)
{
	for (itBoundsVec = boundsVec.begin(); itBoundsVec != boundsVec.end(); itBoundsVec++)
	{
		if (_draw)
		{
			(*itBoundsVec)->setOutlineColor(sf::Color::Blue);
		}
		else
		{
			(*itBoundsVec)->setOutlineColor(sf::Color::Transparent);
		}
		_window->draw(*(*itBoundsVec));
	}
}
 
int Collider::GetSize()
{
	return boundsVec.size();
}

Collider::Collider(sf::Vector2f _colDim, bool _level)
{
	m_colliderColour = new sf::Color(68, 68, 68);

	m_colTop = m_colBottom = m_colLeft = m_colRight = false;

	if (_level)
	{
		colWidth = 38;

		// Adding top level collider
		colBoundsTop = new sf::RectangleShape(sf::Vector2f(_colDim.x, colWidth));
		colBoundsTop->setOutlineColor(sf::Color::Blue);
		colBoundsTop->setFillColor(sf::Color::Transparent);
		colBoundsTop->setOutlineThickness(1);
		boundsVec.push_back(colBoundsTop);

		// Adding bottom level collider
		colBoundsBottom = new sf::RectangleShape(sf::Vector2f(_colDim.x, colWidth));
		colBoundsBottom->setOutlineColor(sf::Color::Blue);
		colBoundsBottom->setFillColor(sf::Color::Transparent);
		colBoundsBottom->setOutlineThickness(1);
		colBoundsBottom->setPosition(sf::Vector2f(0, _colDim.y - colWidth));
		boundsVec.push_back(colBoundsBottom);

		// Adding left level collider
		colBoundsLeft = new sf::RectangleShape(sf::Vector2f(colWidth, _colDim.y));
		colBoundsLeft->setOutlineColor(sf::Color::Blue);
		colBoundsLeft->setFillColor(sf::Color::Transparent);
		colBoundsLeft->setOutlineThickness(1);
		boundsVec.push_back(colBoundsLeft);

		// Adding right level collider
		colBoundsRight = new sf::RectangleShape(sf::Vector2f(colWidth, _colDim.y));
		colBoundsRight->setOutlineColor(sf::Color::Blue);
		colBoundsRight->setFillColor(sf::Color::Transparent);
		colBoundsRight->setOutlineThickness(1);
		colBoundsRight->setPosition(sf::Vector2f(_colDim.x - colWidth, 0));
		boundsVec.push_back(colBoundsRight);

		// Adding level obstacle colliders
		colObs1 = new sf::RectangleShape(sf::Vector2f(10, 10));
		colObs1->setOutlineColor(sf::Color::Blue);
		colObs1->setFillColor(*m_colliderColour);
		colObs1->setOutlineThickness(1);
		colObs1->setPosition(sf::Vector2f(-20, -20));
		boundsVec.push_back(colObs1);

		colObs2 = new sf::RectangleShape(sf::Vector2f(10, 10));
		colObs2->setOutlineColor(sf::Color::Blue);
		colObs2->setFillColor(*m_colliderColour);
		colObs2->setOutlineThickness(1);
		colObs2->setPosition(sf::Vector2f(-20, -20));
		boundsVec.push_back(colObs2);

		colObs3 = new sf::RectangleShape(sf::Vector2f(10, 10));
		colObs3->setOutlineColor(sf::Color::Blue);
		colObs3->setFillColor(*m_colliderColour);
		colObs3->setOutlineThickness(1);
		colObs3->setPosition(sf::Vector2f(-20, -20));
		boundsVec.push_back(colObs3);

		colObs4 = new sf::RectangleShape(sf::Vector2f(10, 10));
		colObs4->setOutlineColor(sf::Color::Blue);
		colObs4->setFillColor(*m_colliderColour);
		colObs4->setOutlineThickness(1);
		colObs4->setPosition(sf::Vector2f(-20, -20));
		boundsVec.push_back(colObs4);
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

		// Setting level colliders to null for non-level objects
		colObs1 = nullptr;
		colObs2 = nullptr;
		colObs3 = nullptr;
		colObs4 = nullptr;
	}
}

Collider::~Collider()
{
	for (itBoundsVec = boundsVec.begin(); itBoundsVec != boundsVec.end(); itBoundsVec++)
	{
		sf::RectangleShape* temp = *itBoundsVec;
		delete temp;
		temp = nullptr;
	}
	boundsVec.clear();

	delete m_colliderColour;
	m_colliderColour = nullptr;
}
