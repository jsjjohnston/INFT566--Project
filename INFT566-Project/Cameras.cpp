#include "Cameras.h"



Cameras::Cameras() : worldTransform(glm::mat4(1)), viewTransform(glm::mat4(1)), projectionTransform(glm::mat4(1)), projectionViewTransform(glm::mat4(1))
{
	m_previousCusorPosX = 1028 / 2;
	m_previousCusorPosY = 780 / 2;
}


Cameras::~Cameras()
{
}

void Cameras::setPerspective(float a_fieldOfView, float a_aspectRatio,float a_near, float a_far)
{
	projectionTransform = glm::perspective(a_fieldOfView, a_aspectRatio, a_near, a_far);
	updateProjectionViewTransform();
}

void Cameras::setLookAt(glm::vec3 a_from, glm::vec3 a_to, glm::vec3 a_up)
{
	viewTransform = glm::lookAt(a_from, a_to, a_up);
	worldTransform = glm::inverse(viewTransform);
	updateProjectionViewTransform();
}

void Cameras::setPosition(glm::vec3 a_position)
{
	//worldTransform[3] = worldTransform[3] + glm::vec4(a_position, 1);
	worldTransform = worldTransform * glm::translate(a_position);
	viewTransform = glm::inverse(worldTransform);
	updateProjectionViewTransform();
}

void Cameras::rotate(glm::vec3 a_angle, float speed)
{
	viewTransform = glm::rotate(speed, a_angle) * viewTransform;
	worldTransform = glm::inverse(viewTransform);
	updateProjectionViewTransform();
}

glm::mat4 Cameras::getWorldTransform() const
{
	return worldTransform;
}

glm::mat4 Cameras::getView() const
{
	return viewTransform;
}

glm::mat4 Cameras::getProjection() const
{
	return projectionTransform;
}

glm::mat4 Cameras::getProjectionView() const
{
	return projectionViewTransform;
}

void Cameras::updateProjectionViewTransform()
{
	projectionViewTransform = projectionTransform * viewTransform ;
}
