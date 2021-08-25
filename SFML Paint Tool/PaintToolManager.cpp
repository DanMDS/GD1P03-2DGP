/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2021 Media Design School
File Name : PaintToolManager.cpp
Description : Function declaration for PaintToolManager.h
Author : Daniel Bolleboom
Mail : daniel.bolleboom@mds.ac.nz
**************************************************************************/
#include "PaintToolManager.h"
#include <math.h>
#include <iostream>
#include <cstdlib>
#include <string>

CPaintToolManager::CPaintToolManager()
{
	// Initialising variables
	// 
	// Initialising colour picker
	hwnd = NULL;

	ZeroMemory(&cc, sizeof(cc));
	cc.lStructSize = sizeof(cc);
	cc.hwndOwner = hwnd;

	cc.lpCustColors = (LPDWORD)acrCustClr;
	cc.rgbResult = rgbCurrent;
	cc.Flags = CC_FULLOPEN | CC_RGBINIT;

	//Initialising cursor
	cursor.setSize(sf::Vector2f(5.0f, 5.0f));
	sf::Vector2i cursorPos;
	cursor.setOrigin(cursor.getSize().x / 2, cursor.getSize().y / 2); 
	cursor.setPosition(sf::Vector2f(cursorPos));
	cursor.setFillColor(sf::Color::Black);
	cursor.setOutlineColor(sf::Color::White);
	cursor.setOutlineThickness(2.0f);


	// Initialising toolbar and icons
	//
	// Toolbar: Text for colour picker and brush size
	if (!font.loadFromFile("ARIAL.TTF"))
	{
		std::cout << "load fail: Font";
	}

	brushSizeStr = std::to_string(brushSize);

	toolbarColourText.setFont(font);
	toolbarColourText.setString("Colour Picker: ");
	toolbarColourText.setCharacterSize(15);
	toolbarColourText.setFillColor(sf::Color::White);

	toolbarSizeText.setFont(font);
	toolbarSizeText.setString("Brush Size: " + brushSizeStr);
	toolbarSizeText.setCharacterSize(15);
	toolbarSizeText.setFillColor(sf::Color::White);

	// Toolbar: brush
	if (!toolbarPenImage.loadFromFile("images/brush.bmp"))
	{
		std::cout << "load fail: Brush";
	}
	toolbarPenImage.createMaskFromColor(sf::Color::Black);

	toolbarPenText.loadFromImage(toolbarPenImage);

	toolbarPenSprite.setTexture(toolbarPenText);
	toolbarPenSprite.setScale(toolbarPenSprite.getScale().y / 5, toolbarPenSprite.getScale().y / 5);
	toolbarPenSprite.setPosition(4, 5);

	// Toolbar: stamp
	if (!toolbarStampImage.loadFromFile("images/toolbarStamp.bmp"))
	{
		std::cout << "load fail: toolbarStamp";
	}
	toolbarStampImage.createMaskFromColor(sf::Color::Black);

	toolbarStampText.loadFromImage(toolbarStampImage);

	toolbarStampSprite.setTexture(toolbarStampText);
	toolbarStampSprite.setScale(toolbarStampSprite.getScale().y / 5, toolbarStampSprite.getScale().y / 5);

	// Stamp tool image
	if (!stampToolImage.loadFromFile("images/stamp.bmp"))
	{
		std::cout << "load fail: toolbarStamp";
	}
	stampToolImage.createMaskFromColor(sf::Color::Black);

	// Undo image
	if (!toolbarUndoImage.loadFromFile("images/undo.bmp"))
	{
		std::cout << "load fail: toolbarUndo";
	}
	toolbarUndoImage.createMaskFromColor(sf::Color::Black);

	toolbarUndoText.loadFromImage(toolbarUndoImage);
	toolbarUndoSprite.setTexture(toolbarUndoText);
	toolbarUndoSprite.setScale(toolbarUndoSprite.getScale().y / 4, toolbarUndoSprite.getScale().y / 4);

	// Save image
	if (!toolbarSaveImage.loadFromFile("images/save.bmp"))
	{
		std::cout << "load fail: toolbarSave";
	}
	toolbarSaveImage.createMaskFromColor(sf::Color::Black);

	toolbarSaveText.loadFromImage(toolbarSaveImage);
	toolbarSaveSprite.setTexture(toolbarSaveText);
	toolbarSaveSprite.setScale(toolbarSaveSprite.getScale().y / 5, toolbarSaveSprite.getScale().y / 5);

	if (!toolbarLoadImage.loadFromFile("images/load.bmp"))
	{
		std::cout << "load fail: toolbarload";
	}
	toolbarLoadImage.createMaskFromColor(sf::Color::Black);

	toolbarLoadText.loadFromImage(toolbarLoadImage);
	toolbarLoadSprite.setTexture(toolbarLoadText);
	toolbarLoadSprite.setScale(toolbarLoadSprite.getScale().y / 5, toolbarLoadSprite.getScale().y / 5);

	// Toolbar: Main bar
	toolbarMain.setFillColor(sf::Color::Black);
	toolbarMain.setPosition(0, 0);

	// Toolbar: colour picker
	toolbarColour.setFillColor(sf::Color::Black);
	toolbarColour.setOutlineColor(sf::Color::White);
	toolbarColour.setOutlineThickness(1.0f);

	toolbarRect.setFillColor(sf::Color::White);

	toolbarColour.setFillColor(sf::Color::Black);
	toolbarColour.setOutlineColor(sf::Color::White);
	toolbarColour.setOutlineThickness(1.0f);
	
	// Toolbar: circle
	toolbarCirc.setFillColor(sf::Color::White);

	// Toolbar: line
	toolbarLine.setFillColor(sf::Color::White);

	// Toolbar: polygon
	toolbarPoly.setFillColor(sf::Color::White);
	toolbarPoly.setPointCount(5);

	// Toolbar: selected tool
	sf::Color grey(128, 128, 128);

	toolbarSelection.setFillColor(grey);
	toolbarSelection.setPosition(0, 0);

	// Other variables
	isPaintDialogOpen = false;

	brushSize = 10;

	polySides = 3;
}

