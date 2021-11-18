#include <fstream>
#include "OptionButton.h"
#include "Player.h"
#include "Turret.h"

#pragma once

class Debug
{
private:
	sf::RenderWindow* m_windowD;

	std::vector<OptionButton*> m_buttonVec;
	std::ifstream m_fileIn;
	std::ofstream m_fileOut;

	sf::Font m_font;

	int m_input;

	bool m_windowOpen;

	sf::Vector2f m_mousePos;

	Player* m_player;
	int* m_turretShootCooldown;
	int* m_turretAlertDist;
	int* m_playerShoot;
	int* m_rocketSpeed;

public:
	Debug(Player* _player, int* _turretShootCooldown, int* _turretAlertDist, int* _playerShoot, int* _rocketSpeed);
	~Debug();

	void OpenWindow();
	void CheckButtons();

	int* GetValue(int _index) { return m_buttonVec[_index]->GetValue(); }
};