/* GUESS WHO'S ROLEPLAYING A TEACHER AGAIN!!! MEEEE!!!!

	Today I shall teach you some basic border collision...cause heaven knows someone else is allergic to doing that *cough* björn *cough*

*/

// I'll be using windows.h movement in this tutorial as well
// Collisions are based off of the pivot of your object (the little black circle that's drawn out on the tge logo)
// Keeping the pivot in the center of your object is gonna be the easiest when it comes to collisions

#include "stdafx.h"

#include "GameWorld.h"
#include <tge/graphics/GraphicsEngine.h>
#include <tge/drawers/SpriteDrawer.h>
#include <tge/texture/TextureManager.h>
#include <tge/drawers/DebugDrawer.h>

#include <Windows.h>

GameWorld::GameWorld()
{
}

GameWorld::~GameWorld()
{
}

void GameWorld::Init()
{
	auto& engine = *Tga::Engine::GetInstance();

	Tga::Vector2ui intResolution = engine.GetRenderSize();
	Tga::Vector2f resolution = { (float)intResolution.x, (float)intResolution.y };
	{
		// AN: rewrite this
		// Why I won't be using the TGA logo for this tutoral
		//myTGELogoInstance.mySize = Tga::Vector2f{ 0.75f, 0.75f }*resolution.y; 
		// so the TGA logo is actually a square png...I have no idea why they chose to do that...
		
		// You can of course do collision with a square...but for a tutorial that relies pretty heavily on you seeing where 
		// something is colliding with another thing, I don't think that's such a smart idea


		mySharedData.myTexture = engine.GetTextureManager().GetTexture(L"Sprites/notASquare.png"); // You most likely don't already have this picture...it's just a yellow 1920x1080 rectangle

		// we need these to move the tge logo
		myPlayer.positionX = 0.5f;
		myPlayer.positionY = 0.5f;

		myTGELogoInstance.myPivot = { 0.5f, 0.5f };
		myTGELogoInstance.myPosition = Tga::Vector2f{ myPlayer.positionX, myPlayer.positionY }*resolution;
		myTGELogoInstance.mySize = Tga::Vector2f{ 200.f, 100.f}; // this makes the TGA logo into a square...I have no idea why they would want this but they did so...

		myTGELogoInstance.myColor = Tga::Color(1, 1, 1, 1);

		// you need these to be able to move the "hitpoint" of your collision from the pivot (more about it later)
		// you need four of these if you're working with a square/rectangle (AN: can you make it three? remove one of the side ones I mean)
		myPlayer.topRadius = 0.045f;
		myPlayer.bottomRadius = 0.045f;
		myPlayer.leftRadius = 0.05f;
		myPlayer.rightRadius = 0.05f;

		// I don't have any sure fire way how to decide your "radius" yet...I'll be sure to update this when I do
		// For now you'll just have to test different numbers until you find something you like
	}
}



void GameWorld::Update(float aTimeDelta)
{
	// This gets the screen resolution
	auto& engine = *Tga::Engine::GetInstance();
	Tga::Vector2ui intResolution = engine.GetRenderSize();
	Tga::Vector2f resolution = { (float)intResolution.x, (float)intResolution.y };

	// MOVEMENT

	if (GetAsyncKeyState(VK_UP) & 0x8000) // Up Arrow
	{
		myPlayer.positionY += 0.5f * aTimeDelta;
	}

	if (GetAsyncKeyState(VK_DOWN) & 0x8000) // Down Arrow
	{
		myPlayer.positionY -= 0.5f * aTimeDelta;
	}

	if (GetAsyncKeyState(VK_LEFT) & 0x8000) // Left Arrow
	{
		myPlayer.positionX -= 0.5f * aTimeDelta;
	}

	if (GetAsyncKeyState(VK_RIGHT) & 0x8000) // Right Arrow
	{
		myPlayer.positionX += 0.5f * aTimeDelta;
	}

	// aTimeDelta, or delta time, is used for making ex movement consistent on multiple different computers



	/////// BORDER COLLISION ///////

	// I'll be doing this with manual input so it's easier to test
	// You can of course make the movement automatic (AN: have I gone through that?)

	// BUT FIRST!!!

	// Small resolution tutorial intermission!!!
	// I will go deeper on how the resolution works in TGE...I just have to figure it out myself first
	// but essentially... 
	// {x, y}
	// {0, 0} = bottom left
	// {1, 0} = bottom right
	// {0.5, 0.5} = center
	// {1, 0} = top left
	// {1, 1} = top right

	// OK, onto collision



	// You can write your collision like this:
	// 
	//  if (myPlayer.positionY > 1.f)
	//  {													   
	//	  // This "resets" the player
	//	  myPlayer.positionX = 0.5f;
	//	  myPlayer.positionY = 0.5f;
	//  }
	//
	// HOWEVER! It will base your collision on the pivot instead of the actual side of your object
	


	// In order to "fix" that you simply just add "+/-" and the "radius" you want to use

	if (myPlayer.positionY + myPlayer.topRadius > 1.f)   // This checks the top of your screen
	{													// You're supposed to be able to use "resolution.y" to check it instead of 1.f...
		// This "resets" the player					   // but why would they make that work twice, right? right???
		myPlayer.positionX = 0.5f;
		myPlayer.positionY = 0.5f;
	}

	if (myPlayer.positionY - myPlayer.bottomRadius < 0.f) // This checks the bottom of the screen
	{
		myPlayer.positionX = 0.5f;
		myPlayer.positionY = 0.5f;
	}

	if (myPlayer.positionX + myPlayer.rightRadius > 1.f) // This checks the right side of the screen
	{
		myPlayer.positionX = 0.5f;
		myPlayer.positionY = 0.5f;
	}

	if (myPlayer.positionX - myPlayer.leftRadius < 0.f) // This checks the left side of the screen
	{
		myPlayer.positionX = 0.5f;
		myPlayer.positionY = 0.5f;
	}

	// You can move the border by just writing a different number (in case you need, say a smaller screen that's your play area *cough* omtenta 1 *cough*) 
}



void GameWorld::Render()
{
	auto& engine = *Tga::Engine::GetInstance();
	Tga::SpriteDrawer& spriteDrawer(engine.GetGraphicsEngine().GetSpriteDrawer());
	Tga::Vector2ui intResolution = engine.GetRenderSize();
	Tga::Vector2f resolution = { (float)intResolution.x, (float)intResolution.y };


	spriteDrawer.Draw(mySharedData, myTGELogoInstance);
	myTGELogoInstance.myPosition = Tga::Vector2f{ myPlayer.positionX, myPlayer.positionY }*resolution; // for updating moving sprite



	// Draws the pivot point
#ifndef _RETAIL
	{
		Tga::DebugDrawer& dbg = engine.GetDebugDrawer();
		Tga::Color c1 = myTGELogoInstance.myColor;
		dbg.DrawCircle(myTGELogoInstance.myPosition, 5.f, (c1.myR + c1.myG + c1.myB) / 3 > 0.3f ? Tga::Color(0, 0, 0, 1) : Tga::Color(1, 1, 1, 1));
	}
#endif
}