CPaintToolManager::~CPaintToolManager()
{
	// Destructor
}

sf::Color* CPaintToolManager::OpenPaintDialog(sf::Window* _windowRef, sf::Color* _Colourref)
{
	// Code for opening the colour picker
	hwnd = _windowRef->getSystemHandle();
	cc.hwndOwner = hwnd;

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
	return NULL;
}

void CPaintToolManager::DrawPen(sf::Vector2i* _MousePos, sf::Color* _PenColour)
{
	for (int i = -brushSize; i < brushSize; i++)
	{
		for (int j = -brushSize; j < brushSize; j++)
		{
			Canvas.setPixel(_MousePos->x + j, _MousePos->y + i, *_PenColour); // Draw pixels around mouse pointer in the shape of a square
		}
	}
}

void CPaintToolManager::DrawShapes(sf::RenderWindow* _Window, sf::Shape* _Shape, sf::Vector2i* _MousePos)
{
	// Function to draw all shapes to screen

	_Window->clear();	// Clear current window so that shapes can be moved while drawing without leaving trails

	_Window->draw(CanvasSprite);

	for (int i = 0; i < int(shapes.size()); i++)	// Draw drawn shapes from the shapes vector
	{
		_Window->draw(*shapes[i]);
	}

	_Window->draw(*_Shape);
	cursor.setPosition(sf::Vector2f(*_MousePos));

	// Shapes are ordered this way so that the toolbar shows over the drawn shapes and canvas
	_Window->draw(cursor);
	_Window->draw(toolbarMain);
	_Window->draw(toolbarSelection);
	_Window->draw(toolbarPenSprite);
	_Window->draw(toolbarStampSprite);
	_Window->draw(toolbarUndoSprite);
	_Window->draw(toolbarSaveSprite);
	_Window->draw(toolbarLoadSprite);
	_Window->draw(toolbarRect);
	_Window->draw(toolbarCirc);
	_Window->draw(toolbarLine);
	_Window->draw(toolbarPoly);
	_Window->draw(toolbarColour);
	_Window->draw(toolbarColourText);
	_Window->draw(toolbarSizeText);

	cursor.setPosition(sf::Vector2f(*_MousePos));

	_Window->display();
}

