#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include <iostream>

#pragma once

class PlayerContactListener : public b2ContactListener
{
private:
	int contacts = 0;

public:
	void BeginContact(b2Contact* contact)	{ contacts++;							 };

	void EndContact(b2Contact* contact)		{ contacts--;							 };

	bool IsGrounded()						{ return (contacts == 0) ? false : true; };
};