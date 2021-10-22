#include "box2d/b2_fixture.h"
#include "Player.h"
#include "LevelObstacle.h"
#include "PlayerContactListener.h"
#include "Object.h"
#include <iostream>

bool canJump = false;
std::vector<Object*> ObjVec;
std::vector<Object*>::iterator itObjVec;

sf::ContextSettings contSet;

int main()
{
	contSet.antialiasingLevel = 8;

	float scale = 30.0f;
	b2Vec2 m_Gravity(0.0f, 50.0f);
	b2World* m_world;
	m_world = new b2World(m_Gravity);
	PlayerContactListener* contactListener = new PlayerContactListener();
	m_world->SetContactListener(contactListener);

	Player* player = new Player(b2Vec2(500, 400), m_world, scale);
	ObjVec.push_back(player);

	ObjVec.push_back(new LevelObstacle(b2Vec2(500, 800), m_world, scale));
	ObjVec.push_back(new LevelObstacle(b2Vec2(900, 800), m_world, scale));

	sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(1280, 720), "deez nuts", sf::Style::Close);
	window->setFramerateLimit(60);
	sf::View view = window->getView();
	window->setView(view);

	sf::Event event;

	while (window->isOpen())
	{
		view.setCenter(sf::Vector2f(player->GetSprite()->getPosition().x + 400, player->GetSprite()->getPosition().y));
		window->setView(view);
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window->close();
			}
		}

		player->PlayerControls(contactListener->IsGrounded());
		window->clear(sf::Color::White);

		for (auto& itr : ObjVec)
		{
			itr->Update();
			window->draw(*itr->GetSprite());
		}

		window->display();

		m_world->Step(1.0f / 60.0f, 10, 30);
	}

	for (auto& itr : ObjVec)
	{
		delete itr;
		itr = nullptr;
	}
	ObjVec.clear();

	return 0;
}