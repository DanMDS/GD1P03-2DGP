#include "CPaintTool.h"

int main()
{
	CPaintTool* PaintTool = new CPaintTool();

	PaintTool->RunProgram();

	delete PaintTool;
	PaintTool = nullptr;

	return 0;
}