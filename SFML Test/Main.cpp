#include <SFML/Graphics.hpp>

void InputChecking(sf::RectangleShape* rect, sf::Vector2f* move, float speed)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		move->x = -speed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		move->x = speed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		move->y = -speed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		move->y = speed;
	}

	rect->move(*move);
}

int main()
{
	std::vector<sf::Shape*> shapes;

	// Player input move vector
	sf::Vector2f moveVector;

	// Window properties
	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");
	
	// Variables
	float speed = 0.01f;

	// Circle properties
	sf::CircleShape shape(50.0f);
	sf::Vector2f shapePos = sf::Vector2f(400, 300);
	shape.setOrigin(shape.getRadius(), shape.getRadius());	// Set origin to centre of circle
	shape.setPosition(shapePos);
	shape.setFillColor(sf::Color::Green);

	shapes.push_back(&shape);

	sf::RectangleShape rectShape;
	sf::Vector2f rectDimensions(150, 50);
	rectShape.setSize(rectDimensions);
	rectShape.setOrigin(rectShape.getSize()/2.0f);
	rectShape.setFillColor(sf::Color::Cyan);
	rectShape.setPosition(window.getSize().x / 2.0f, window.getSize().y / 2.0f);

	shapes.push_back(&rectShape);

	while (window.isOpen())
	{
		moveVector.x = 0;
		moveVector.y = 0;

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}

			if (event.type == sf::Event::KeyPressed)
			{
				/*if (event.key.code == sf::Keyboard::Left)
				{
					moveVector.x = -5.0f;
				}
				if (event.key.code == sf::Keyboard::Right)
				{
					moveVector.x = 5.0f;
				}
				if (event.key.code == sf::Keyboard::Up)
				{
					moveVector.y = -5.0f;
				}
				if (event.key.code == sf::Keyboard::Down)
				{
					moveVector.y = 5.0f;
				}
				rectShape.move(moveVector);*/

				if (event.key.code == sf::Keyboard::A)
				{
					shape.setRadius(shape.getRadius() - 5);
				}
				if (event.key.code == sf::Keyboard::D)
				{
					shape.setRadius(shape.getRadius() + 5);
				}
				shape.setOrigin(shape.getRadius(), shape.getRadius());
			}
		}

		InputChecking(&rectShape, &moveVector, speed);

		window.clear();

		for (int i = 0; i < shapes.size(); i++)
		{
			window.draw(*shapes[i]);
		}

		window.display();
	}
	
	return 0;
}