#include "box2d/b2_fixture.h"
#include "Player.h"
#include "Obstacle.h"
#include "LevelObstacle.h"
#include "PlayerContactListener.h"
#include "Object.h"
#include "GrapplePoint.h"
#include <iostream>

bool canJump = false;
std::vector<Object*> ObjVec;
std::vector<GrapplePoint*> grappleVec;

sf::RectangleShape* line;

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

	Player* player = new Player(b2Vec2(300, 400), m_world, scale);
	ObjVec.push_back(player);

	ObjVec.push_back(new LevelObstacle(sf::Vector2f(500, 500), b2Vec2(500, 800), m_world, scale));
	ObjVec.push_back(new LevelObstacle(sf::Vector2f(500, 500), b2Vec2(800, 500), m_world, scale));
	grappleVec.push_back(new GrapplePoint(player, b2Vec2(0, 450), m_world, scale));

	for (auto& itr : grappleVec)
	{
		ObjVec.push_back(itr);
	}

	sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(1280, 720), "deez nuts", sf::Style::Close);
	window->setFramerateLimit(60);
	sf::View view = window->getView();
	window->setView(view);

	sf::Event event;

	while (window->isOpen())
	{
		window->setView(view);
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window->close();
			}

			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					for (auto& itr : grappleVec)
					{
						itr->GrappleStart();
					}
				}
			}
			
			if (event.type == sf::Event::MouseButtonReleased)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					for (auto& itr : grappleVec)
					{
						itr->GrappleEnd();
					}
				}
			}
		}
		for (auto& itr : grappleVec)
		{
			if (itr->Grappling()) { continue; }
			player->PlayerControls(contactListener->IsGrounded());
			break;
		}
		window->clear(sf::Color::Cyan);

		for (auto& itr : grappleVec)
		{
			itr->Update(window);
		}

		for (auto& itr : ObjVec)
		{
			itr->Update();
			if (itr->GetTag() == "levelObstacle")
			{
				window->draw(*itr->GetShape());
				continue;
			}
			window->draw(*itr->GetSprite());
		}
		view.setCenter(sf::Vector2f(player->GetSprite()->getPosition().x, player->GetSprite()->getPosition().y));

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