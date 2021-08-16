#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <windows.h>
#include <wingdi.h> // windows gdi

class CPaintToolManager
{
private:

public:
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
};
