/*

If you make all your sprites like björn did they'll have to update every frame, it'll lower fps, we don't want low fps
DO THIS INSTEAD!

*/


/*
If you don't know how to add your own images to this here's a mini tutorial

1. go to your tge folder
2. go to the source folder
3. go to the game folder
4. make a new folder, call it something like data
5. enter your new folder
6. make another folder, call it sprites or something similar
7. put all your assets in (they have to be png, dds or...tga (what kind of file format???)

when accessing the images don't forget to write it like this "sprites/image_name.png"

...think this is how you did it at least...I'll check tomorrow
 */

#include "stdafx.h"

#include "GameWorld.h"
#include <tge/graphics/GraphicsEngine.h>
#include <tge/drawers/SpriteDrawer.h>
#include <tge/texture/TextureManager.h>
#include <tge/drawers/DebugDrawer.h>


GameWorld::GameWorld()
{}

GameWorld::~GameWorld() 
{}

void GameWorld::Init()  
{
	// Gets screen resolution
	auto& engine = *Tga::Engine::GetInstance();
	Tga::Vector2ui intResolution = engine.GetRenderSize();
	Tga::Vector2f resolution = { (float)intResolution.x, (float)intResolution.y };
	{
		// Original sprite, comes free with the program
		mySharedData.myTexture = engine.GetTextureManager().GetTexture(L"Sprites/tge_logo_w.dds"); // Decides the picture you're using

		myTGELogoInstance.myPivot = { 0.5f, 0.5f }; // The centerpoint of the image
		myTGELogoInstance.myPosition = Tga::Vector2f{ 0.5f, 0.5f }*resolution; // Position of the image on screen
		myTGELogoInstance.mySize = Tga::Vector2f{ 0.75f, 0.75f }*resolution.y; // Image size
		myTGELogoInstance.myColor = Tga::Color(1, 1, 1, 1); // Image color...wait what???


		// Second sprite (still just the tge logo)
		myOwnImageSharedData.myTexture = engine.GetTextureManager().GetTexture(L"Sprites/tge_logo_w.dds"); // Use the "SharedData" on this, change the "tge_logo_w.dds" to your own image file name

		myOwnImageInstance.myPivot = { 0.5f, 0.5f };
		myOwnImageInstance.myPosition = Tga::Vector2f{ 0.5f, 0.8f }*resolution;
		myOwnImageInstance.mySize = Tga::Vector2f{ 0.75f, 0.75f }*resolution.y;
		myOwnImageInstance.myColor = Tga::Color(1, 1, 1, 1);
	}
}
void GameWorld::Update(float aTimeDelta)
{
	UNREFERENCED_PARAMETER(aTimeDelta);

}

void GameWorld::Render()
{
	auto &engine = *Tga::Engine::GetInstance();
	Tga::SpriteDrawer& spriteDrawer(engine.GetGraphicsEngine().GetSpriteDrawer());
	// Game update
	{
		// Gets screen resolution
		spriteDrawer.Draw(mySharedData, myTGELogoInstance); // draws original picture
		spriteDrawer.Draw(myOwnImageSharedData, myOwnImageInstance); // draws second picture

	}


}