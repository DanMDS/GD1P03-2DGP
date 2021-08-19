#include "PaintToolManager.h"
#include <math.h>
#include <iostream>
#include <cstdlib>

CPaintToolManager::CPaintToolManager()
{
	
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

void CPaintToolManager::DrawPen(sf::Vector2i* _MousePos, int _BrushSize, sf::Color* _PenColour)
{
	for (int i = -_BrushSize; i < _BrushSize / 2; i++)
	{
		for (int j = -_BrushSize; j < _BrushSize / 2; j++)
		{
			Canvas.setPixel(_MousePos->x + j, _MousePos->y + i, *_PenColour);
		}
	}
}

sf::RectangleShape* CPaintToolManager::DrawRect(sf::Vector2i* _MousePos, sf::Color* _PenColour, sf::RenderWindow* _Window)
{
	sf::RectangleShape* rect = new sf::RectangleShape();
	sf::Vector2f dimensions;

	sf::Vector2i MouseInitial = *_MousePos;
	sf::Vector2f Position = sf::Vector2f(MouseInitial);

	rect->setFillColor(*_PenColour);
	rect->setOutlineColor(sf::Color::White);
	rect->setOutlineThickness(10.0f);

	while (sf::Mouse::isButtonPressed(sf::Mouse::Right))
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

		_Window->clear();

		_Window->draw(CanvasSprite);

		for (int i = 0; i < shapes.size(); i++)
		{
			_Window->draw(*shapes[i]);
		}

		_Window->draw(*rect);
		_Window->display();
	}

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
	circ->setOutlineThickness(10.0f);

	while (sf::Mouse::isButtonPressed(sf::Mouse::Right))
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
		circ->setScale(sf::Vector2f(circ->getScale().x, ((_MousePos->x - MouseInitial.x) / (_MousePos->y - MouseInitial.y))));

		_Window->clear();

		_Window->draw(CanvasSprite);

		for (int i = 0; i < shapes.size(); i++)
		{
			_Window->draw(*shapes[i]);
		}

		_Window->draw(*circ);
		_Window->display();
	}

	return circ;
}
