#pragma once
#include "GameOBJ.h"
#include "AIE\Gizmos.h" // NOTE Should be convered to use openGL AIE Gemoerty 
#include "GLM\glm.hpp" // Math Libary 
#include "GLM\ext.hpp"

/*
	NOTE ensure Correct Header Grid
	Author: Jay Johnston
	Discription: Simple Grid Based off the Tutorials
*/

class Grid :
	public GameOBJ
{
public:
	Grid();
	~Grid();

	//Getter/Setter for m_projectionView
	const glm::mat4 getProjectionView();
	void setProjectionView(const glm::mat4 a_projectionView);

	//Set up the Grid
	virtual void startup();
	virtual void shutdown();
	virtual void update(float deltaTime);
	virtual void draw();

private:
	glm::mat4 m_projectionView;
};

