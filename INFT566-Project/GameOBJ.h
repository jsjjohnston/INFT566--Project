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

	virtual void startup() = 0;
	virtual void shutdown() = 0;
	virtual void update(float deltaTime) = 0;
	virtual void draw() = 0;
};

