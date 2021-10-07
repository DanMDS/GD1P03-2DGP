// Non-Local Includes
#include <iostream>

// Local Includes
#include "CExample.h"

namespace Utils
{
	const int WINDOWWIDTH = 640;
	const int WINDOWHEIGHT = 640;
	const float m_Scale = 30.0f;
};

// Forward Declaration
void Start();

void Update();
void BodyUpdates();

void Render();

void InitView();
void InitStatic();

void CenterViewTo(sf::RectangleShape _object);




// Main Render Window
sf::RenderWindow* m_RenderWindow;

// Main View / Camera
sf::View m_View;

// b2World
b2Vec2 m_Gravity(0.0f, 10.0f);
b2World m_World(m_Gravity);

// Player
CExample* m_Player;

// Static Block
sf::RectangleShape m_Shape;
b2Body* m_Body;
b2BodyDef m_BodyDef;
b2PolygonShape m_b2pShape;
b2FixtureDef m_FixtureDef;



int main()
{
	// Render Window Settings
	sf::ContextSettings m_Settings;
	m_Settings.antialiasingLevel = 8;

	// Render Window Creation
	m_RenderWindow = new sf::RenderWindow(sf::VideoMode(Utils::WINDOWWIDTH, Utils::WINDOWHEIGHT), "SFML and box2D works!", sf::Style::Default, m_Settings);
	m_RenderWindow->setFramerateLimit(60);


	Start();
	Update();


	// Cleanup
	m_World.DestroyBody(m_Body);
	delete m_Player;
	delete m_RenderWindow;
	m_Player = nullptr;
	m_RenderWindow = nullptr;

	return 0;
}

void Start()
{
	m_Player = new CExample(m_RenderWindow, m_World, Utils::m_Scale);

	InitStatic();
	InitView();
	CenterViewTo(m_Player->GetShape());
}

void Update()
{
	while (m_RenderWindow->isOpen())
	{
		std::cout << m_Shape.getPosition().x << std::endl;
		std::cout << m_Shape.getPosition().y << std::endl;

		sf::Event event;
		while (m_RenderWindow->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				m_RenderWindow->close();
				break;
			}
		}

		// Centre View To Player
		CenterViewTo(m_Player->GetShape());

		// World Step
		m_World.Step(1 / 60.f, 10, 30);

		// Body Updates
		BodyUpdates();

		// Render
		Render();
	}
}

void Render()
{
	m_RenderWindow->clear();

	
	m_Player->Render();
	m_RenderWindow->draw(m_Shape);


	m_RenderWindow->display();
}

void InitView()
{
	m_View = sf::View(sf::Vector2f(0.0f,0.0f), sf::Vector2f(m_RenderWindow->getSize().x, m_RenderWindow->getSize().y));
	m_RenderWindow->setView(m_View);
}

void CenterViewTo(sf::RectangleShape _object)
{
	m_View.setCenter(_object.getPosition());
	m_RenderWindow->setView(m_View);
}

void BodyUpdates()
{
	// Bodies
	for (b2Body* BodyIterator = m_World.GetBodyList(); BodyIterator != 0; BodyIterator = BodyIterator->GetNext())
	{
		// Dynamic
		if (BodyIterator->GetType() == b2_dynamicBody)
		{
			m_Player->Update(BodyIterator);
		}

		// Static
		else if (BodyIterator->GetType() == b2_staticBody)
		{
			// Set SFML Shape Transform To Box 2D Body Transform
			m_Shape.setOrigin(50, 50);
			m_Shape.setPosition(BodyIterator->GetPosition().x * Utils::m_Scale, BodyIterator->GetPosition().y * Utils::m_Scale);
			m_Shape.setRotation(BodyIterator->GetAngle() * 180 / b2_pi);
		}
	}
}

// Ground
void InitStatic()
{
	// b2Body Type And Position And Creation
	m_BodyDef.position = b2Vec2(100 / Utils::m_Scale, 300 / Utils::m_Scale);
	m_BodyDef.type = b2_staticBody;
	m_Body = m_World.CreateBody(&m_BodyDef);

	// Fixture Size
	m_b2pShape.SetAsBox((100 / 2) / Utils::m_Scale, (100 / 2) / Utils::m_Scale);

	// Hard Fixture
	m_FixtureDef.density = 1.0f;
	m_FixtureDef.shape = &m_b2pShape;
	m_Body->CreateFixture(&m_FixtureDef);

	// SFML Sprite / Shape
	m_Shape.setFillColor(sf::Color::Green);
	m_Shape.setSize(sf::Vector2f(100, 100));
	m_Shape.setOrigin(m_Shape.getGlobalBounds().width / 2, m_Shape.getGlobalBounds().height / 2);
	m_Shape.setPosition(m_Body->GetPosition().x * Utils::m_Scale, m_Body->GetPosition().y * Utils::m_Scale);
	m_Shape.setRotation(m_Body->GetAngle() * 180 / b2_pi);
}
