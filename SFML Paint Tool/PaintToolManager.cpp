#include "PaintToolManager.h"

CPaintToolManager::CPaintToolManager()
{

}

CPaintToolManager::~CPaintToolManager()
{
}

sf::Color* CPaintToolManager::OpenPaintDialog(sf::Window* _windowRef, sf::Color* _Colourref)
{
	hwnd = _windowRef->getSystemHandle();

	// -- Initialise CHOOSECOLOR -- //
	ZeroMemory(&cc, sizeof(cc));
	cc.lStructSize = sizeof(cc);
	cc.hwndOwner = hwnd;

	cc.lpCustColors = (LPDWORD)acrCustClr;
	cc.rgbResult = rgbCurrent;
	cc.Flags = CC_FULLOPEN | CC_RGBINIT;

	if (ChooseColor(&cc) == TRUE) // if the user has chosen a colour when closing the color picker window
	{
		cr = cc.rgbResult;

		sf::Color tempColour;

		tempColour.r = GetRValue(cr);
		tempColour.g = GetGValue(cr);
		tempColour.b = GetBValue(cr);

		*_Colourref = tempColour; // Setting our circle to the new colour
		return _Colourref;
	}

}

void CPaintToolManager::DrawPen(sf::Texture _CanvasTextRef, sf::Image* _CanvasRef, sf::Vector2i* _MousePos, int _BrushSize, sf::Color* _PenColour)
{
	for (int i = -_BrushSize; i < _BrushSize / 2; i++)
	{
		for (int j = -_BrushSize; j < _BrushSize / 2; j++)
		{
			_CanvasRef->setPixel(_MousePos->x + j, _MousePos->y + i, *_PenColour);
		}
	}
}
