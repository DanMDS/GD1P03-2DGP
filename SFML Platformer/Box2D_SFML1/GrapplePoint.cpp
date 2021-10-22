#include "GrapplePoint.h"

GrapplePoint::GrapplePoint()
{
	m_maxDist = 100.0f;
}

GrapplePoint::~GrapplePoint()
{
}

bool GrapplePoint::CanGrapple(sf::Vector2f _mousePos, sf::Vector2f _playerPos)
{
	return false;
}
