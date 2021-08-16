#include "PaintToolManager.h"

CPaintToolManager* MainManager;
int WindowXSize = 1024;
int WindowYSize = 720;

int brushSize = 5;

bool bDrawingPen = false;
bool bDrawingLine = false;
bool bDrawingLineStart = false;

sf::Color* CurrentPenColour;

// Vector2i means vector2 int, Vector2f means vector2 float
void DrawPen(sf::Image* _CanvasRef, sf::Vector2i* _MousePos) // mouse needs reference to window relevant 
{
	if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) && !sf::Mouse::isButtonPressed(sf::Mouse::Right))
	{
		return;
	}

	if (bDrawingPen)
	{
		for (int i = -brushSize; i < brushSize / 2; i++)
		{
			// Square shape pen
			for (int j = -brushSize; j < brushSize / 2; j++)
			{
				_CanvasRef->setPixel(_MousePos->x + j, _MousePos->y + i, *CurrentPenColour);
			}

			/*// Star shape pen
			_CanvasRef->setPixel(_MousePos->x, _MousePos->y, *CurrentPenColour);

			_CanvasRef->setPixel(_MousePos->x + i, _MousePos->y, *CurrentPenColour);
			_CanvasRef->setPixel(_MousePos->x - i, _MousePos->y, *CurrentPenColour);

			_CanvasRef->setPixel(_MousePos->x, _MousePos->y + i, *CurrentPenColour);
			_CanvasRef->setPixel(_MousePos->x, _MousePos->y - i, *CurrentPenColour);

			_CanvasRef->setPixel(_MousePos->x + i, _MousePos->y + i, *CurrentPenColour);
			_CanvasRef->setPixel(_MousePos->x - i, _MousePos->y - i, *CurrentPenColour);
			_CanvasRef->setPixel(_MousePos->x - i, _MousePos->y + i, *CurrentPenColour);
			_CanvasRef->setPixel(_MousePos->x + i, _MousePos->y - i, *CurrentPenColour);*/
		}
	}
}

void DrawLine(sf::Vector2i* _MousePos, sf::Vertex* _Line[])
{
	sf::Vector2f mousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition());
	if (bDrawingLine)
	{
		_Line[0]->position = mousePos;
		_Line[0]->color = *CurrentPenColour;
	}
	_Line[1]->position = mousePos;
	_Line[1]->color = *CurrentPenColour;
}

int main()
{
	// -- Window Properties -- //
	sf::RenderWindow window(sf::VideoMode(WindowXSize, WindowYSize), "SFML Window");

	std::vector<sf::Vertex*> lines;

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
				while (sf::Mouse::isButtonPressed(sf::Mouse::Right))
				{
					sf::Vertex* line = MainManager->DrawLine(CurrentPenColour);
					lines.push_back(line);
				}
			}
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

	return 0;
}