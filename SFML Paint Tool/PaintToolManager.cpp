#include "PaintToolManager.h"
#include <math.h>
#include <iostream>
#include <cstdlib>

CPaintToolManager::CPaintToolManager()
{
	cursor.setSize(sf::Vector2f(5.0f, 5.0f));
	sf::Vector2i cursorPos;
	cursor.setOrigin(cursor.getSize().x / 2, cursor.getSize().y / 2); // Set circle origin to centre of circle with getRadius()
	cursor.setPosition(sf::Vector2f(cursorPos));
	cursor.setFillColor(sf::Color::Black);
	cursor.setOutlineColor(sf::Color::White);
	cursor.setOutlineThickness(2.0f);

	if (!font.loadFromFile("ARIAL.TTF"))
	{
		std::cout << "load fail: Font";
	}

	toolbarColourText.setFont(font);
	toolbarColourText.setString("Colour Picker: ");
	toolbarColourText.setCharacterSize(15);
	toolbarColourText.setFillColor(sf::Color::White);

	if (!toolbarPenImage.loadFromFile("images/brush.bmp"))
	{
		std::cout << "load fail: Brush";
	}
	toolbarPenImage.createMaskFromColor(sf::Color::Black);

	toolbarPenText.loadFromImage(toolbarPenImage);

	toolbarPenSprite.setTexture(toolbarPenText);
	toolbarPenSprite.setScale(toolbarPenSprite.getScale().y / 5, toolbarPenSprite.getScale().y / 5);
	toolbarPenSprite.setPosition(4, 5);

	if (!toolbarStampImage.loadFromFile("images/toolbarStamp.bmp"))
	{
		std::cout << "load fail: toolbarStamp";
	}
	toolbarStampImage.createMaskFromColor(sf::Color::Black);

	toolbarStampText.loadFromImage(toolbarStampImage);

	toolbarStampSprite.setTexture(toolbarStampText);
	toolbarStampSprite.setScale(toolbarStampSprite.getScale().y / 5, toolbarStampSprite.getScale().y / 5);

	if (!stampToolImage.loadFromFile("images/stamp.bmp"))
	{
		std::cout << "load fail: toolbarStamp";
	}
	stampToolImage.createMaskFromColor(sf::Color::Black);

	isPaintDialogOpen = false;

	brushSize = 4;

	toolbarMain.setFillColor(sf::Color::Black);
	toolbarMain.setPosition(0, 0);

	toolbarColour.setFillColor(sf::Color::Black);
	toolbarColour.setOutlineColor(sf::Color::White);
	toolbarColour.setOutlineThickness(1.0f);

	toolbarRect.setFillColor(sf::Color::White);

	toolbarColour.setFillColor(sf::Color::Black);
	toolbarColour.setOutlineColor(sf::Color::White);
	toolbarColour.setOutlineThickness(1.0f);

	toolbarCirc.setFillColor(sf::Color::White);

	toolbarLine.setFillColor(sf::Color::White);

	sf::Color grey(128, 128, 128);

	toolbarSelection.setFillColor(grey);
	toolbarSelection.setPosition(0, 0);
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

		*_Colourref = tempColour; // Returning the new colour
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
	_Window->draw(cursor);
	_Window->draw(toolbarMain);
	_Window->draw(toolbarSelection);
	_Window->draw(toolbarPenSprite);
	_Window->draw(toolbarStampSprite);
	_Window->draw(toolbarRect);
	_Window->draw(toolbarCirc);
	_Window->draw(toolbarLine);
	_Window->draw(toolbarColour);
	_Window->draw(toolbarColourText);

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

sf::CircleShape* CPaintToolManager::DrawPoly(sf::Vector2i* _MousePos, sf::Color* _PenColour, sf::RenderWindow* _Window)
{
	sf::CircleShape* poly = new sf::CircleShape();
	sf::Vector2f dimensions;

	int tempSize = brushSize;
	brushSize = 5;
	sf::Event event;

	sf::Vector2i MouseInitial = *_MousePos;
	sf::Vector2f Position = sf::Vector2f(MouseInitial);

	poly->setFillColor(*_PenColour);
	poly->setOutlineColor(sf::Color::White);
	poly->setOutlineThickness(1.0f);

	while (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		_Window->pollEvent(event);
		if (event.type == sf::Event::MouseWheelMoved)
		{
			brushSize += event.mouseWheel.delta;
			if (brushSize < 3)
			{
				brushSize = 3;
			}
		}

		poly->setPointCount(brushSize);

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

		poly->setRadius(dimensions.x / 2);
		poly->setPosition(sf::Vector2f(Position));

		poly->setScale(sf::Vector2f(poly->getScale().x, abs(MouseInitial.y - _MousePos->y) / poly->getRadius() / 2));

		DrawShapes(_Window, poly, _MousePos);
	}

	poly->setOutlineThickness(0.0f);

	brushSize = tempSize;

	return poly;
}

void CPaintToolManager::DrawStamp(sf::Vector2i* _MousePos, sf::Color* _PenColour, sf::RenderWindow* _Window)
{
	for (int i = 0; i < stampToolImage.getSize().x; i++)
	{
		if (_MousePos->x + i - stampToolImage.getSize().x / 2 < _Window->getSize().x - 1 && _MousePos->x + i - stampToolImage.getSize().x / 2 > 1)
		{
			for (int j = 0; j < stampToolImage.getSize().y; j++)
			{
				sf::Color tempColour = stampToolImage.getPixel(i, j);
				if (_MousePos->y + j - stampToolImage.getSize().y / 2 < _Window->getSize().y - 1 && _MousePos->y + j - stampToolImage.getSize().y / 2 > toolbarMain.getSize().y - 1)
				{
					if (stampToolImage.getPixel(i, j).a == 0)
					{
						Canvas.setPixel(_MousePos->x - stampToolImage.getSize().x / 2 + i, _MousePos->y - stampToolImage.getSize().y / 2 + j, *_PenColour);
					}
				}
			}
		}
	}
}

sf::RectangleShape* CPaintToolManager::DrawLine(sf::Vector2i* _MousePos, sf::Color* _PenColour, sf::RenderWindow* _Window)
{
	sf::RectangleShape* line = new sf::RectangleShape();
	sf::Vector2f dimensions;

	line->setPosition(sf::Vector2f(_MousePos->x, _MousePos->y));
	line->setFillColor(*_PenColour);
	line->setOutlineColor(sf::Color::White);
	line->setOutlineThickness(1.0f);

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
	line->setOutlineThickness(0.0f);

	return line;
}