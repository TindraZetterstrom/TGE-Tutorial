#pragma once
#include <tge/text/text.h> // Don't forget to include this


class GameWorld
{
public:
	GameWorld(); 
	~GameWorld();

	void Init();
	void Update(float aTimeDelta); 
	void Render();

private:

	Tga::Text myText; // we want this function because text is very expensive, this makes it less expensive...just do it, bud
	Tga::Text myTextThatUpdates;

	int myUpdateText; // don't forget this :D

};