/*

I'm gonna be real with you, I have no real clue how this works, Folke did most of the heavy lifting in my original pong game and I just copied.
But hey, it works :)

ctrl + f and search "movement" to see all the stuff you need to add

*/

#pragma once
#include <tge/input/InputManager.h> // MOVEMENT 1

struct MovableObject //make an object to move! MOVEMENT 2
{
	float y; // give it a y axis to move on
	float x; // give it an x axis to move on
};


class GameWorld
{
public:
	GameWorld();
	~GameWorld();

	void Init(Tga::InputManager* myInputManager); // MOVEMENT 3
	void Update(float aTimeDelta);
	void Render();

private:

	Tga::Sprite2DInstanceData myMovableObjectInstance = {};
	Tga::SpriteSharedData myMovableObjectSharedData = {};

	MovableObject myMovableObject; // create struct object...idk, I'm new here, MOVEMENT 3

	Tga::InputManager* myInputManager; // MOVEMENT 4

};