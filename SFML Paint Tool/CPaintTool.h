#pragma once
#include "PaintToolManager.h"

class CPaintTool
{
	// Variable setup
	int toolChoice;

	// Tool enum setup
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

	tool Tool;

	// Class object setup
	CPaintToolManager* MainManager;

	// Window size variable setup
	int WindowXSize{};
	int WindowYSize{};

	// Toolbar offset is for the tool selection square movement
	float toolbarOffset{};

	// "Is the colour picker open" setup
	bool paintDialogOpen{};

	// Pen colour setup
	sf::Color* CurrentPenColour;

public:
	// Method setup
	CPaintTool();
	~CPaintTool();

	void RunProgram();
};