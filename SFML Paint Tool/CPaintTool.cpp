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
	MainManager = new CPaintToolManager();

	CurrentPenColour = new sf::Color(sf::Color::Black);

	drawMode = 1;

	toolChoice = 0;

	Tool = tool::Pen;

	modes = sf::VideoMode::getFullscreenModes();

	WindowXSize = 1024;
	WindowYSize = 720;

	toolbarOffset = 48;

	paintDialogOpen = false;
}

CPaintTool::~CPaintTool() {}

void CPaintTool::RunProgram()
{
	// -- Window Properties -- //

	sf::RenderWindow window(sf::VideoMode(WindowXSize, WindowYSize), "SFML Window");

	//::ShowWindow(window.getSystemHandle(), SW_MAXIMIZE);

	// -- Canvas Setup -- //

	MainManager->Canvas.create(WindowXSize, WindowYSize, sf::Color::White);

	MainManager->CanvasTexture.loadFromImage(MainManager->Canvas); // same proccess for creating sprites

	MainManager->CanvasSprite.setTexture(MainManager->CanvasTexture);
	MainManager->CanvasSprite.setOrigin(WindowXSize / 2, WindowYSize / 2);
	MainManager->CanvasSprite.setPosition(WindowXSize / 2, WindowYSize / 2);

	sf::Vector2i MousePos = sf::Mouse::getPosition(window);

	// -- Toolbar Properties -- //

	MainManager->toolbarSelection.setSize(sf::Vector2f(48, 48));

	MainManager->toolbarColour.setPosition(WindowXSize - toolbarOffset + 5, 5);
	MainManager->toolbarColour.setSize(sf::Vector2f(36, 36));
	MainManager->toolbarColour.setFillColor(*CurrentPenColour);

	MainManager->toolbarColourText.setPosition(WindowXSize - toolbarOffset * 3, 13);

	MainManager->toolbarMain.setSize(sf::Vector2f(WindowXSize, 48));

	MainManager->toolbarRect.setPosition(toolbarOffset + 6, 5);
	MainManager->toolbarRect.setSize(sf::Vector2f(36, 36));

	MainManager->toolbarCirc.setPosition((toolbarOffset * 2) + 6, 5);
	MainManager->toolbarCirc.setRadius(19);

	MainManager->toolbarLine.setSize(sf::Vector2f(48, 5));
	MainManager->toolbarLine.setPosition((toolbarOffset * 3) + 10, 5);
	MainManager->toolbarLine.setRotation(45);

	MainManager->toolbarStampSprite.setPosition((toolbarOffset * 4) + 4, 5);

	while (window.isOpen())
	{
		MainManager->toolbarColourText.setPosition(WindowXSize - toolbarOffset * 3, 13);
		MousePos = sf::Mouse::getPosition(window);
		MainManager->cursor.setPosition(sf::Vector2f(MousePos));
		MainManager->cursor.setSize(sf::Vector2f(MainManager->brushSize * 2, MainManager->brushSize * 2));
		MainManager->cursor.setOrigin(MainManager->brushSize, MainManager->brushSize);

		sf::Event event;
		while (window.pollEvent(event))
		{
			// Allows close button to close window
			if (event.type == sf::Event::Closed)
				window.close();
			else if (event.type == sf::Event::MouseWheelMoved)
			{
				if (MainManager->brushSize <= 0)
				{
					MainManager->brushSize = 2;
				}
				MainManager->brushSize += event.mouseWheel.delta * 2;
			}
		}

		if (event.type == sf::Event::Resized)
		{
			// -- Giving the window size a maximum x and y value -- //
			if (window.getSize().x > WindowXSize || window.getSize().y > WindowYSize)
			{
				window.setSize(sf::Vector2u(WindowXSize, WindowYSize));
			}

			sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
			window.setView(sf::View(visibleArea));
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			sf::Vector2i MousePos = sf::Mouse::getPosition(window);

			if (MousePos.y > 48)
			{
				switch (Tool)
				{
				case tool::Pen:
				{
					if (!(MousePos.y < 5 || MousePos.y > WindowYSize - 5 || MousePos.x < 5 || MousePos.x > WindowXSize - 5))
					{
						MainManager->DrawPen(&MousePos, CurrentPenColour);
						MainManager->CanvasTexture.loadFromImage(MainManager->Canvas);
					}
					break;
				}
				case tool::Circle:
				{
					sf::CircleShape* circ = MainManager->DrawCirc(&MousePos, CurrentPenColour, &window);
					MainManager->shapes.push_back(circ);
					break;
				}
				case tool::Rectangle:
				{
					sf::RectangleShape* rect = MainManager->DrawRect(&MousePos, CurrentPenColour, &window);
					MainManager->shapes.push_back(rect);
					break;
				}
				case tool::Line:
				{
					sf::RectangleShape* line = MainManager->DrawLine(&MousePos, CurrentPenColour, &window);
					MainManager->shapes.push_back(line);
					break;
				}
				case tool::Poly:
				{
					sf::CircleShape* poly = MainManager->DrawPoly(&MousePos, CurrentPenColour, &window);
					MainManager->shapes.push_back(poly);
					break;
				}
				case tool::Stamp:
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
			else
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

		if (MousePos.y > 48)
		{
			window.setMouseCursorVisible(false);
		}
		else
		{
			window.setMouseCursorVisible(true);
		}

		MainManager->DrawShapes(&window, &MainManager->cursor, &MousePos);
	}

	delete MainManager;
	MainManager = nullptr;
}