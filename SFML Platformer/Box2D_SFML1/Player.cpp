#include "Player.h"

Player::Player(b2Vec2 _pos, b2World* m_world, const float& _scale)
{
	m_grounded = false;
	m_jumpPower = 15.0f;
	m_speed = 0.0f;
	m_speedMax = 10.0f;
	m_speedInc = 1.0f;

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

void Player::Move(float _speed)
{
	if ((_speed < 0 && box2d->GetVelocity().x > _speed) || (_speed > 0 && box2d->GetVelocity().x < _speed))
	{
		box2d->SetVelocity(b2Vec2(_speed, box2d->GetVelocity().y));
	}
}

void Player::PlayerControls(bool _grounded)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && _grounded)
	{
		Jump(m_jumpPower);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		m_speed = (m_speed > -m_speedMax) ? m_speed - m_speedInc : m_speed;
		Move(m_speed);
	}
	else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::A) && sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		m_speed = (m_speed < m_speedMax) ? m_speed + m_speedInc : m_speed;
		Move(m_speed);
	}

	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		m_speed = box2d->GetVelocity().x;
	}
}
