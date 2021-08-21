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
	sf::CircleShape cursor;

	int brushSize;

	bool isPaintDialogOpen;

	CHOOSECOLOR cc; // Common dialog box structure
	COLORREF acrCustClr[16];// Array of custom colours
	HWND hwnd; // Owne window
	// HBRUSH hbrush; // brush handle
	DWORD rgbCurrent; // initial colour selection
	COLORREF cr;

	CPaintToolManager();
	~CPaintToolManager();
	sf::Color* OpenPaintDialog(sf::Window* _windowRef, sf::Color* _Colouref);

	void DrawShapes(sf::RenderWindow* _Window, sf::Shape* _Shape, sf::Vector2i* _MousePos);

	void DrawPen(sf::Vector2i* _MousePos, sf::Color* _PenColour);

	sf::RectangleShape* DrawRect(sf::Vector2i* _MousePos, sf::Color* _PenColour, sf::RenderWindow* _Window);
	sf::CircleShape* DrawCirc(sf::Vector2i* _MousePos, sf::Color* _PenColour, sf::RenderWindow* _Window);
	sf::RectangleShape* DrawLine(sf::Vector2i* _MousePos, sf::Color* _PenColour, sf::RenderWindow* _Window);
};