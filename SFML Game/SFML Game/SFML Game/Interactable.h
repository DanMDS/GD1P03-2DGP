#include <SFML/Graphics.hpp>

#pragma once
/*
	Class: Interactable
	Description: Class for interactables to handle interactions with player
	Written by: Daniel Bolleboom
*/
class Interactable
{
private:
	// Bool for checkign whether to run interact script
	bool m_canInteract;

protected:
	// Sprite 
	sf::Sprite* m_intSprite;

	// Position
	sf::Vector2f pos;

	// Values and bools for easy calculations
	int m_distance;
	bool m_interacted;
	bool m_isDoor;
	bool m_isButton;

public:

	// Methods
	bool Interact(sf::Vector2f _playerPos, sf::Vector2f _interactPos);

	// Getters and setters
	sf::Vector2f GetInteractPos()			{ return pos;					};
	sf::Sprite* GetSprite()					{ return m_intSprite;			};
	int GetDistance()						{ return m_distance;			};
	bool GetInteracted()					{ return m_interacted;			};
	bool GetIsDoor()						{ return m_isDoor;				};
	bool GetIsButton()						{ return m_isButton;			};

	void SetInteracted(bool _interacted)	{ m_interacted = _interacted;	};

	// Update method, different for each ineractable
	virtual void Update(){};

	// Constructor/destructor
	Interactable();
	~Interactable();
};