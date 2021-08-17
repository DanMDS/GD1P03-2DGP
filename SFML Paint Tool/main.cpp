#include "PaintToolManager.h"

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
	//sf::CircleShape shape(50.0f);
	//sf::Vector2f shapePos = sf::Vector2f(400, 300);
	//shape.setOrigin(shape.getRadius(), shape.getRadius()); // Set circle origin to centre of circle with getRadius()
	//shape.setPosition(shapePos);
	//shape.setFillColor(sf::Color::Black);

	//shape.setOutlineColor(sf::Color::White);
	//shape.setOutlineThickness(10.0f);

	//shapes.push_back(&shape);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			// Allows close button to close window
			if (event.type == sf::Event::Closed)
			window.close(); 
		}

		if (event.type == sf::Event::MouseButtonPressed) // Calls the mouse input check
		{
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				while (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					sf::Vector2i MousePos = sf::Mouse::getPosition(window);

					MainManager->DrawPen(CanvasTexture, &Canvas, &MousePos, brushSize, CurrentPenColour);
					CanvasTexture.loadFromImage(Canvas);
					window.draw(CanvasSprite);
					window.display();
				}
			}
			if (event.mouseButton.button == sf::Mouse::Right)
			{
				sf::Vector2i MousePos = sf::Mouse::getPosition(window);

				sf::RectangleShape rect = MainManager->DrawLine(&MousePos, brushSize, CurrentPenColour);

				shapes.push_back(&rect);
				window.draw(rect);
				window.draw(CanvasSprite);
			}
			CanvasTexture.loadFromImage(Canvas);
			window.draw(CanvasSprite);
			window.display();
		}
		
		if (event.type == sf::Event::MouseButtonReleased) // Calls the mouse input check
		{
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				bDrawingPen = false;
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
		{
			MainManager->OpenPaintDialog(&window, CurrentPenColour);
		}

		window.clear();

		window.draw(CanvasSprite);

		/*for (int i = 0; i < shapes.size(); i++)
		{
			window.draw(*shapes[i]);
		}*/

		window.display();
	}

	shapes.clear();

	return 0;
}