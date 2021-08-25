/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2021 Media Design School
File Name : PaintToolManager.h
Description : Class header for tool functions and tool bar
Author : Daniel Bolleboom
Mail : daniel.bolleboom@mds.ac.nz
**************************************************************************/
#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <windows.h>
#include <wingdi.h>
#include <string>

class CPaintToolManager
{
public:
	// Vector to store shapes
	std::vector<sf::Shape*> shapes;

	// Canvas setup
	sf::Image Canvas;
	sf::Texture CanvasTexture;
	sf::Sprite CanvasSprite;

	// Font setup
	sf::Font font;
	sf::Text toolbarColourText;
	sf::Text toolbarSizeText;
	sf::Text toolbarSizeNumber;

	// Toolbar setup
	sf::RectangleShape toolbarMain;
	sf::Image toolbarPenImage;
	sf::Image toolbarUndoImage;
	sf::Texture toolbarUndoText;
	sf::Sprite toolbarUndoSprite;
	sf::Image toolbarSaveImage;
	sf::Texture toolbarSaveText;
	sf::Sprite toolbarSaveSprite;
	sf::Image toolbarLoadImage;
	sf::Texture toolbarLoadText;
	sf::Sprite toolbarLoadSprite;
	sf::Texture toolbarPenText;
	sf::Sprite toolbarPenSprite;
	sf::RectangleShape toolbarRect;
	sf::CircleShape toolbarCirc;
	sf::RectangleShape toolbarLine;
	sf::RectangleShape toolbarColour;
	sf::RectangleShape toolbarSelection;
	sf::CircleShape toolbarPoly;
	sf::Image toolbarStampImage;
	sf::Texture toolbarStampText;
	sf::Sprite toolbarStampSprite;

	// Stamp image setup
	sf::Image stampToolImage;
	sf::Texture stampToolText;

	// Cursor setup
	sf::RectangleShape cursor;

	// Other variables setup
	int brushSize;
	int polySides;
	std::string brushSizeStr;

	bool isPaintDialogOpen;

	// Colour picker setup
	CHOOSECOLOR cc; // Common dialog box structure
	COLORREF acrCustClr[16];// Array of custom colours
	HWND hwnd; // Owne window
	// HBRUSH hbrush; // brush handle
	DWORD rgbCurrent; // initial colour selection
	COLORREF cr;

	// Method setup
	CPaintToolManager();
	~CPaintToolManager();
	sf::Color* OpenPaintDialog(sf::Window* _windowRef, sf::Color* _Colouref);

	void DrawShapes(sf::RenderWindow* _Window, sf::Shape* _Shape, sf::Vector2i* _MousePos);

	void DrawPen(sf::Vector2i* _MousePos, sf::Color* _PenColour);

	void DrawStamp(sf::Vector2i* _MousePos, sf::Color* _PenColour, sf::RenderWindow* _Window);

	sf::RectangleShape* DrawRect(sf::Vector2i* _MousePos, sf::Color* _PenColour, sf::RenderWindow* _Window);
	sf::CircleShape* DrawCirc(sf::Vector2i* _MousePos, sf::Color* _PenColour, sf::RenderWindow* _Window);
	sf::CircleShape* DrawPoly(sf::Vector2i* _MousePos, sf::Color* _PenColour, sf::RenderWindow* _Window);
	sf::RectangleShape* DrawLine(sf::Vector2i* _MousePos, sf::Color* _PenColour, sf::RenderWindow* _Window);
};