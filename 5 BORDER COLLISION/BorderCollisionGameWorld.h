#pragma once

// if you don't know what this is yet, check tutorial 4 - Input with Windows.h 
struct Player
{
	float positionX;
	float positionY;

	float topRadius;
	float bottomRadius;
	float rightRadius;
	float leftRadius;
};


class GameWorld
{
public:
	GameWorld(); 
	~GameWorld();

	void Init();
	void Update(float aTimeDelta); 
	void Render();
private:
	Tga::Sprite2DInstanceData myTGELogoInstance = {};
	Tga::SpriteSharedData mySharedData = {};

	Player myPlayer;
};