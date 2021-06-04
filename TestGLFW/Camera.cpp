#pragma once
#include "Camera.h"

Camera::Camera()
{
}

Camera::~Camera()
{
}

void Camera::SetEye(glm::vec3 e)
{
	eye = e;
}

void Camera::SetTarget(glm::vec3 t)
{
	target = t;
}

void Camera::SetUp(glm::vec3 u)
{
	up = u;
}

glm::vec3 Camera::GetEye()
{
	return eye;
}

glm::vec3 Camera::GetTarget()
{
	return target;
}

glm::vec3 Camera::GetUp()
{
	return up;
}

const glm::vec3& Camera::getEye() const
{
	return eye;
}

const glm::vec3& Camera::getTarget() const
{
	return target;
}

double Camera::distanceFromEyeToTarget() const
{
	return glm::distance(eye, target);
}

glm::mat4 Camera::calcViewMatrix() const
{
	return glm::lookAt(eye, target, up);
}

void Camera::setRightView()
{
	glm::vec3 oldTarget = target;
	setFrontView();
	rotate(oldTarget, { 0,1,0 }, glm::pi<float>() * 0.5);
}

void Camera::setLeftView()
{
	glm::vec3 oldTarget = target;
	setFrontView();
	rotate(oldTarget, { 0,-1,0 }, glm::pi<float>() * 0.5);
}

void Camera::setRearView()//вид сзади
{
	glm::vec3 oldTarget = target;
	setFrontView();
	rotate(oldTarget, { 0,0,-1 }, glm::pi<float>() * 0.5);
}

void Camera::setTopView()
{
	glm::vec3 oldTarget = target;
	setFrontView();
	rotate(oldTarget, { 1,0,0 }, glm::pi<float>() * 0.5);
}

void Camera::setBottomView()//вид снизу
{
	glm::vec3 oldTarget = target;
	setFrontView();
	rotate(oldTarget, { -1,0,0 }, glm::pi<float>() * 0.5);
}

glm::vec3 Camera::calcForward() const//определение направления взгляда
{
	return glm::normalize(eye - target);
}

void Camera::setIsoView()
{
	glm::vec3 oldTarget = target;
	setFrontView();
	rotate(oldTarget, { 1,1,0 }, glm::pi<float>() * 0.25);
}

void Camera::setFrontView()
{
	double D = distanceFromEyeToTarget();
	setEyeTargetUp(target + glm::vec3{ 0,0,1 }, target, { 0,1,0 });
	setDistanceToTarget(D);
}

void Camera::transform(const glm::mat4& trf)//перемножение всех векторов на матрицу трансформирования
{
	eye = trf * glm::vec4{ eye, 1 };
	target = trf * glm::vec4{ target, 1 };
	up = trf * glm::vec4{ up, 0 };
}

void Camera::rotate(glm::vec3 point, glm::vec3 axis, double angle)//перемещаем eye и target в точку 0,0,0, 
																	//расчитываем новую матрицу с уголом и направлением и возращаем точку на место
{
	translate(-point);
	transform(glm::rotate(calcViewMatrix(), (float)angle, axis));
	translate(point);
}

void Camera::translate(glm::vec3 delta)//смещение глаза и цели относительно точки
{
	eye += delta;
	target += delta;
}

void Camera::setDistanceToTarget(double D)//расчитываем приближаем или удаляем и умножаем на расстояние
{
	eye = target - calcForward() * (glm::vec3)D;
}

void Camera::setEyeTargetUp(glm::vec3 newEye, glm::vec3 newTarget, glm::vec3 newUp)//переприсваиваем значения, если форвард 
																					//и новый up не перпендикулярный - поворачиваем up
{
	eye = newEye;
	target = newTarget;
	if (glm::dot(calcForward(), newUp) != 0)
	{
		glm::vec3 f = glm::cross(calcForward(), newUp);
		up = glm::rotate(glm::half_pi<float>(), f) * glm::vec4(f, 0);
	}
	else
		up = newUp;
}

void Camera::orbit(glm::vec3 a, glm::vec3 b)//преобразование вида относительно перемещения с одной точки в другую точку
{
	float angle = glm::acos(glm::min(1.0f, glm::dot(a, b)));
	glm::vec3 axis = glm::cross(a, b);
	glm::mat3 toWorldCameraSpace = glm::inverse(calcViewMatrix());
	axis = toWorldCameraSpace * axis;
	glm::mat3 O = glm::rotate(angle, -axis);
	eye = target + O * (eye - target);
	up = O * up;
}

glm::vec3 Camera::calcRight() const //????
{
	return glm::normalize(glm::cross(up, calcForward()));
}

void Camera::pan(double u, double v)//пан-преобразование при равных векторных преобразованиях eye и target
{
	eye = eye + calcRight() * (float)u + up * (float)v;
	target = target + calcRight() * (float)u + up * (float)v;
}

void Camera::zoom(double factor)//приближение
{
	eye *= factor;
	target *= factor;
}


