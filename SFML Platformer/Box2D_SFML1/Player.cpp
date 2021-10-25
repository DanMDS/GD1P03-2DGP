#include "Player.h"

Player::Player(b2Vec2 _pos, b2World* m_world, const float& _scale)
{
	tag = "player";

	m_grounded = false;
	m_jumpPower = 15.0f;
	m_speed = 50.0f;

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

Player::~Player()
{
	delete box2d;
	box2d = nullptr;
}

void Player::Update()
{
	m_sprite->setPosition(m_colliderBounds->getPosition());
	m_sprite->setRotation(m_colliderBounds->getRotation());
	box2d->Update();
}


void Player::Jump(float _power)
{
	box2d->SetVelocity(b2Vec2(box2d->GetVelocity().x, -_power));
}

void Player::PlayerControls(bool _grounded)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && _grounded)
	{
		Jump(m_jumpPower);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		if (box2d->GetVelocity().x > -m_speed / 4)
		{
			box2d->GetBody()->ApplyForce(b2Vec2(-m_speed, box2d->GetVelocity().y), box2d->GetBody()->GetPosition(), true);
		}
		else
		{
			box2d->GetBody()->SetLinearVelocity(b2Vec2(-m_speed / 4, box2d->GetVelocity().y));
		}
	}
	else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::A) && sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		if (box2d->GetVelocity().x < m_speed / 4)
		{
			box2d->GetBody()->ApplyForce(b2Vec2(m_speed, box2d->GetVelocity().y), box2d->GetBody()->GetPosition(), true);
		}
		else
		{
			box2d->GetBody()->SetLinearVelocity(b2Vec2(m_speed / 4, box2d->GetVelocity().y));
		}
	}

	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		box2d->GetBody()->SetLinearVelocity(b2Vec2(box2d->GetVelocity().x, box2d->GetVelocity().y));
	}
}
