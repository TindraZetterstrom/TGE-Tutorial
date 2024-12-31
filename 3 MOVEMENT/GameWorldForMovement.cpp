/*

I'm gonna be real with you, I have no real clue how this works, Folke did most of the heavy lifting in my original pong game and I just copied.
But hey, it works :)

ctrl + f and search "movement" to see all the stuff you need to add

*/

/* !=!=!=!=!=! UPDATE !=!=!=!=!=!

	You'll most likely only use this method for pong tbh...
	Look at the "Input with 'windows.h'" tutorial instead, it covers movement as well (it's much easier to deal with too)

*/


#include "stdafx.h"

#include "GameWorld.h"
#include <tge/graphics/GraphicsEngine.h>
#include <tge/drawers/SpriteDrawer.h>
#include <tge/texture/TextureManager.h>
#include <tge/drawers/DebugDrawer.h>

 // NEW INCLUDES
#include <tge/input/InputManager.h>



GameWorld::GameWorld()
{}

GameWorld::~GameWorld()
{}



void GameWorld::Init(Tga::InputManager* aInputManager) // MOVEMENT 1
{
	// Gets screen resolution, draws the TGE logo, we'll be moving this with this tutorial
	auto& engine = *Tga::Engine::GetInstance();
	Tga::Vector2ui intResolution = engine.GetRenderSize();
	Tga::Vector2f resolution = { (float)intResolution.x, (float)intResolution.y };
	{
		myMovableObjectSharedData.myTexture = engine.GetTextureManager().GetTexture(L"Sprites/tge_logo_w.dds");

		myMovableObject.x = 0.5f; // Start positon, x axis, MOVEMENT 2
		myMovableObject.y = 0.5f; // Start position, y axis, MOVEMENT 3

		myMovableObjectInstance.myPivot = { 0.5f, 0.5f };
		myMovableObjectInstance.myPosition = Tga::Vector2f{ myMovableObject.x, myMovableObject.y }*resolution; // use the myMovableObject. x/y instead of floats, MOVEMENT 4
		myMovableObjectInstance.mySize = Tga::Vector2f{ 0.75f, 0.75f }*resolution.y;
		myMovableObjectInstance.myColor = Tga::Color(1, 1, 1, 1);
	}

	myInputManager = aInputManager; // MOVEMENT 5
}



void GameWorld::Update(float aTimeDelta)
{
	UNREFERENCED_PARAMETER(aTimeDelta);

	// MOVEMENT 5
	if (myInputManager->IsKeyHeld('W')) // move up
	{
		myMovableObject.y += 0.02f;
	}

	if (myInputManager->IsKeyHeld('S')) // move down
	{
		myMovableObject.y -= 0.02f;

	}

	if (myInputManager->IsKeyHeld('A')) // move left
	{
		myMovableObject.x -= 0.02f;
	}

	if (myInputManager->IsKeyHeld('D')) // move right
	{
		myMovableObject.x += 0.02f;
	}

}



void GameWorld::Render()
{
	auto& engine = *Tga::Engine::GetInstance();

	Tga::Vector2ui intResolution = engine.GetRenderSize();
	Tga::Vector2f resolution = { (float)intResolution.x, (float)intResolution.y };

	Tga::SpriteDrawer& spriteDrawer(engine.GetGraphicsEngine().GetSpriteDrawer());
	{
		spriteDrawer.Draw(myMovableObjectSharedData, myMovableObjectInstance); // draw the sprite
		myMovableObjectInstance.myPosition = Tga::Vector2f{ myMovableObject.x, myMovableObject.y }*resolution; // use the myMovableObject. x/y instead of floats

	}

}