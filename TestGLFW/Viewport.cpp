#include "Viewport.h"
#include<iostream>

glm::mat4 Viewport::calcProjectionMatrix() const
{
	if (isParallelProj)
		return glm::ortho(0.0f, (float)width, (float)height, 0.0f, (float)zNear, (float)zFar);
	else
		return glm::perspective(getFov(), calcAspectRatio(), zNear, zFar);
}

void Viewport::setViewportSize(uint32_t width, uint32_t height)
{
	this->width = width;
	this->height = height;
}

void Viewport::setFOV(double inFOV)
{
	fov = inFOV;
}

void Viewport::setZNear(double inZNear)
{
	zNear = inZNear;
}

void Viewport::setZFar(double inZFar)
{
	zFar = inZFar;
}

void Viewport::setParallelProjection(bool use)
{
	isParallelProj = use;
}

double Viewport::getZNear() const
{
	return zNear;
}

double Viewport::getZFar() const
{
	return zFar;
}

double Viewport::getFov() const
{
	return glm::radians(fov);
}

double Viewport::getWidth() const
{
	return width;
}

double Viewport::getHeight() const
{
	return height;
}

bool Viewport::isParallelProjection() const
{
	return isParallelProj;
}

Camera& Viewport::getCamera()
{
	return camera;
}

//ray Viewport::calcCursorRay(double x, double y) const
//{
//	x = (2.0f * x) / width - 1.0f;
//	y = 1.0f - (2.0f * y) / height;
//	float z = 1.0f;
//	glm::vec3 ray_nds = glm::vec3(x, y, z);
//	glm::vec4 ray_clip(ray_nds.x, ray_nds.y, -1.0f, 1.0f);
//	glm::vec4 ray_eye = glm::inverse(calcProjectionMatrix()) * ray_clip;
//	ray_eye = glm::vec4(ray_eye.x, ray_eye.y, -1.0f, 0.0f);
//	glm::vec3 ray_wor = glm::inverse(camera.calcViewMatrix()) * ray_eye;
//	ray_wor = glm::normalize(ray_wor);
//	return ray();
//}

double Viewport::calcTargetPlaneWidth() const
{
	return calcTargetPlaneHeight() * calcAspectRatio();
}

double Viewport::calcTargetPlaneHeight() const
{
	return 2.0 * camera.distanceFromEyeToTarget() * glm::tan(glm::radians(fov / 2.0));
}

double Viewport::calcAspectRatio() const
{
	return width / (double)height;
}