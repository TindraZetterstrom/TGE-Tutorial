#pragma once

struct MovableObject // make a struct or class to be able to make multiple movable ojects
{
	float positionX; // give your movable object a position on the X-axis
	float positionY; // give your movable object a position on the Y-axis

	float movementSpeed; // Decide how fast/much your movable object moves
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

	MovableObject myMovableObject; // create your instance of a moveable object
};