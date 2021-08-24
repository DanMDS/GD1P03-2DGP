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

	WindowXSize = 1280;
	WindowYSize = 720;

	toolbarOffset = 48;

	paintDialogOpen = false;

	fileName = std::string("images/Paint Tool Image.bmp");
}

CPaintTool::~CPaintTool() { /* Destructor */ }

void CPaintTool::Save(sf::RenderWindow* _Window, std::string* _Name)
{
	sf::Texture texture;
	texture.create(_Window->getSize().x, _Window->getSize().y);	// Create texture for saving

	_Window->clear(); 
	
	_Window->draw(MainManager->CanvasSprite);					// Draw canvas without toolbar

	for (int i = 0; i < int(MainManager->shapes.size()); i++)
	{
		_Window->draw(*MainManager->shapes[i]);
	}

	texture.update(*_Window);									// Update texture
	if (texture.copyToImage().saveToFile(*_Name))
	{
		std::cout << std::endl <<  "Painting saved to " << *_Name << std::endl;	// Console output saying savign was successful
	}
	else
	{
		std::cout << "Error: saving";							// Console output saying savign was unsuccessful
	}
}

void CPaintTool::Load()
{
	sf::Image loadImage;										// Create image to load from

	if (!loadImage.loadFromFile("images/Paint Tool Image.bmp"))	// Load image from saved file
	{
		std::cout << "Error: toolbarLoad";						// Console output error if loading is unsuccessful
	}

	MainManager->CanvasTexture.loadFromImage(loadImage);		// Apply loaded image to canvas
}

void CPaintTool::RunProgram()
{
	// Window Properties

	sf::RenderWindow window(sf::VideoMode(WindowXSize, WindowYSize), "SFML Window");
	window.setFramerateLimit(60);

	// Canvas Setup

	MainManager->Canvas.create(WindowXSize, WindowYSize, sf::Color::White);

	MainManager->CanvasTexture.loadFromImage(MainManager->Canvas);

	MainManager->CanvasSprite.setTexture(MainManager->CanvasTexture);
	MainManager->CanvasSprite.setOrigin(float(WindowXSize / 2), float(WindowYSize / 2));
	MainManager->CanvasSprite.setPosition(float(WindowXSize) / 2, float(WindowYSize / 2));

	sf::Vector2i MousePos = sf::Mouse::getPosition(window);

	// Toolbar Properties

	MainManager->toolbarSelection.setSize(sf::Vector2f(48, 48));

	MainManager->toolbarColour.setPosition(WindowXSize - toolbarOffset + 5, 5);
	MainManager->toolbarColour.setSize(sf::Vector2f(36, 36));
	MainManager->toolbarColour.setFillColor(*CurrentPenColour);

	MainManager->toolbarColourText.setPosition(WindowXSize - toolbarOffset * 3, 13);

	MainManager->toolbarSizeText.setPosition(WindowXSize - toolbarOffset * 6, 13);
	MainManager->toolbarSizeText.setString("Brush Size: " + MainManager->brushSizeStr);

	MainManager->toolbarMain.setSize(sf::Vector2f(float(WindowXSize), 48.0f));

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

	MainManager->toolbarUndoSprite.setPosition((toolbarOffset * 6) + 4, 5);

	MainManager->toolbarSaveSprite.setPosition((toolbarOffset * 7) + 4, 5);

	MainManager->toolbarLoadSprite.setPosition((toolbarOffset * 8) + 4, 5);

	// Main program loop
	while (window.isOpen())
	{
		MainManager->brushSizeStr = std::to_string(MainManager->brushSize / 2);
		MainManager->toolbarSizeText.setString("Brush Size: " + MainManager->brushSizeStr);					// Setting brush size text to correct number

		MainManager->toolbarColour.setFillColor(*CurrentPenColour);											// Setting colour picker button to correct colour

		MousePos = sf::Mouse::getPosition(window);															// Setting mouse and cursor position
		MainManager->cursor.setPosition(sf::Vector2f(MousePos));
		MainManager->cursor.setSize(sf::Vector2f(float(MainManager->brushSize * 2), float(MainManager->brushSize * 2)));
		MainManager->cursor.setOrigin(float(MainManager->brushSize), float(MainManager->brushSize));

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
			if (int(window.getSize().x) > WindowXSize || int(window.getSize().y) > WindowYSize)
			{
				window.setSize(sf::Vector2u(WindowXSize, WindowYSize));
			}

			sf::FloatRect visibleArea(0, 0, float(event.size.width), float(event.size.height));
			window.setView(sf::View(visibleArea));
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))													// When the left mouse button is pressed, activate the current selected tool
		{
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
				else if (MousePos.x > (toolbarOffset * 6) + 4 && MousePos.x < (toolbarOffset * 6) + 30 && MousePos.y < MainManager->toolbarMain.getSize().y / 2)
				{
					std::cout << "test";
					if (MainManager->shapes.size() > 0)
					{
						MainManager->shapes.pop_back();
					}
					while (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {}
				}
				else if (MousePos.x < toolbarOffset * 8)
				{
					Save(&window, &fileName);
				}
				else if (MousePos.x < toolbarOffset * 9)
				{
					Load();
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