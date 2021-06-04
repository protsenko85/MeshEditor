#pragma once
#include "Camera.h"
#include "glm/gtc/type_ptr.hpp"

struct ray
{
	glm::vec3 orig;
	glm::vec3 dir{ 0,0,1 };
};

class Viewport
{
public:
	glm::mat4 calcProjectionMatrix() const;

	void setViewportSize(uint32_t inWidth, uint32_t inHeight);
	void setFOV(double inFOV);
	void setZNear(double inZNear);
	void setZFar(double inZFar);
	void setParallelProjection(bool use);

	double getZNear() const; 		// 0.01 by default
	double getZFar() const; 		// 500 by default
	double getFov() const;		// 60 in degrees by default
	double getWidth() const; 		// 1 by default
	double getHeight() const; 		// 1 by default
	bool isParallelProjection() const; // false by default

	/*ray calcCursorRay(double x, double y) const;*/

	double calcTargetPlaneWidth() const;
	double calcTargetPlaneHeight() const;
	double calcAspectRatio() const;

	Camera& getCamera();
private:
	Camera camera;
	uint32_t width = 1920;
	uint32_t height = 1080;
	double fov = 60;
	double zNear = 0.01;
	double zFar = 500;
	bool isParallelProj = false;
};

