#include "PaintToolManager.h"
#include <iostream>

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

	std::vector<sf::Shape*> shapes;

	MainManager = new CPaintToolManager;

	CurrentPenColour = new sf::Color(sf::Color::Black);

	// -- Canvas Setup -- //
	sf::Image Canvas; 
	Canvas.create(WindowXSize, WindowYSize, sf::Color::White);

	sf::Texture CanvasTexture;
	CanvasTexture.loadFromImage(Canvas); // same proccess for creating sprites

	sf::Sprite CanvasSprite;
	CanvasSprite.setTexture(CanvasTexture);
	CanvasSprite.setOrigin(WindowXSize/2, WindowYSize/2);
	CanvasSprite.setPosition(WindowXSize / 2, WindowYSize / 2);

	//// -- Circle Properties -- //
	sf::CircleShape shape(50.0f);
	sf::Vector2f shapePos = sf::Vector2f(400, 300);
	shape.setOrigin(shape.getRadius(), shape.getRadius()); // Set circle origin to centre of circle with getRadius()
	shape.setPosition(shapePos);
	shape.setFillColor(sf::Color::Black);

	shape.setOutlineColor(sf::Color::White);
	shape.setOutlineThickness(10.0f);

	shapes.push_back(&shape);

	sf::RectangleShape shape2(sf::Vector2f(153.0f, 50.0f));
	sf::Vector2f shapePos2 = sf::Vector2f(400, 300);
	shape2.setOrigin(10, 10); // Set circle origin to centre of circle with getRadius()
	shape2.setPosition(shapePos2);
	shape2.setFillColor(sf::Color::Black);

	shape2.setOutlineColor(sf::Color::White);
	shape2.setOutlineThickness(10.0f);

	shapes.push_back(&shape2);


	sf::RectangleShape rect(sf::Vector2f(50.0f, 60.0f));
	rect.setOrigin(10.0f, 10.0f);
	rect.setFillColor(*CurrentPenColour);
	rect.setOutlineColor(sf::Color::White);
	rect.setOutlineThickness(10.0f);

	shapes.push_back(&rect);

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
				MainManager->DrawPen(CanvasTexture, &Canvas, &MousePos, brushSize, CurrentPenColour);
				CanvasTexture.loadFromImage(Canvas);
			}
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
		{
			sf::Vector2i MousePos1 = sf::Mouse::getPosition(window);
			sf::RectangleShape* rect = MainManager->DrawRect(&MousePos1, CurrentPenColour, &window);
			shapes.push_back(rect);
		}

		if (event.type == sf::Event::MouseButtonReleased) // Calls the mouse input check
		{

		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
		{
			MainManager->OpenPaintDialog(&window, CurrentPenColour);
		}

		window.clear();
		window.draw(CanvasSprite);
		for (int i = 0; i < shapes.size(); i++)
		{
			window.draw(*shapes[i]);
		}
		window.display();
	}

	return 0;
}