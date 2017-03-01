#pragma once
#include "GLM\glm.hpp"
#include "GLM\ext.hpp"


/*
	Author: Jay Johnston
	Discription: Base camera class
*/
class Cameras
{
public:
	Cameras();
	~Cameras();

	virtual void update(float deltaTime) = 0;

	void setPerspective(float a_fieldOfView, float a_aspectRatio,float a_near, float a_far);

	void setLookAt(glm::vec3 a_from, glm::vec3 a_to, glm::vec3 a_up);

	void setPosition(glm::vec3 a_position);

	void rotate(glm::vec3 a_angle, float speed);

	glm::mat4 getWorldTransform() const;

	glm::mat4 getView() const;

	glm::mat4 getProjection() const;

	glm::mat4 getProjectionView() const;

protected:
	glm::mat4 worldTransform;
	glm::mat4 viewTransform;
	glm::mat4 projectionTransform;
	glm::mat4 projectionViewTransform;
	
	void updateProjectionViewTransform();

	double m_previousCusorPosX;
	double m_previousCusorPosY;

private:

};

