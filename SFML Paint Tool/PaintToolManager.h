#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <windows.h>
#include <wingdi.h> // windows gdi

class CPaintToolManager
{
private:

public:
	std::vector<sf::Shape*> shapes;

	bool isPaintDialogOpen = false; // functions like a pause menu for the paint software

	CHOOSECOLOR cc; // Common dialog box structure
	COLORREF acrCustClr[16];// Array of custom colours
	HWND hwnd; // Owne window
	// HBRUSH hbrush; // brush handle
	DWORD rgbCurrent; // initial colour selection
	COLORREF cr;

	CPaintToolManager();
	~CPaintToolManager();
	sf::Color* OpenPaintDialog(sf::Window* _windowRef, sf::Color* _Colouref);

	sf::Vertex* DrawLine(sf::Color* _Colour);
	void DrawPen(sf::Texture _CanvasTextRef, sf::Image* _CanvasRef, sf::Vector2i* _MousePos, int _BrushSize, sf::Color* _PenColour);
};