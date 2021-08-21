#include "PaintToolManager.h"
#include <math.h>
#include <iostream>
#include <cstdlib>

CPaintToolManager::CPaintToolManager()
{
	cursor.setRadius(5.0f);
	sf::Vector2i cursorPos;
	cursor.setOrigin(cursor.getRadius(), cursor.getRadius()); // Set circle origin to centre of circle with getRadius()
	cursor.setPosition(sf::Vector2f(cursorPos));
	cursor.setFillColor(sf::Color::Black);

	cursor.setOutlineColor(sf::Color::White);
	cursor.setOutlineThickness(2.0f);

	shapes.push_back(&cursor);

	isPaintDialogOpen = false;

	brushSize = 4;
}

CPaintToolManager::~CPaintToolManager()
{

}

sf::Color* CPaintToolManager::OpenPaintDialog(sf::Window* _windowRef, sf::Color* _Colourref)
{
	hwnd = _windowRef->getSystemHandle();

	// -- Initialise CHOOSECOLOR -- //
	ZeroMemory(&cc, sizeof(cc));
	cc.lStructSize = sizeof(cc);
	cc.hwndOwner = hwnd;

	cc.lpCustColors = (LPDWORD)acrCustClr;
	cc.rgbResult = rgbCurrent;
	cc.Flags = CC_FULLOPEN | CC_RGBINIT;

	if (ChooseColor(&cc) == TRUE) // if the user has chosen a colour when closing the color picker window
	{
		cr = cc.rgbResult;

		sf::Color tempColour;

		tempColour.r = GetRValue(cr);
		tempColour.g = GetGValue(cr);
		tempColour.b = GetBValue(cr);

		*_Colourref = tempColour; // Setting our circle to the new colour
		return _Colourref;
	}

}

void CPaintToolManager::DrawPen(sf::Vector2i* _MousePos, sf::Color* _PenColour)
{
	for (int i = -brushSize; i < brushSize; i++)
	{
		for (int j = -brushSize; j < brushSize; j++)
		{
			Canvas.setPixel(_MousePos->x + j, _MousePos->y + i, *_PenColour);
		}
	}
}

void CPaintToolManager::DrawShapes(sf::RenderWindow* _Window, sf::Shape* _Shape, sf::Vector2i* _MousePos)
{
	_Window->clear();

	_Window->draw(CanvasSprite);

	for (int i = 0; i < shapes.size(); i++)
	{
		_Window->draw(*shapes[i]);
	}

	_Window->draw(*_Shape);

	cursor.setPosition(sf::Vector2f(*_MousePos));

	_Window->display();
}

sf::RectangleShape* CPaintToolManager::DrawRect(sf::Vector2i* _MousePos, sf::Color* _PenColour, sf::RenderWindow* _Window)
{
	sf::RectangleShape* rect = new sf::RectangleShape();
	sf::Vector2f dimensions;

	sf::Vector2i MouseInitial = *_MousePos;
	sf::Vector2f Position = sf::Vector2f(MouseInitial);

	rect->setFillColor(*_PenColour);
	rect->setOutlineColor(sf::Color::White);
	rect->setOutlineThickness(1.0f);

	while (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		*_MousePos = sf::Mouse::getPosition(*_Window);

		dimensions.x = MouseInitial.x - _MousePos->x;
		dimensions.y = MouseInitial.y - _MousePos->y;

		if (dimensions.x < 0)
		{
			dimensions.x *= -1;
		}
		if (dimensions.y < 0)
		{
			dimensions.y *= -1;
		}

		if (MouseInitial.y < _MousePos->y)
		{
			if (MouseInitial.x < _MousePos->x)
			{
				Position = sf::Vector2f(MouseInitial);
			}
			else
			{
				Position = sf::Vector2f(_MousePos->x, MouseInitial.y);
			}
		}
		else
		{
			if (MouseInitial.x < _MousePos->x)
			{
				Position = sf::Vector2f(MouseInitial.x, _MousePos->y);
			}
			else
			{
				Position = sf::Vector2f(_MousePos->x, _MousePos->y);
			}
		}

		rect->setPosition(sf::Vector2f(Position));
		rect->setSize(sf::Vector2f(dimensions));

		DrawShapes(_Window, rect, _MousePos);
	}

	rect->setOutlineThickness(0.0f);
	return rect;
}

sf::CircleShape* CPaintToolManager::DrawCirc(sf::Vector2i* _MousePos, sf::Color* _PenColour, sf::RenderWindow* _Window)
{
	sf::CircleShape* circ = new sf::CircleShape();
	sf::Vector2f dimensions;

	sf::Vector2i MouseInitial = *_MousePos;
	sf::Vector2f Position = sf::Vector2f(MouseInitial);

	circ->setFillColor(*_PenColour);
	circ->setOutlineColor(sf::Color::White);
	circ->setOutlineThickness(1.0f);

	while (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		*_MousePos = sf::Mouse::getPosition(*_Window);

		dimensions.x = MouseInitial.x - _MousePos->x;
		dimensions.y = MouseInitial.y - _MousePos->y;

		if (dimensions.x < 0)
		{
			dimensions.x *= -1;
		}
		if (dimensions.y < 0)
		{
			dimensions.y *= -1;
		}

		if (MouseInitial.y < _MousePos->y)
		{
			if (MouseInitial.x < _MousePos->x)
			{
				Position = sf::Vector2f(MouseInitial);
			}
			else
			{
				Position = sf::Vector2f(_MousePos->x, MouseInitial.y);
			}
		}
		else
		{
			if (MouseInitial.x < _MousePos->x)
			{
				Position = sf::Vector2f(MouseInitial.x, _MousePos->y);
			}
			else
			{
				Position = sf::Vector2f(_MousePos->x, _MousePos->y);
			}
		}

		circ->setRadius(dimensions.x / 2);
		circ->setPosition(sf::Vector2f(Position));

		circ->setScale(sf::Vector2f(circ->getScale().x, abs(MouseInitial.y - _MousePos->y) / circ->getRadius() / 2));

		DrawShapes(_Window, circ, _MousePos);
	}

	circ->setOutlineThickness(0.0f);
	return circ;
}

sf::RectangleShape* CPaintToolManager::DrawLine(sf::Vector2i* _MousePos, sf::Color* _PenColour, sf::RenderWindow* _Window)
{
	sf::RectangleShape* line = new sf::RectangleShape();
	sf::Vector2f dimensions;

	line->setPosition(sf::Vector2f(_MousePos->x, _MousePos->y));
	line->setFillColor(*_PenColour);

	float sideOpp;
	float sideAdj;
	float sideHyp;
	float angle;
	float pi = 3.141592654f;

	while (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		*_MousePos = sf::Mouse::getPosition(*_Window);

		sf::Vector2f linePosition = sf::Vector2f(line->getPosition().x, line->getPosition().y + brushSize / 2);

		sideOpp = _MousePos->y - linePosition.y;
		sideAdj = _MousePos->x - linePosition.x;
		sideHyp = sqrt((sideOpp * sideOpp) + (sideAdj * sideAdj));

		dimensions = sf::Vector2f(sideHyp, brushSize);

		angle = atan2(sideOpp, sideAdj) * (180 / pi);

		line->setRotation(angle);
		line->setSize(dimensions);

		DrawShapes(_Window, line, _MousePos);
	}

	return line;
}