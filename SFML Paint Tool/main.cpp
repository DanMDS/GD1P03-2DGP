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
#include "resource1.h"

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

HINSTANCE inst;

CPaintToolManager* MainManager;
int WindowXSize = 1024;
int WindowYSize = 720;

bool paintDialogOpen = false;

sf::Color* CurrentPenColour;

int main()
{
	// -- Window Properties -- //

	sf::RenderWindow window(sf::VideoMode(WindowXSize, WindowYSize), "SFML Window");

	window.setMouseCursorVisible(false);

	SetMenu(window.getSystemHandle(), LoadMenu(inst, MAKEINTRESOURCE(IDR_MENU1)));

	MainManager = new CPaintToolManager;

	CurrentPenColour = new sf::Color(sf::Color::Black);

	// -- Canvas Setup -- //
	MainManager->Canvas.create(WindowXSize, WindowYSize, sf::Color::White);

	MainManager->CanvasTexture.loadFromImage(MainManager->Canvas); // same proccess for creating sprites

	MainManager->CanvasSprite.setTexture(MainManager->CanvasTexture);
	MainManager->CanvasSprite.setOrigin(WindowXSize/2, WindowYSize/2);
	MainManager->CanvasSprite.setPosition(WindowXSize / 2, WindowYSize / 2);

	sf::Vector2i MousePos = sf::Mouse::getPosition(window);

	//// -- Circle Properties -- //


	while (window.isOpen())
	{
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

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			toolChoice = 0;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			toolChoice = 1;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			toolChoice = 2;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::F))
		{
			toolChoice = 3;
		}
		switch (toolChoice)
		{
		case 0:
			{
				Tool = tool::Pen;
				break;
			}
		case 1:
			{
				Tool = tool::Circle;
				break;
			}
		case 2:
			{
				Tool = tool::Rectangle;
				break;
			}
		case 3:
			{
				Tool = tool::Line;
				break;
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
			switch (Tool)
			{
			case tool::Pen:
				{
					if (!(MousePos.y < 10 || MousePos.y > WindowYSize - 10))
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

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
		{
			window.setMouseCursorVisible(true);
			MainManager->OpenPaintDialog(&window, CurrentPenColour);
		}

		window.setMouseCursorVisible(false);

		window.clear();
		window.draw(MainManager->CanvasSprite);
		for (int i = 0; i < MainManager->shapes.size(); i++)
		{
			window.draw(*MainManager->shapes[i]);
		}
		window.display();
	}

	return 0;
}