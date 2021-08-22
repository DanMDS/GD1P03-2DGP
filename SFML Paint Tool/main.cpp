#pragma once
#include "PaintToolManager.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <Windows.h>
#include <wingdi.h>

#include <CommCtrl.h>
#include <sstream>
#include <string>

#include <commdlg.h>

int drawMode = 1;

int toolChoice = 0;
enum class tool
{
	Pen,
	Circle,
	Rectangle,
	Line,
	Last
};

tool Tool = tool::Pen;

CPaintToolManager* MainManager;
int WindowXSize = 1024;
int WindowYSize = 720;

float toolbarOffset = WindowYSize / 15;

bool paintDialogOpen = false;

sf::Color* CurrentPenColour;

int main()
{
	// -- Window Properties -- //

	sf::RenderWindow window(sf::VideoMode(WindowXSize, WindowYSize), "SFML Window");

	MainManager = new CPaintToolManager;

	CurrentPenColour = new sf::Color(sf::Color::Black);

	// -- Canvas Setup -- //

	MainManager->Canvas.create(WindowXSize, WindowYSize, sf::Color::White);

	MainManager->CanvasTexture.loadFromImage(MainManager->Canvas); // same proccess for creating sprites

	MainManager->CanvasSprite.setTexture(MainManager->CanvasTexture);
	MainManager->CanvasSprite.setOrigin(WindowXSize/2, WindowYSize/2);
	MainManager->CanvasSprite.setPosition(WindowXSize / 2, WindowYSize / 2);

	sf::Vector2i MousePos = sf::Mouse::getPosition(window);

	// -- Toolbar Properties -- //

	MainManager->toolbarSelection.setSize(sf::Vector2f(WindowYSize / 15, WindowYSize / 15));

	MainManager->toolbarColour.setPosition(WindowXSize - toolbarOffset + 5, 5);
	MainManager->toolbarColour.setSize(sf::Vector2f(WindowYSize / 20, WindowYSize / 20));
	MainManager->toolbarColour.setFillColor(*CurrentPenColour);

	MainManager->toolbarColourText.setPosition(WindowXSize - toolbarOffset * 3, 13);

	MainManager->toolbarMain.setSize(sf::Vector2f(WindowXSize, WindowYSize / 15));

	MainManager->toolbarRect.setPosition(toolbarOffset + 5, 5);
	MainManager->toolbarRect.setSize(sf::Vector2f(WindowYSize / 20, WindowYSize / 20));

	MainManager->toolbarCirc.setPosition((toolbarOffset * 2) + 5, 5);
	MainManager->toolbarCirc.setRadius(WindowYSize / 40);

	MainManager->toolbarLine.setSize(sf::Vector2f(WindowYSize / 15, 5));
	MainManager->toolbarLine.setPosition((toolbarOffset * 3) + 10, 5);
	MainManager->toolbarLine.setRotation(45);

	while (window.isOpen())
	{
		MainManager->toolbarColour.setFillColor(*CurrentPenColour);
		MousePos = sf::Mouse::getPosition(window);
		MainManager->cursor.setPosition(sf::Vector2f(MousePos));
		MainManager->cursor.setRadius(MainManager->brushSize);
		MainManager->cursor.setOrigin(MainManager->cursor.getRadius(), MainManager->cursor.getRadius());

		sf::Event event;
		while (window.pollEvent(event))
		{
			// Allows close button to close window
			if (event.type == sf::Event::Closed)
			window.close(); 
			else if (event.type == sf::Event::MouseWheelMoved)
			{
				int wheel = event.mouseWheel.delta;
				MainManager->brushSize += event.mouseWheel.delta * 2;
			}
		}
		
		if (event.type == (sf::Event::KeyPressed))
		{
			std::cout << "test";
			if (event.key.code == sf::Keyboard::Q)
			{
				std::cout << "test";
				MainManager->brushSize += 1;
			}
		}
		
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			sf::Vector2i MousePos = sf::Mouse::getPosition(window);

			if (MousePos.y > WindowYSize / 15)
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
				else if (MousePos.x > WindowXSize - toolbarOffset)
				{
					window.setMouseCursorVisible(true);
					MainManager->OpenPaintDialog(&window, CurrentPenColour);
				}
			}
		}

		if (MousePos.y > WindowYSize / 15)
		{
			window.setMouseCursorVisible(false);
		}
		else
		{
			window.setMouseCursorVisible(true);
		}

		MainManager->DrawShapes(&window, &MainManager->cursor, &MousePos);
	}

	return 0;
}