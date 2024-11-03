#include "stdafx.h"

#include "GameWorld.h"
#include <tge/graphics/GraphicsEngine.h>
#include <tge/drawers/SpriteDrawer.h>
#include <tge/texture/TextureManager.h>
#include <tge/drawers/DebugDrawer.h>

#include <tge/text/text.h> // Don't forget to include this



GameWorld::GameWorld()
{}

GameWorld::~GameWorld() 
{}



void GameWorld::Init()  
{
	myText = Tga::Text(L"Text/arial.ttf", Tga::FontSize_48); // Decide font + font size for your text. The "myText =" is to make the "Tga::Text myText;" function in the h file work
	myTextThatUpdates = Tga::Text(L"Text/arial.ttf", Tga::FontSize_60);

	myUpdateText = 0; // initialize the variable
}



void GameWorld::Update(float aTimeDelta)
{
	UNREFERENCED_PARAMETER(aTimeDelta); // when not using any delta time (tge's own timer)

	// This chunk of text gets the screen resolution
	auto& engine = *Tga::Engine::GetInstance();
	Tga::Vector2ui intResolution = engine.GetRenderSize();
	Tga::Vector2f resolution = { (float)intResolution.x, (float)intResolution.y };

	// Static text
	myText.SetText("Hello World!"); // Decide what the text should say
	myText.SetColor(Tga::Color(1.f, 1.f, 1.f, 1.f)); // Decide text color, this is white
	myText.SetPosition(Tga::Vector2f{ 0.5f, 0.5f } *resolution); // Decide where on the screen the text should be, this is in the center (the first letter starts in the middle of the screen, the text itself isn't centered...don't ask me why)



	// Text that updates
	if (myUpdateText < 10000) // simple example of updating the variable we want to print. put it before the print or it will just print the initial value :/
	{
		myUpdateText++;
	}

	myTextThatUpdates.SetText(std::to_string(myUpdateText)); // make the int into a string so it's displayable
	myTextThatUpdates.SetColor(Tga::Color(1.f, 1.f, 1.f, 1.f));
	myTextThatUpdates.SetPosition(Tga::Vector2{ 0.35f, 0.7f } *resolution); // { x position, y position }

}



void GameWorld::Render()
{
	myText.Render(); // Make the text visible on the game window
	myTextThatUpdates.Render();
}