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

HINSTANCE inst;

CPaintToolManager* MainManager;
int WindowXSize = 1024;
int WindowYSize = 720;

int brushSize = 5;

bool bDrawingPen = false;
bool bDrawingLine = false;
bool bDrawingLineStart = false;

sf::Color* CurrentPenColour;

int main()
{
	// -- Window Properties -- //

	sf::RenderWindow window(sf::VideoMode(WindowXSize, WindowYSize), "SFML Window");

	SetMenu(window.getSystemHandle(), LoadMenu(inst, MAKEINTRESOURCE(IDR_MENU1)));

	MainManager = new CPaintToolManager;

	CurrentPenColour = new sf::Color(sf::Color::Black);

	// -- Canvas Setup -- //
	MainManager->Canvas.create(WindowXSize, WindowYSize, sf::Color::White);

	MainManager->CanvasTexture.loadFromImage(MainManager->Canvas); // same proccess for creating sprites

	MainManager->CanvasSprite.setTexture(MainManager->CanvasTexture);
	MainManager->CanvasSprite.setOrigin(WindowXSize/2, WindowYSize/2);
	MainManager->CanvasSprite.setPosition(WindowXSize / 2, WindowYSize / 2);

	//// -- Circle Properties -- //
	sf::CircleShape shape(50.0f);
	sf::Vector2f shapePos = sf::Vector2f(400, 300);
	shape.setOrigin(shape.getRadius(), shape.getRadius()); // Set circle origin to centre of circle with getRadius()
	shape.setPosition(shapePos);
	shape.setFillColor(sf::Color::Black);

	shape.setOutlineColor(sf::Color::White);
	shape.setOutlineThickness(10.0f);

	MainManager->shapes.push_back(&shape);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			// Allows close button to close window
			if (event.type == sf::Event::Closed)
			window.close(); 
		}
		
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			sf::Vector2i MousePos = sf::Mouse::getPosition(window);
			if (!(MousePos.y < 10 || MousePos.y > WindowYSize - 10))
			{
				MainManager->DrawPen(&MousePos, brushSize, CurrentPenColour);
				MainManager->CanvasTexture.loadFromImage(MainManager->Canvas);
			}
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
		{
			sf::Vector2i MousePos1 = sf::Mouse::getPosition(window);
			sf::CircleShape* rect = MainManager->DrawCirc(&MousePos1, CurrentPenColour, &window);
			MainManager->shapes.push_back(rect);
		}

		if (event.type == sf::Event::MouseButtonReleased) // Calls the mouse input check
		{

		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
		{
			MainManager->OpenPaintDialog(&window, CurrentPenColour);
		}

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