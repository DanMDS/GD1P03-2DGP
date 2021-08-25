/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2021 Media Design School
File Name : main.cpp
Description : Main file for code execution
Author : Daniel Bolleboom
Mail : daniel.bolleboom@mds.ac.nz
**************************************************************************/
#include "CPaintTool.h"

int main()
{
	// Create main class object
	CPaintTool* PaintTool = new CPaintTool();

	// Run program
	PaintTool->RunProgram();

	// Deallocate memory
	delete PaintTool;
	PaintTool = nullptr;

	// End program
	return 0;
}