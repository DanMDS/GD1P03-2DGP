#include "Turret.h"

Turret::Turret(Player* _player, sf::Vector2f _turretPos, std::vector<Object*>* _objVec, int* _fireRate, int* _alertDist, int* _rocketSpeed, SoundManager* _soundManager)
{
	m_objVec = _objVec;

	m_rocketSpeed = _rocketSpeed;

	m_soundManager = _soundManager;

	m_image = new sf::Image();
	if (!m_image->loadFromFile("sprites/turret.png"))
	{
		std::cout << "Error loading turret sprite";
	}
	m_image->createMaskFromColor(sf::Color::Blue);
	m_texture->loadFromImage(*m_image);
	m_sprite->setTexture(*m_texture);
	m_sprite->setPosition(_turretPos);
	m_sprite->setOrigin(m_sprite->getGlobalBounds().width / 2, m_sprite->getGlobalBounds().height / 2);
	m_sprite->setScale(sf::Vector2f(2, 2));

	m_gunImg = new sf::Image();
	m_gunTex = new sf::Texture();
	m_gunSpr = new sf::Sprite();

	if (!m_gunImg->loadFromFile("sprites/turret_gun.png"))
	{
		std::cout << "Error loading turret gun image";
	}
	m_gunTex->loadFromImage(*m_gunImg);
	m_gunSpr->setTexture(*m_gunTex);
	m_gunSpr->setOrigin(m_gunSpr->getGlobalBounds().width / 2, m_gunSpr->getGlobalBounds().height / 2);
	m_gunSpr->setScale(sf::Vector2f(2, 2));
	m_gunSpr->setPosition(m_sprite->getPosition());

	m_fireRate = _fireRate;
	m_alertDist = _alertDist;
	m_player = _player;
	m_playerDist = 0;

	m_time = m_clock.getElapsedTime();
}

Turret::~Turret()
{
	delete m_gunImg;
	delete m_gunTex;
	delete m_gunSpr;

	m_gunImg = nullptr;
	m_gunTex = nullptr;
	m_gunSpr = nullptr;
}

void Turret::Shoot()
{
	// Setting gun position and rotation
	m_gunSpr->setPosition(m_sprite->getPosition());

	float sideOpp = m_gunSpr->getPosition().y - m_playerPos.y;							// Setting pythagoras variables
	float sideAdj = m_gunSpr->getPosition().x - m_playerPos.x;

	m_gunSpr->setRotation((atan2(sideOpp, sideAdj) * (180.0f / b2_pi)) + (270.0f / b2_pi));		// Setting rotation and size

	if (m_clock.getElapsedTime().asMilliseconds() - m_time.asMilliseconds() > *m_fireRate)
	{
		// Shoot
		m_objVec->push_back(new Rocket(m_player->GetSprite()->getPosition(), m_sprite->getPosition(), m_player, *m_rocketSpeed));
		m_soundManager->PlaySoundShootEnemy();
		m_time = m_clock.getElapsedTime();
	}
}

void Turret::Update()
{
	// Setting player position
	m_playerPos = m_player->GetSprite()->getPosition();

	// Set player dist
	m_playerDist = sqrt(
		((m_playerPos.x - m_sprite->getPosition().x) * (m_playerPos.x - m_sprite->getPosition().x))
		+ ((m_playerPos.y - m_sprite->getPosition().y) * (m_playerPos.y - m_sprite->getPosition().y)));

	// If player is close enough, shoot
	if (m_playerDist < *m_alertDist)
	{
		Shoot();
	}
}
