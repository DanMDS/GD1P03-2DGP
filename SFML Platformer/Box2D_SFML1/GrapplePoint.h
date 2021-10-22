#include <SFML/Graphics.hpp>
#include "Object.h"

#pragma once

class GrapplePoint : public Object
{
private:
	float m_maxDist;

public:
	GrapplePoint();
	~GrapplePoint();

	bool CanGrapple(sf::Vector2f _mousePos, sf::Vector2f _playerPos);

	void Update() {};
};