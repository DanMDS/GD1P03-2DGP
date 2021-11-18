#include "Player.h"

Player::Player(b2Vec2 _pos, SoundManager* _soundManager, b2World* m_world, const float& _scale)
{
	tag = Tag::Player;

	m_posBoundsMax = b2Vec2(0, 0);
	m_posBoundsMin = b2Vec2(0, 0);

	m_soundManager = _soundManager;

	m_scale = _scale;

	m_maxSpeed = 30.0f;

	m_trans = new sf::CircleShape(10);
	m_trans->setFillColor(sf::Color::Red);
	m_trans->setOrigin(m_trans->getGlobalBounds().width / 2,
		m_trans->getGlobalBounds().height / 2);

	m_transDone = false;
	m_isDead = false;

	m_explodeDir = b2Vec2(0, 0);
	m_explodeDist = 0;
	m_explodeMag = 0;

	m_grounded = false;
	m_jumpPower = 15.0f;
	m_speed = 50.0f;

	m_startPos = _pos;

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

	jumpTime = clock.getElapsedTime();

	m_jumpCooldown = 100.0f;
};

Player::~Player()
{

}

void Player::Update()
{
	//std::cout << "Player X pos: " << box2d->GetBody()->GetPosition().x << "\nPlayer Y pos : " << box2d->GetBody()->GetPosition().y << "\n\n";

	// Updating box2d collider position and moving sprite with it
	box2d->Update();
	m_sprite->setPosition(m_colliderBounds->getPosition());
	m_sprite->setRotation(m_colliderBounds->getRotation());



	// If not transitioning, do player movement
	if (!m_isDead)
	{
		if (box2d->GetBody()->GetLinearVelocity().x > m_maxSpeed)
		{
			box2d->SetVelocity(b2Vec2(m_maxSpeed, box2d->GetBody()->GetLinearVelocity().y));
		}
		if (box2d->GetBody()->GetLinearVelocity().x < -m_maxSpeed)
		{
			box2d->SetVelocity(b2Vec2(-m_maxSpeed, box2d->GetBody()->GetLinearVelocity().y));
		}
	}
	// If transitioning, change scale and position of transition circle depending on if the player has teleported yet
	else
	{
		m_trans->setPosition(m_sprite->getPosition());
		if (!m_transDone)
		{
			if (m_trans->getScale().x < 250)
			{
				m_trans->setScale(sf::Vector2f(m_trans->getScale().x * 1.1, m_trans->getScale().y * 1.1));
			}
			else
			{
				// Moving player to next respawn point, will change if level changes
				box2d->GetBody()->SetTransform(b2Vec2(m_startPos.x / m_scale, m_startPos.y / m_scale), box2d->GetBody()->GetAngle());
				box2d->Update();

				m_sprite->setPosition(m_colliderBounds->getPosition());
				m_sprite->setRotation(m_colliderBounds->getRotation());
				m_trans->setPosition(m_sprite->getPosition());

				// Setting bool for use in other classes
				m_transDone = true;
			}
		}
		else
		{
			if (m_trans->getScale().x > 1)
			{
				m_trans->setScale(sf::Vector2f(m_trans->getScale().x / 1.1, m_trans->getScale().y / 1.1));
			}
			else
			{
				// Setting body back to dynamic and not fixed rotation
				m_isDead = false;
				box2d->GetBody()->SetFixedRotation(false);
				box2d->GetBody()->SetType(b2_dynamicBody);
			}
		}
		box2d->SetVelocity(b2Vec2(0, 0));
	}

	// Killing player if they leave level bounds
	if (!m_isDead && (GetBodyPos().x > m_posBoundsMax.x || GetBodyPos().y > m_posBoundsMax.y || GetBodyPos().x < m_posBoundsMin.x || GetBodyPos().y < m_posBoundsMin.y))
	{
		Transition(true);
	}
}

void Player::Jump(float _power)
{
	box2d->SetVelocity(b2Vec2(box2d->GetVelocity().x, -_power));
}

void Player::Explode(sf::Vector2f _rocketPos, float _power)
{
	// Applying force in opposite direction of destroyed rocket for rocket jumping

	// Calculating direction
	m_explodeDir = b2Vec2(m_sprite->getPosition().x - _rocketPos.x, m_sprite->getPosition().y - _rocketPos.y);

	// Calculating distance, doing some weird square root stuff so that force scales intuitively with
	// distance from explosion point, makes the game feel nicer to play
	m_explodeDist = sqrt((m_explodeDir.x * m_explodeDir.x) + (m_explodeDir.y * m_explodeDir.y));
	m_explodeDist *= m_explodeDist;
	m_explodeDist = sqrt(m_explodeDist);

	// Doing nothing if explosion is too far away
	if (m_explodeDist < 150.0f)
	{
		m_explodeDir = b2Vec2((m_explodeDir.x * 1.5f * _power) / 10.0f, (m_explodeDir.y * _power) / 10.0f);
		box2d->GetBody()->ApplyLinearImpulse(m_explodeDir, box2d->GetBody()->GetPosition(), true);
	}
}

void Player::PlayerControls(bool _grounded)
{
	// Jumping
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && _grounded)
	{
		// Cooldown on jump so that the player doesn't get stuck to the roof when they hold the space bar
		if (clock.getElapsedTime().asMilliseconds() - jumpTime.asMilliseconds() > m_jumpCooldown)
		{
			Jump(m_jumpPower);
			jumpTime = clock.getElapsedTime();
		}
	}
	// Moving left and right
	// Using ApplyForce and max speed for smooth movement
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		if (box2d->GetVelocity().x > -m_speed / 4)
		{
			box2d->GetBody()->ApplyForce(b2Vec2(-m_speed, box2d->GetVelocity().y), box2d->GetBody()->GetPosition(), true);
		}
	}
	else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::A) && sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		if (box2d->GetVelocity().x < m_speed / 4)
		{
			box2d->GetBody()->ApplyForce(b2Vec2(m_speed, box2d->GetVelocity().y), box2d->GetBody()->GetPosition(), true);
		}
	}
}

void Player::Transition(bool _dead)
{
	// Updating sprite so that the player remains completely stationary during transition
	// Update(); <--- Causes stack overflow, not needed since sprite doesn't move anyway

	// Setting bools, color of transition circle and body type for screen transition
	m_isDead = true;
	m_transDone = false;
	m_trans->setFillColor(_dead ? sf::Color::Red : sf::Color::Green);

	// Setting rotation to fixed and body type to kinematic so that the player doesn't move during the transition
	box2d->GetBody()->SetFixedRotation(true);
	box2d->GetBody()->SetType(b2_kinematicBody);

	// Playing win/lose sound
	_dead ? m_soundManager->PlaySoundDie() : m_soundManager->PlaySoundWin();
}

void Player::SetStartPos(b2Vec2 _pos, bool _checkpoint)
{
	// Setting respawn point for level
	m_startPos = _pos;
	if (!_checkpoint)
	{
		box2d->GetBody()->SetTransform(b2Vec2(_pos.x / m_scale, _pos.y / m_scale), box2d->GetBody()->GetAngle());
		box2d->Update();
		m_sprite->setPosition(m_colliderBounds->getPosition());
		m_sprite->setRotation(m_colliderBounds->getRotation());
	}
}
