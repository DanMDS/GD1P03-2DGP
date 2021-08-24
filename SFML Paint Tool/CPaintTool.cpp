#pragma once
#include "CPaintTool.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <Windows.h>
#include <wingdi.h>

#include <CommCtrl.h>
#include <sstream>
#include <string>

#include <commdlg.h>

CPaintTool::CPaintTool()
{
	// Initialising variables
	MainManager = new CPaintToolManager();

	CurrentPenColour = new sf::Color(sf::Color::Black);

	toolChoice = 0;

	Tool = tool::Pen;

	WindowXSize = 1024;
	WindowYSize = 720;

	toolbarOffset = 48;

	paintDialogOpen = false;
}

CPaintTool::~CPaintTool() { /* Destructor */ }

void CPaintTool::RunProgram()
{
	// Window Properties

	sf::RenderWindow window(sf::VideoMode(WindowXSize, WindowYSize), "SFML Window");

	// Canvas Setup

	MainManager->Canvas.create(WindowXSize, WindowYSize, sf::Color::White);

	MainManager->CanvasTexture.loadFromImage(MainManager->Canvas); // same proccess for creating sprites

	MainManager->CanvasSprite.setTexture(MainManager->CanvasTexture);
	MainManager->CanvasSprite.setOrigin(WindowXSize / 2, WindowYSize / 2);
	MainManager->CanvasSprite.setPosition(WindowXSize / 2, WindowYSize / 2);

	sf::Vector2i MousePos = sf::Mouse::getPosition(window);

	// Toolbar Properties

	MainManager->toolbarSelection.setSize(sf::Vector2f(48, 48));

	MainManager->toolbarColour.setPosition(WindowXSize - toolbarOffset + 5, 5);
	MainManager->toolbarColour.setSize(sf::Vector2f(36, 36));
	MainManager->toolbarColour.setFillColor(*CurrentPenColour);

	MainManager->toolbarColourText.setPosition(WindowXSize - toolbarOffset * 3, 13);

	MainManager->toolbarSizeText.setPosition(WindowXSize - toolbarOffset * 6, 13);
	MainManager->toolbarSizeText.setString("Brush Size: " + MainManager->brushSizeStr);

	MainManager->toolbarMain.setSize(sf::Vector2f(WindowXSize, 48));

	MainManager->toolbarRect.setPosition(toolbarOffset + 6, 5);
	MainManager->toolbarRect.setSize(sf::Vector2f(36, 36));

	MainManager->toolbarCirc.setPosition((toolbarOffset * 2) + 5, 5);
	MainManager->toolbarCirc.setRadius(19);

	MainManager->toolbarLine.setSize(sf::Vector2f(48, 5));
	MainManager->toolbarLine.setPosition((toolbarOffset * 3) + 10, 5);
	MainManager->toolbarLine.setRotation(45);

	MainManager->toolbarPoly.setPosition((toolbarOffset * 4) + 5, 5);
	MainManager->toolbarPoly.setRadius(19);

	MainManager->toolbarStampSprite.setPosition((toolbarOffset * 5) + 4, 5);

	// Main program loop
	while (window.isOpen())
	{
		MainManager->brushSizeStr = std::to_string(MainManager->brushSize / 2);
		MainManager->toolbarSizeText.setString("Brush Size: " + MainManager->brushSizeStr);					// Setting brush size text to correct number

		MousePos = sf::Mouse::getPosition(window);															// Setting mouse and cursor position
		MainManager->cursor.setPosition(sf::Vector2f(MousePos));
		MainManager->cursor.setSize(sf::Vector2f(MainManager->brushSize * 2, MainManager->brushSize * 2));
		MainManager->cursor.setOrigin(MainManager->brushSize, MainManager->brushSize);

		sf::Event event;																					// Creating window event and polling it
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)															// Closes window when the X is clicked
				window.close();
			else if (event.type == sf::Event::MouseWheelMoved)												// Changes brush size with mouse wheel
			{
				MainManager->brushSize += event.mouseWheel.delta * 2;
			}
		}
		if (MainManager->brushSize < 2)
		{
			MainManager->brushSize = 2;
		}
		if (MainManager->brushSize > 50)
		{
			MainManager->brushSize = 50;
		}

		if (event.type == sf::Event::Resized)																// Resets window scale if it gets resized too big
		{
			// -- Giving the window size a maximum x and y value -- //
			if (window.getSize().x > WindowXSize || window.getSize().y > WindowYSize)
			{
				window.setSize(sf::Vector2u(WindowXSize, WindowYSize));
			}

			sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
			window.setView(sf::View(visibleArea));
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))													// When the left mouse button is pressed, activate the current selected tool
		{
			sf::Vector2i MousePos = sf::Mouse::getPosition(window);

			if (MousePos.y > 48)
			{
				switch (Tool)
				{
				case tool::Pen:																				// Activate pen tool if drawing isn't out of bounds
				{
					if (!(MousePos.y < MainManager->brushSize|| MousePos.y > WindowYSize - MainManager->brushSize || MousePos.x < MainManager->brushSize || MousePos.x > WindowXSize - MainManager->brushSize))
					{
						MainManager->DrawPen(&MousePos, CurrentPenColour);
						MainManager->CanvasTexture.loadFromImage(MainManager->Canvas);
					}
					break;
				}
				case tool::Circle:																			// Activate circle tool
				{
					sf::CircleShape* circ = MainManager->DrawCirc(&MousePos, CurrentPenColour, &window);
					MainManager->shapes.push_back(circ);
					break;
				}
				case tool::Rectangle:																		// Activate rectangle tool
				{
					sf::RectangleShape* rect = MainManager->DrawRect(&MousePos, CurrentPenColour, &window);
					MainManager->shapes.push_back(rect);
					break;
				}
				case tool::Line:																			// Activate line tool
				{
					sf::RectangleShape* line = MainManager->DrawLine(&MousePos, CurrentPenColour, &window);
					MainManager->shapes.push_back(line);
					break;
				}
				case tool::Poly:																			// Activate polygon tool
				{
					sf::CircleShape* poly = MainManager->DrawPoly(&MousePos, CurrentPenColour, &window);
					MainManager->shapes.push_back(poly);
					break;
				}
				case tool::Stamp:																			// Activate stamp tool
				{
					if (!(MousePos.y < 5 || MousePos.y > WindowYSize - 5 || MousePos.x < 5 || MousePos.x > WindowXSize - 5))
					{
						MainManager->DrawStamp(&MousePos, CurrentPenColour, &window);
						MainManager->CanvasTexture.loadFromImage(MainManager->Canvas);
					}
					break;
				}
				}
			}
			else																							// Else statement for setting tool depending on mouse click position in tool bar
			{
				if (MousePos.x < toolbarOffset)
				{
					Tool = tool::Pen;
					MainManager->toolbarSelection.setPosition(0, 0);
				}
				else if (MousePos.x < toolbarOffset * 2)
				{
					Tool = tool::Rectangle;
					MainManager->toolbarSelection.setPosition(toolbarOffset, 0);
				}
				else if (MousePos.x < toolbarOffset * 3)
				{
					Tool = tool::Circle;
					MainManager->toolbarSelection.setPosition(toolbarOffset * 2, 0);
				}
				else if (MousePos.x < toolbarOffset * 4)
				{
					Tool = tool::Line;
					MainManager->toolbarSelection.setPosition(toolbarOffset * 3, 0);
				}
				else if (MousePos.x < toolbarOffset * 5)
				{
					Tool = tool::Poly;
					MainManager->toolbarSelection.setPosition(toolbarOffset * 4, 0);
				}
				else if (MousePos.x < toolbarOffset * 6)
				{
					Tool = tool::Stamp;
					MainManager->toolbarSelection.setPosition(toolbarOffset * 5, 0);
				}
				else if (MousePos.x > WindowXSize - toolbarOffset && MousePos.y > 0)
				{
					window.setMouseCursorVisible(true);
					MainManager->OpenPaintDialog(&window, CurrentPenColour);
				}
			}
		}

		if (MousePos.y > 48)																				// Hide original mouse cursor unless hovering over toolbar
		{
			window.setMouseCursorVisible(false);
		}
		else
		{
			window.setMouseCursorVisible(true);
		}

		MainManager->DrawShapes(&window, &MainManager->cursor, &MousePos);									// Draw shapes
	}

	delete MainManager;																						// Deallocate memory
	MainManager = nullptr;
}