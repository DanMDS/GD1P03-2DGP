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
	sf::Image Canvas;
	sf::Texture CanvasTexture;
	sf::Sprite CanvasSprite;

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

	void DrawPen(sf::Vector2i* _MousePos, int _BrushSize, sf::Color* _PenColour);

	sf::RectangleShape* DrawRect(sf::Vector2i* _MousePos, sf::Color* _PenColour, sf::RenderWindow* _Window);
	sf::CircleShape* DrawCirc(sf::Vector2i* _MousePos, sf::Color* _PenColour, sf::RenderWindow* _Window);
};