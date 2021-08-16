#include "PaintToolManager.h"

CPaintToolManager* MainManager;
int WindowXSize = 1024;
int WindowYSize = 720;

int brushSize = 5;

bool bDrawing = false;

sf::Color* CurrentPenColour;


void InputChecking(sf::RectangleShape* _rect, sf::Vector2f* _vect) // player controller function
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		_vect->x -= 5.0f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		_vect->x += 5.0f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		_vect->y -= 5.0f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		_vect->y += 5.0f;
	}

	_rect->move(*_vect);
}

// Vector2i means vector2 int, Vector2f means vector2 float
void MouseInputChecking(sf::Image* _CanvasRef, sf::Vector2i* _MousePos) // mouse needs reference to window relevant 
{
	for (int i = 0; i < brushSize; i++)
	{
		_CanvasRef->setPixel(_MousePos->x, _MousePos->y, *CurrentPenColour);
	
		_CanvasRef->setPixel(_MousePos->x + i, _MousePos->y, *CurrentPenColour);
		_CanvasRef->setPixel(_MousePos->x - i, _MousePos->y, *CurrentPenColour);

		_CanvasRef->setPixel(_MousePos->x, _MousePos->y + i, *CurrentPenColour);
		_CanvasRef->setPixel(_MousePos->x, _MousePos->y - i, *CurrentPenColour);
		
		_CanvasRef->setPixel(_MousePos->x + i, _MousePos->y + i, *CurrentPenColour);
		_CanvasRef->setPixel(_MousePos->x - i, _MousePos->y - i, *CurrentPenColour);
		_CanvasRef->setPixel(_MousePos->x - i, _MousePos->y + i, *CurrentPenColour);
		_CanvasRef->setPixel(_MousePos->x + i, _MousePos->y - i, *CurrentPenColour);
	}
}

int main()
{
	// -- Window Properties -- //
	sf::RenderWindow window(sf::VideoMode(WindowXSize, WindowYSize), "Blood for the blood god!");

	std::vector<sf::Shape*> shapes;
	sf::Vector2f moveVector(0, 0);

	MainManager = new CPaintToolManager;

	CurrentPenColour = new sf::Color(sf::Color::White);

	// -- Canvas Setup -- //
	sf::Image Canvas; 
	Canvas.create(WindowXSize, WindowYSize, sf::Color::Black);

	sf::Texture CanvasTexture;
	CanvasTexture.loadFromImage(Canvas); // same proccess for creating sprites

	sf::Sprite CanvasSprite;
	CanvasSprite.setTexture(CanvasTexture);
	CanvasSprite.setOrigin(WindowXSize/2, WindowYSize/2);
	CanvasSprite.setPosition(WindowXSize / 2, WindowYSize / 2);

	// -- Circle Properties -- //
	sf::CircleShape shape(50.0f);
	sf::Vector2f shapePos = sf::Vector2f(400, 300);
	shape.setOrigin(shape.getRadius(), shape.getRadius()); // Set circle origin to centre of circle with getRadius()
	shape.setPosition(shapePos);
	shape.setFillColor(sf::Color::Black);

	shape.setOutlineColor(sf::Color::White);
	shape.setOutlineThickness(10.0f);

	shapes.push_back(&shape);

	// -- Rectangle Properties -- //
	sf::RectangleShape rectShape;
	sf::Vector2f rectDimensions(100, 100);
	rectShape.setSize(rectDimensions);
	rectShape.setOutlineThickness(10.0f);
	rectShape.setFillColor(sf::Color::Black);
	rectShape.setOrigin(rectShape.getSize()/2.0f);
	rectShape.setPosition(window.getSize().x / 2.0f, (window.getSize().y / 2.0f) + 110);

	shapes.push_back(&rectShape);

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
				bDrawing = true;
			}
		}

		if (bDrawing)
		{
			MouseInputChecking(&Canvas, &sf::Mouse::getPosition(window));
			CanvasTexture.loadFromImage(Canvas);
		}
		
		if (event.type == sf::Event::MouseButtonReleased) // Calls the mouse input check
		{
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				bDrawing = false;
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
		{
			MainManager->OpenPaintDialog(&window, CurrentPenColour);
		}

		InputChecking(&rectShape, &moveVector);

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