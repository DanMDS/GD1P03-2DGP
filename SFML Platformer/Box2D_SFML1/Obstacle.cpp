#include "Obstacle.h"

Obstacle::Obstacle(b2Vec2 _pos, b2World* m_world, const float& _scale)
{
	if (!m_texture->loadFromFile("sprites/player.png"))
	{
		std::cout << "Error, loading texture";
	}
	m_sprite->setTexture(*m_texture);
	m_sprite->setOrigin(m_sprite->getGlobalBounds().width / 2, m_sprite->getGlobalBounds().height / 2);

	m_colliderBounds = new sf::RectangleShape(sf::Vector2f(m_sprite->getGlobalBounds().width, m_sprite->getGlobalBounds().height));
	m_colliderBounds->setOutlineColor(sf::Color::Blue);
	m_colliderBounds->setOutlineThickness(1);

	box2d = new Box2d(m_world, _scale, m_colliderBounds, _pos, true);
};

Obstacle::~Obstacle()
{
	delete box2d;
	box2d = nullptr;
}

void Obstacle::Update()
{
	m_sprite->setPosition(m_colliderBounds->getPosition());
	m_sprite->setRotation(m_colliderBounds->getRotation());
	box2d->Update();
}
