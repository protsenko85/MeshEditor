#pragma once
#include <glm/glm.hpp>;
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/rotate_vector.hpp>


class Camera
{
public:
	~Camera();
	Camera();
	void SetEye(glm::vec3 e);
	void SetTarget(glm::vec3 t);
	void SetUp(glm::vec3 u);
	glm::vec3 GetEye();
	glm::vec3 GetTarget();
	glm::vec3 GetUp();

	glm::mat4 calcViewMatrix() const;
	glm::vec3 calcForward() const;
	glm::vec3 calcRight() const;
	double distanceFromEyeToTarget() const;
	const glm::vec3& getEye() const;
	const glm::vec3& getTarget() const;
	void setFrontView();
	void setTopView();
	void setRearView();
	void setRightView();
	void setLeftView();
	void setBottomView();
	void setIsoView();
	void orbit(glm::vec3 a, glm::vec3 b);
	void pan(double u, double v);
	void zoom(double factor);
	void translate(glm::vec3 delta);
	void setDistanceToTarget(double D);
	void transform(const glm::mat4& trf);
	void rotate(glm::vec3 point, glm::vec3 axis, double angle);
	void setEyeTargetUp(glm::vec3 newEye, glm::vec3 newTarget, glm::vec3 newUp);
private:
	glm::vec3 eye { 0, 0, 5 };
	glm::vec3 target {0, 0, 0};
	glm::vec3 up{ 0, 1, 0 };
};
