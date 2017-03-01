#pragma once

/*
	NOTE ensure Headder is correct
	GameOBJ
	Author: Jay Johnston
	Discription: Base Class for All game Objects
*/
class GameOBJ
{
public:
	GameOBJ();
	~GameOBJ();

	//Required Functions for all Game Objects
	virtual void update(float deltaTime) = 0;
	virtual void draw() = 0;
};

