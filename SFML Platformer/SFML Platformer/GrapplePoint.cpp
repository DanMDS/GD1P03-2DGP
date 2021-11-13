#include "GrapplePoint.h"
#include <iostream>

GrapplePoint::GrapplePoint(Player* _player, b2Vec2 _pos, b2World* m_world, const float& _scale)
{
	tag = Tag::GrapplePoint;
	world = m_world;

	m_scale = _scale;

	m_maxDist = 10.0f;
	m_playerDist = 0.0f;

	sideOpp = 0.0f;
	sideAdj = 0.0f;
	sideHyp = 0.0f;
	angle = 0.0f;
	lineThickness = 5.0f;

	m_image = new sf::Image();

	if (!m_image->loadFromFile("sprites/grapple.png"))
	{
		std::cout << "Error, loading image";
	}
	m_image->createMaskFromColor(sf::Color::White);

	m_texture->loadFromImage(*m_image);

	m_sprite->setTexture(*m_texture);
	m_sprite->setOrigin(m_sprite->getGlobalBounds().width / 2, m_sprite->getGlobalBounds().height / 2);

	m_colliderBounds = new sf::RectangleShape(sf::Vector2f(m_sprite->getGlobalBounds().width, m_sprite->getGlobalBounds().height));
	m_colliderBounds->setOutlineColor(sf::Color::Blue);
	m_colliderBounds->setOutlineThickness(1);
	
	m_player = _player;

	box2d = new Box2d(m_world, _scale, m_colliderBounds, _pos);

	m_sprite->setPosition(m_colliderBounds->getPosition());
	m_sprite->setRotation(m_colliderBounds->getRotation());

	m_selectionCircle = new sf::CircleShape(m_sprite->getGlobalBounds().height / 2);
	m_selectionCircle->setFillColor(sf::Color::Transparent);
	m_selectionCircle->setOutlineColor(sf::Color::Red);
	m_selectionCircle->setOutlineThickness(3);
	m_selectionCircle->setOrigin(sf::Vector2f(m_sprite->getGlobalBounds().height / 2, m_sprite->getGlobalBounds().height / 2));
	m_selectionCircle->setPosition(m_sprite->getPosition());

	distanceDef = nullptr;
	distanceJoint = nullptr;

	m_line = new sf::RectangleShape();
	m_line->setFillColor(sf::Color::Black);
	m_line->setOrigin(lineThickness / 2, 0);
}

GrapplePoint::~GrapplePoint()
{
	delete box2d;
	//delete distanceDef;

	box2d = nullptr;
	//distanceDef = nullptr;
}

bool GrapplePoint::CanGrapple()
{
	// Checking if player is close enough to grapple

	int playerX = m_player->GetSprite()->getPosition().x / m_scale;
	int playerY = m_player->GetSprite()->getPosition().y / m_scale;

	int grappleX = m_sprite->getPosition().x / m_scale;
	int grapplyY = m_sprite->getPosition().y / m_scale;

	m_playerDist = sqrt(((playerX - grappleX) * (playerX - grappleX)) + ((playerY - grapplyY) * (playerY - grapplyY)));

	return m_playerDist <= m_maxDist;
}

void GrapplePoint::GrappleStart()
{
	if (CanGrapple())
	{
		printf("grapple start;");
		distanceDef = new b2DistanceJointDef();

		distanceDef->Initialize(box2d->GetBody(),
			m_player->GetB2d()->GetBody(),
			box2d->GetBody()->GetWorldCenter(),
			m_player->GetB2d()->GetBody()->GetWorldCenter());

		distanceDef->maxLength = m_playerDist + 1.0f;
		distanceDef->minLength = 0.1f;

		distanceJoint = (b2DistanceJoint*)world->CreateJoint(distanceDef);

		m_grappling = true;
	}
	else
	{
		return;
	}
}

void GrapplePoint::GrappleEnd()
{
	if (m_grappling)
	{
		printf("grapple end;");
		world->DestroyJoint(distanceJoint);
		m_grappling = false;
	}
}


void GrapplePoint::Update(sf::RenderWindow* _window)
{
	sf::Vector2f grapplePos = m_sprite->getPosition();

	m_line->setPosition(grapplePos);			// Set position

	playerPos = m_player->GetSprite()->getPosition();	// Changing position to match with rotation

	sideOpp = grapplePos.y - playerPos.y;							// Setting pythagoras variables
	sideAdj = grapplePos.x - playerPos.x;
	sideHyp = sqrt((sideOpp * sideOpp) + (sideAdj * sideAdj));

	m_lineDimensions = sf::Vector2f(-sideHyp, float(lineThickness));						// Changing line dimensions

	angle = atan2(sideOpp, sideAdj) * (180.0f / b2_pi);						// Setting rotation angle

	m_line->setRotation(angle);											// Setting rotation and size
	m_line->setSize(m_lineDimensions);

	if (m_grappling)
	{
		_window->draw(*m_line);
	}

	if (CanGrapple() || m_grappling)
	{
		_window->draw(*m_selectionCircle);
	}
}