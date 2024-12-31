/*
	This is a movement AND input tutorial

	Here's a list of keys and their codes, I'll explain them more further down
	https://learn.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes
*/

#include "stdafx.h"
#include "GameWorld.h"
#include <tge/graphics/GraphicsEngine.h>
#include <tge/drawers/SpriteDrawer.h>
#include <tge/texture/TextureManager.h>
#include <tge/drawers/DebugDrawer.h>

// New includes
#include <Windows.h>



GameWorld::GameWorld()
{}

GameWorld::~GameWorld() 
{}



void GameWorld::Init()  
{
	// Our lovely TGA logo that we will be moving
	auto& engine = *Tga::Engine::GetInstance();

	Tga::Vector2ui intResolution = engine.GetRenderSize();
	Tga::Vector2f resolution = { (float)intResolution.x, (float)intResolution.y };
	{
		mySharedData.myTexture = engine.GetTextureManager().GetTexture(L"Sprites/tge_logo_w.dds");

		// tga logo position
		myMovableObject.positionX = 0.5f; // center of the screen
		myMovableObject.positionY = 0.5f; // center of the screen

		myTGELogoInstance.myPivot = { 0.5f, 0.5f };
		myTGELogoInstance.myPosition = Tga::Vector2f{ myMovableObject.positionX, myMovableObject.positionY }*resolution; // you need this in render as well for your sprite to update
		myTGELogoInstance.mySize = Tga::Vector2f{ 0.75f, 0.75f }*resolution.y;
		myTGELogoInstance.myColor = Tga::Color(1, 1, 1, 1);

		myMovableObject.movementSpeed = 0.05f; // Movement speed, change the value as you like
	}
}



void GameWorld::Update(float aTimeDelta)
{
	UNREFERENCED_PARAMETER(aTimeDelta);

	////// BASIC INPUT //////

	// Now this is how you set the input detector up
	if (GetAsyncKeyState(VK_UP) & 0x8000) // VK_UP is the up arrow, "& 0x8000" checks if the button is currently pressed, you need it for the key press to be detected and functional
	{
		//in here you put whatever you want to happen when you press your button...you know how if statements work by now
		std::cout << "Pressing the up arrow" << std::endl; // this prints in the console...it's mainly for debugging purposes (testing if your button actually works)
	}

	// There are some buttons that don't have a "placeholder" name, for example "W"
	// To make "E" work you instead need to write "0x45" like below (check the link above for a list of all the buttons and their codes)
	if (GetAsyncKeyState(0x45) & 0x8000)
	{
		std::cout << "Pressing E" << std::endl;
	}

	// You can also detect mouse button clicks
	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
	{
		std::cout << "Clicked the left mouse button" << std::endl;
	}



	////// INPUT FOR MOVEMENT //////

	if (GetAsyncKeyState(0x57) & 0x8000) // Pressing W
	{
		std::cout << "Pressing W" << std::endl; // debugging

		myMovableObject.positionY += myMovableObject.movementSpeed; // move the sprite up
	}

	if (GetAsyncKeyState(0x41) & 0x8000) // Pressing A
	{
		std::cout << "Pressing A" << std::endl; // debugging

		myMovableObject.positionX -= myMovableObject.movementSpeed; // move sprite to the left
	}

	if (GetAsyncKeyState(0x53) & 0x8000) // Pressing S
	{
		std::cout << "Pressing S" << std::endl; // debugging

		myMovableObject.positionY -= myMovableObject.movementSpeed; // move sprite down
	}

	if (GetAsyncKeyState(0x44) & 0x8000) // Pressing D
	{ 
		std::cout << "Pressing D" << std::endl; // debugging

		myMovableObject.positionX += myMovableObject.movementSpeed; // move sprite to the right
	}
}



void GameWorld::Render()
{

	auto& engine = *Tga::Engine::GetInstance();

	// Add these two lines for the *resolution to work
	Tga::Vector2ui intResolution = engine.GetRenderSize();
	Tga::Vector2f resolution = { (float)intResolution.x, (float)intResolution.y };

	Tga::SpriteDrawer& spriteDrawer(engine.GetGraphicsEngine().GetSpriteDrawer());
	// Game update
	{
		spriteDrawer.Draw(mySharedData, myTGELogoInstance);
		myTGELogoInstance.myPosition = Tga::Vector2f{ myMovableObject.positionX, myMovableObject.positionY }*resolution; // add this to update the render of the sprite (make it move)

	}
}