sf::RectangleShape* CPaintToolManager::DrawRect(sf::Vector2i* _MousePos, sf::Color* _PenColour, sf::RenderWindow* _Window)
{
	// Function to draw custom rectangle

	sf::RectangleShape* rect = new sf::RectangleShape();	// Create rectangle
	sf::Vector2f dimensions;

	sf::Vector2i MouseInitial = *_MousePos;					// Set initial mouse position for calculations
	sf::Vector2f Position = sf::Vector2f(MouseInitial);

	rect->setFillColor(*_PenColour);						// Setting colour of rectangle so it can be seen while drawing as the correct colour
	rect->setOutlineColor(sf::Color::White);
	rect->setOutlineThickness(1.0f);

	while (sf::Mouse::isButtonPressed(sf::Mouse::Left))		// Main loop for drawing the rectangle
	{
		*_MousePos = sf::Mouse::getPosition(*_Window);						// Setting current mouse position

		dimensions.x = abs(float(MouseInitial.x) - float(_MousePos->x));					// Setting dimensions to be drawn, made positive to avoid errors
		dimensions.y = abs(float(MouseInitial.y) - float(_MousePos->y));

		if (MouseInitial.y < _MousePos->y)									// If statement to change position depending on where from the mouse the rectangle is drawn
		{
			if (MouseInitial.x < _MousePos->x)
			{
				Position = sf::Vector2f(MouseInitial);
			}
			else
			{
				Position = sf::Vector2f(float(_MousePos->x), float(MouseInitial.y));
			}
		}
		else
		{
			if (MouseInitial.x < _MousePos->x)
			{
				Position = sf::Vector2f(float(MouseInitial.x), float(_MousePos->y));
			}
			else
			{
				Position = sf::Vector2f(float(_MousePos->x), float(_MousePos->y));
			}
		}

		rect->setPosition(sf::Vector2f(Position));							// Setting size and position of rectangle to draw to screen
		rect->setSize(sf::Vector2f(dimensions));

		DrawShapes(_Window, rect, _MousePos);
	}

	rect->setOutlineThickness(0.0f);										// Removing outline and returning shape
	return rect;
}

sf::CircleShape* CPaintToolManager::DrawCirc(sf::Vector2i* _MousePos, sf::Color* _PenColour, sf::RenderWindow* _Window)
{
	sf::CircleShape* circ = new sf::CircleShape();						// Create circle
	sf::Vector2f dimensions;

	sf::Vector2i MouseInitial = *_MousePos;								// Set initial mouse position for calculations
	sf::Vector2f Position = sf::Vector2f(MouseInitial);

	circ->setFillColor(*_PenColour);									// Setting colour of circle so it can be seen while drawing as the correct colour
	circ->setOutlineColor(sf::Color::White);
	circ->setOutlineThickness(1.0f);

	while (sf::Mouse::isButtonPressed(sf::Mouse::Left))					// Main loop for drawing the circle
	{
		*_MousePos = sf::Mouse::getPosition(*_Window);					// Setting current mouse position

		dimensions.x = abs(float(MouseInitial.x) - float(_MousePos->x));				// Setting dimensions to be drawn, made positive to avoid errors
		dimensions.y = abs(float(MouseInitial.y) - float(_MousePos->y));

		if (MouseInitial.y < _MousePos->y)								// If statement to change position depending on where from the mouse the circle is drawn
		{
			if (MouseInitial.x < _MousePos->x)
			{
				Position = sf::Vector2f(MouseInitial);
			}
			else
			{
				Position = sf::Vector2f(float(_MousePos->x), float(MouseInitial.y));
			}
		}
		else
		{
			if (MouseInitial.x < _MousePos->x)
			{
				Position = sf::Vector2f(float(MouseInitial.x), float(_MousePos->y));
			}
			else
			{
				Position = sf::Vector2f(float(_MousePos->x), float(_MousePos->y));
			}
		}

		circ->setRadius(dimensions.x / 2);								// Setting size and position of circle to draw to screen
		circ->setPosition(sf::Vector2f(Position));

		circ->setScale(sf::Vector2f(circ->getScale().x, abs(MouseInitial.y - _MousePos->y) / circ->getRadius() / 2));

		DrawShapes(_Window, circ, _MousePos);
	}

	circ->setOutlineThickness(0.0f);									// Removing outline and returning shape
	return circ;
}

