#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include <iostream>
#include "SoundManager.h"

#pragma once

class PlayerContactListener : public b2ContactListener
{
private:
	int contacts = 0;
	SoundManager* m_soundManager;

public:
	PlayerContactListener(SoundManager* _soundManager) 
											{ m_soundManager = _soundManager;				}
	
	~PlayerContactListener() {};

	void BeginContact(b2Contact* contact)	{ contacts++; m_soundManager->PlaySoundLand();	};

	void EndContact(b2Contact* contact)		{ contacts--;									};

	bool IsGrounded()						{ return (contacts == 0) ? false : true;		};
};