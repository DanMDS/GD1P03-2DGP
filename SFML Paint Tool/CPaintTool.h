#pragma once
#include "PaintToolManager.h"

class CPaintTool
{
	// Variable setup
	int toolChoice;
	std::string fileName;

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

	void Save(sf::RenderWindow* _Window, std::string* _Name);
	void Load();
	void RunProgram();
};