#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include "Player.h"
#include "Object.h"

#pragma once

class GrapplePoint : public Object
{
private:
	float m_maxDist;
	float m_playerDist;
	Player* m_player;

	sf::RectangleShape* m_line;
	sf::Vector2f m_lineDimensions;
	sf::Vector2f playerPos;
	float sideOpp;
	float sideAdj;
	float sideHyp;
	float angle;
	float lineThickness;

	sf::CircleShape* m_selectionCircle;

	bool m_grappling = false;

	b2DistanceJointDef* distanceDef;
	b2DistanceJoint* distanceJoint;

public:
	GrapplePoint(Player* _player, b2Vec2 _pos, b2World* m_world, const float& _scale);
	~GrapplePoint();

	bool CanGrapple();
	void GrappleStart();
	void GrappleEnd();

	bool Grappling()				{ return m_grappling;	};

	sf::RectangleShape* GetLine()	{ return m_line;		};

	void Update(sf::RenderWindow* _window);
};