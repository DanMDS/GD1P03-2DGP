#pragma once
#include "PaintToolManager.h"

class CPaintTool
{
	int drawMode = 1;

	int toolChoice = 0;
	enum class tool
	{
		Pen,
		Circle,
		Rectangle,
		Line,
		Poly,
		Stamp,
		Last
	};

	tool Tool = tool::Pen;

	CPaintToolManager* MainManager;

	std::vector<sf::VideoMode> modes;

	int WindowXSize{};
	int WindowYSize{};

	float toolbarOffset{};

	bool paintDialogOpen{};

	sf::Color* CurrentPenColour;

public:
	CPaintTool();
	~CPaintTool();

	void RunProgram();
};