sf::CircleShape* CPaintToolManager::DrawPoly(sf::Vector2i* _MousePos, sf::Color* _PenColour, sf::RenderWindow* _Window)
{
	sf::CircleShape* poly = new sf::CircleShape();						// Create polygon
	sf::Vector2f dimensions;	
	sf::Event event;

	sf::Vector2i MouseInitial = *_MousePos;								// Set initial mouse position for calculations
	sf::Vector2f Position = sf::Vector2f(MouseInitial);

	poly->setFillColor(*_PenColour);									// Setting colour of polygon so it can be seen while drawing as the correct colour
	poly->setOutlineColor(sf::Color::White);
	poly->setOutlineThickness(1.0f);

	while (sf::Mouse::isButtonPressed(sf::Mouse::Left))					// Main loop for drawing the polygon
	{
		_Window->pollEvent(event);										// Event check for changing the amount of sides the polygon has when using the scroll wheel
		if (event.type == sf::Event::MouseWheelMoved)
		{
			polySides += event.mouseWheel.delta;
		}
		if (polySides < 3)
		{
			polySides = 3;
		}

		poly->setPointCount(polySides);

		*_MousePos = sf::Mouse::getPosition(*_Window);					// Setting current mouse position

		dimensions.x = abs(float(MouseInitial.x) - float(_MousePos->x));				// Setting dimensions to be drawn, made positive to avoid errors
		dimensions.y = abs(float(MouseInitial.y) - float(_MousePos->y));

		if (MouseInitial.y < _MousePos->y)
		{
			if (MouseInitial.x < _MousePos->x)
			{
				Position = sf::Vector2f(MouseInitial);
			}
			else
			{
				Position = sf::Vector2f(float(_MousePos->x), float(MouseInitial.y));
			}
		}
		else
		{
			if (MouseInitial.x < _MousePos->x)
			{
				Position = sf::Vector2f(float(MouseInitial.x), float(_MousePos->y));
			}
			else
			{
				Position = sf::Vector2f(float(_MousePos->x), float(_MousePos->y));
			}
		}

		poly->setRadius(dimensions.x / 2);								// Setting size and position of polygon to draw to screen
		poly->setPosition(sf::Vector2f(Position));

		poly->setScale(sf::Vector2f(poly->getScale().x, abs(MouseInitial.y - _MousePos->y) / poly->getRadius() / 2));

		DrawShapes(_Window, poly, _MousePos);
	}

	poly->setOutlineThickness(0.0f);									// Removing outline and returning shape

	return poly;
}

void CPaintToolManager::DrawStamp(sf::Vector2i* _MousePos, sf::Color* _PenColour, sf::RenderWindow* _Window)
{
	// If statements are for checking if the pixel being drawn if it is out of bounds, doesn't draw it if this is true
	for (int i = 0; i < int(stampToolImage.getSize().x); i++)
	{
		if (_MousePos->x + i - stampToolImage.getSize().x / 2 < _Window->getSize().x && _MousePos->x + i - stampToolImage.getSize().x / 2 > 0)
		{
			for (int j = 0; j < int(stampToolImage.getSize().y); j++)
			{
				sf::Color tempColour = stampToolImage.getPixel(i, j);
				if (_MousePos->y + j - stampToolImage.getSize().y / 2 < _Window->getSize().y && _MousePos->y + j - stampToolImage.getSize().y / 2 > toolbarMain.getSize().y)
				{
					if (stampToolImage.getPixel(i, j).a == 0)
					{
						Canvas.setPixel(_MousePos->x - stampToolImage.getSize().x / 2 + i, _MousePos->y - stampToolImage.getSize().y / 2 + j, *_PenColour);	// Draws pixle if it both matches the stamp and is in bounds
					}
				}
			}
		}
	}
}

sf::RectangleShape* CPaintToolManager::DrawLine(sf::Vector2i* _MousePos, sf::Color* _PenColour, sf::RenderWindow* _Window)
{
	sf::RectangleShape* line = new sf::RectangleShape();					// Create line
	sf::Vector2f dimensions;

	line->setPosition(sf::Vector2f(float(_MousePos->x), float(_MousePos->y)));			// Set position and colour
	line->setFillColor(*_PenColour);
	line->setOutlineColor(sf::Color::White);
	line->setOutlineThickness(1.0f);

	float sideOpp;															// Setting pythagoras variables and pi for calculations
	float sideAdj;
	float sideHyp;
	float angle;
	float pi = 3.141592654f;

	while (sf::Mouse::isButtonPressed(sf::Mouse::Left))						// Main loop for drawing line
	{
		*_MousePos = sf::Mouse::getPosition(*_Window);						// Setting current mouse position

		sf::Vector2f linePosition = sf::Vector2f(line->getPosition().x, line->getPosition().y + brushSize / 2);	// Changing position to match with rotation

		sideOpp = _MousePos->y - linePosition.y;							// Setting pythagoras variables
		sideAdj = _MousePos->x - linePosition.x;
		sideHyp = sqrt((sideOpp * sideOpp) + (sideAdj * sideAdj));

		dimensions = sf::Vector2f(sideHyp, float(brushSize));						// Changing line dimensions

		angle = atan2(sideOpp, sideAdj) * (180 / pi);						// Setting rotation angle

		line->setRotation(angle);											// Setting rotation and size
		line->setSize(dimensions);

		DrawShapes(_Window, line, _MousePos);
	}
	line->setOutlineThickness(0.0f);										// Removing outline and returning shape

	return line;
}