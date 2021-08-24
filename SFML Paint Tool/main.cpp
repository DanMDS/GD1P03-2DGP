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