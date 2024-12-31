#pragma once

class GameWorld
{
public:
	GameWorld(); 
	~GameWorld();

	void Init();
	void Update(float aTimeDelta); 
	void Render();
	
private:
	// put these here so you don't have to put them in render and create a new img each frame (saves fps)

	// original sprite
	Tga::Sprite2DInstanceData myTGELogoInstance = {};
	Tga::SpriteSharedData mySharedData = {};

	//second sprite
	Tga::Sprite2DInstanceData myOwnImageInstance = {};
	Tga::SpriteSharedData myOwnImageSharedData = {};
};